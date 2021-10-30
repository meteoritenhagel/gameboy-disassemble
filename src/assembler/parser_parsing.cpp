#include "parser.h"

/******************************/
/******** ADD COMMANDS ********/
/******************************/
UnresolvedInstructionPtr Parser::parse_add() {
    increment_position(); // because instruction-specific token was already checked before calling the function

    if (read_next().get_token_type() ==
        TokenType::COMMA) { // if comma on second position, then long version, e.g. "ADD A, B" or "ADD SP, -0x01"
        const Token destinationToken = fetch();
        const Token commaToken = fetch();
        const Token sourceToken = fetch();

        to_register(destinationToken); // destinationToken must always be a register

        if (is_register_8_bit(destinationToken)) { // Case 1: 8-bit (destinationToken is A)
            to_register_expect(destinationToken, Register8Bit::A);

            if (is_register_8_bit(sourceToken)) {
                return create_unresolved_instruction([this, sourceToken]() {
                    return AddAAnd8BitRegister(to_register_8_bit(sourceToken));
                });
            } else { // is number or symbol
                return create_unresolved_instruction([this, sourceToken]() {
                    return AddAAndImmediate(to_number_8_bit(sourceToken));
                });
            }
        } else if (is_register_16_bit(destinationToken)) { // Case 2: 16-bit (destinationToken is HL or SP)
            if (is_register_16_bit(sourceToken)) {
                return create_unresolved_instruction([this, sourceToken]() {
                    return AddHLAnd16BitRegister(to_register_16_bit(sourceToken));
                });
            } else { // is number or symbol
                return create_unresolved_instruction([this, sourceToken]() {
                    return AddSPAndImmediate(to_signed_number_8_bit(sourceToken));
                });
            }
        }
    } else { // short version, e.g. "ADD B", ONLY for 8-bit contexts
        const Token sourceToken = fetch();

        if (is_register_8_bit(sourceToken)) {
            return create_unresolved_instruction([this, sourceToken]() {
                return AddAAnd8BitRegister(to_register_8_bit(sourceToken));
            });
        } else { // is number or symbol
            return create_unresolved_instruction([this, sourceToken]() {
                return AddAAndImmediate(to_number_8_bit(sourceToken));
            });
        }
    }
}

UnresolvedInstructionPtr Parser::parse_adc() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    if (read_next().get_token_type() == TokenType::COMMA) { // long version, e.g. ADC A, B
        to_register_expect(fetch(), Register8Bit::A);
        const Token commaToken = fetch();
    } // else short version

    const Token sourceToken = fetch();

    if (is_register_8_bit(sourceToken)) {
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return AddWithCarryAAnd8BitRegister(to_register_8_bit(sourceToken));
                }
        );
    } else { // number or symbol
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return AddWithCarryAAndImmediate(to_number_8_bit(sourceToken));
                }
        );
    }
}

/*****************************************/
/******** BIT COMPLEMENT COMMANDS ********/
/*****************************************/

UnresolvedInstructionPtr Parser::parse_bit() {
    increment_position(); // because instruction-specific token was already checked before calling the function

    const Token indexToken = fetch();
    const Token commaToken = fetch();
    const Token registerToken = fetch();

    // BIT INDEX, 8BitRegister

    expect_type(commaToken, TokenType::COMMA);

    return create_unresolved_instruction([this, indexToken, registerToken]() {
        return BitOf8BitRegisterComplementIntoZero(to_index(indexToken),
                                                   to_register_8_bit(registerToken));
    });
}

/**********************************/
/******** INC/DEC COMMANDS ********/
/**********************************/

UnresolvedInstructionPtr Parser::parse_inc() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token registerToken = fetch();
    if (registerToken.get_string() == "AF") {
        throw_logic_error_and_highlight(registerToken, "Parser error: \"AF\" is forbidden in this context");
    }
    return create_unresolved_instruction(
            [this, registerToken]() { return IncrementRegister(to_register(registerToken)); });
}

UnresolvedInstructionPtr Parser::parse_dec() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token registerToken = fetch();
    if (registerToken.get_string() == "AF") {
        throw_logic_error_and_highlight(registerToken, "Parser error: \"AF\" is forbidden in this context");
    }
    return create_unresolved_instruction(
            [this, registerToken]() { return DecrementRegister(to_register(registerToken)); });
}

/*******************************/
/******** JUMP COMMANDS ********/
/*******************************/

UnresolvedInstructionPtr Parser::parse_jp() {
    increment_position(); // because instruction-specific token was already checked before calling the function

    if (read_next().get_token_type() == TokenType::COMMA) { // conditioned version, e.g. JP NZ, 0x1234
        const Token conditionToken = fetch();
        const Token commaToken = fetch();
        const Token addressToken = fetch();

        return create_unresolved_instruction([this, conditionToken, addressToken]() {
            return JumpConditional(to_flag_condition(conditionToken), to_unsigned_number_16_bit(addressToken));
        });
    } else { // short version
        const Token addressToken = fetch();

        if (is_register(addressToken)) { // JP HL
            to_register_expect(addressToken, Register16Bit::HL);
            return create_unresolved_instruction([]() { return JumpToHL(); });
        } else { // has to be numeric value
            return create_unresolved_instruction(
                    [this, addressToken]() { return Jump(to_unsigned_number_16_bit(addressToken)); });
        }
    }
}

UnresolvedInstructionPtr Parser::parse_jr() { // JR s8
    increment_position(); // because instruction-specific token was already checked before calling the function
    const auto offsetToken = fetch();

    if (offsetToken.get_token_type() == TokenType::NUMBER) { // relative jump to fixed address
        return create_unresolved_instruction([this, offsetToken]() {
            return JumpRelative(to_signed_number_8_bit(offsetToken));
        });
    }

    // else, it has to be label or constant. Please do not use signed 8-bit constants, as they will be treated like labels!
    expect_type(offsetToken, {TokenType::IDENTIFIER, TokenType::LOCAL_LABEL});
    const size_t referenceAddress = _currentAddress;
    return create_unresolved_instruction([this, offsetToken, referenceAddress]() {
        return JumpRelative(to_relative_offset(offsetToken, referenceAddress));
    });
}

/*******************************/
/******** LOAD COMMANDS ********/
/*******************************/

UnresolvedInstructionPtr Parser::parse_ld() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    /* The order is very specific, since for determining each subcase no
     * token type check of the token containing an immediate value may be done.
     * This is due to the fact that the constructed instructions are unresolved
     * and therefore may be of type TokenType::IDENTIFIER even though they are numbers, addresses etc.
     *
     *
     *  case 1: LD r16, XX
     *      1a) LD HL, SP+a8 <-> LDHL SP, a8 // TODO: first variant does not support constants yet
     *      1b) LD r16, a16
     *      1c) LD SP, HL
     *  case 2: LD r8, XX
     *      2a) LD r8, r8
     *      2b) [1] LD A, (BC|DE)
     *          [2] LD A, (HL+|-) <-> LD A, (HLI|D)
     *          [3] LD A, (C)
     *          [4] LD A, (a16)
     *      2c) LD r8, a8
     *  case 3: LD XX, A
     *      3a) LD (BC|DE), A
     *      3b) LD (HL+|-), A <-> LD (HLI|D), A
     *      3c) LD (C), A
     *      3d) LD (a16), A
     *  case 4: LD (a16), SP
    */

    const Token destinationToken = fetch();
    const Token commaToken = fetch_and_expect({TokenType::COMMA});
    const Token sourceToken = fetch();

    // 1: LD r16, XX
    if (is_register_16_bit(destinationToken)) {
        const auto destination = to_register_16_bit(destinationToken);

        // 1a) LD HL, SP+s8
        if (destination == Register16Bit::HL) {
            expect_type(sourceToken, TokenType::SP_SHIFTED);
            return create_unresolved_instruction([this, sourceToken]() {
                return LoadSPShiftedByImmediateIntoHL(to_signed_number_8_bit(sourceToken));
            });
        // 1b) LD r16, a16
        } else if (!is_register_16_bit(sourceToken)) { // this strange construction must be so that the immediate value can be resolved as a last step
            if (destination == Register16Bit::AF) {
                throw_logic_error_and_highlight(destinationToken, "Parser error: \"AF\" is forbidden in this context");
            }
            return create_unresolved_instruction([this, sourceToken, destination]() {
                return LoadImmediateInto16BitRegister(destination, to_number_16_bit(sourceToken));
            });
        // 1c) LD SP, HL
        } else {
            to_register_expect(destinationToken, Register16Bit::SP);
            to_register_expect(sourceToken, Register16Bit::HL);
            return create_unresolved_instruction([]() {
                return LoadHLIntoSP();
            });
        }
    // 2: LD r8, XX
    } else if (is_register_8_bit(destinationToken)){
        const auto destination = to_register_8_bit(destinationToken);

        // 2a) LD r8, r8
        if (is_register_8_bit(sourceToken)) {
            const auto source = to_register_8_bit(sourceToken);
            if (source == destination && destination == Register8Bit::ADDRESS_HL) { // LD (HL), (HL) is forbidden
                throw_logic_error_and_highlight(destinationToken, "Parser error: \"LD (HL), (HL)\" is invalid command");
            }
            return create_unresolved_instruction([this, source, destination]() {
                return Load8BitRegisterInto8BitRegister(source, destination);
            });
        } else if (destination == Register8Bit::A) {
            // 2b) LD A, XX
            // [1]: i) LD A, (BC)
            const std::string source_str = to_upper(sourceToken.get_string());
            if (source_str == "(BC)") // 4b
                return create_unresolved_instruction([](){
                    return LoadAddress16BitRegisterIntoA(Register16Bit::BC);
                });
            // [2]: ii) LD A, (DE)
            else if (source_str == "(DE)") // 4b
                return create_unresolved_instruction([](){
                    return LoadAddress16BitRegisterIntoA(Register16Bit::DE);
                });
            // [2]: i) LD A, (HL+)
            else if (source_str == "(HL+)" || source_str == "(HLI)") // 4c
                return create_unresolved_instruction([](){
                    return LoadAddressHLIncrementIntoA();
                });
            // [2]: ii) LD A, (HL-)
            else if (source_str == "(HL-)" || source_str == "(HLD)") // 4c
                return create_unresolved_instruction([](){
                    return LoadAddressHLDecrementIntoA();
                });
            // [3]: LD A, (C)
            else if (source_str == "(C)")
                return create_unresolved_instruction([](){
                    return LoadPortAddressCIntoA();
                });
            else
                // [4]: LD A, (a16)
                return create_unresolved_instruction([this, sourceToken]() {
                    return LoadAddressImmediateIntoA(to_number_16_bit(sourceToken));
                });
        } else {
            // 2c) LD r8, a8
            return create_unresolved_instruction([this, sourceToken, destination]() {
                return LoadImmediateInto8BitRegister(destination, to_number_8_bit(sourceToken));
            });
        }
    // 3 LD XX, A
    } else if (is_register_8_bit(sourceToken)) {
        const auto source = to_register_expect(sourceToken, Register8Bit::A);
        const std::string destination_str = to_upper(destinationToken.get_string());

        // 3a) [1] LD (BC), A
        if (destination_str == "(BC)")
            return create_unresolved_instruction([](){
                return LoadAIntoAddress16BitRegister(Register16Bit::BC);
            });
        // 3a) [2] LD (DE), A
        else if (destination_str == "(DE)")
            return create_unresolved_instruction([](){
                return LoadAIntoAddress16BitRegister(Register16Bit::DE);
            });
        // 3b) [1] LD (HL+), A
        else if (destination_str == "(HL+)" || destination_str == "(HLI)") // 2b (3)
            return create_unresolved_instruction([](){
                return LoadAIntoAddressHLIncrement();
            });
        // 3b) [4] LD (HL-), A
        else if (destination_str == "(HL-)" || destination_str == "(HLD)") // 2b (3)
            return create_unresolved_instruction([](){
                return LoadAIntoAddressHLDecrement();
            });
        // 3c)
        else if (destination_str == "(C)")
            return create_unresolved_instruction([](){
                return LoadAIntoPortAddressC();
            });
        // 3d)
        else
            return create_unresolved_instruction([this, destinationToken]() {
                return LoadAIntoAddressImmediate(to_number_16_bit(destinationToken));
            });
    // 4: LD HL, SP+s8
    } else {
        to_register_expect(sourceToken, Register16Bit::SP);
            return create_unresolved_instruction([this, destinationToken]() {
                return LoadSPIntoAddressImmediate(to_number_16_bit(destinationToken));
            });
    }
}

UnresolvedInstructionPtr Parser::parse_ldi() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token destinationToken = fetch();
    const Token commaToken = fetch_and_expect({TokenType::COMMA});
    const Token sourceToken = fetch();

    if (to_register_8_bit(destinationToken) == Register8Bit::ADDRESS_HL) { // LDI (HL), A
        to_register_expect(sourceToken, Register8Bit::A);
        return create_unresolved_instruction([](){
            return LoadAIntoAddressHLIncrement();
        });
    } else { // LDI A, (HL)
        to_register_expect(destinationToken, Register8Bit::A);
        to_register_expect(sourceToken, Register8Bit::ADDRESS_HL);
        return create_unresolved_instruction([](){
            return LoadAddressHLIncrementIntoA();
        });
    }
}

UnresolvedInstructionPtr Parser::parse_ldd() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token destinationToken = fetch();
    const Token commaToken = fetch_and_expect({TokenType::COMMA});
    const Token sourceToken = fetch();

    if (to_register_8_bit(destinationToken) == Register8Bit::ADDRESS_HL) { // LDD (HL), A
        to_register_expect(sourceToken, Register8Bit::A);
        return create_unresolved_instruction([](){
            return LoadAIntoAddressHLDecrement();
        });
    } else { // LDD A, (HL)
        to_register_expect(destinationToken, Register8Bit::A);
        to_register_expect(sourceToken, Register8Bit::ADDRESS_HL);
        return create_unresolved_instruction([](){
            return LoadAddressHLDecrementIntoA();
        });
    }
}

UnresolvedInstructionPtr Parser::parse_ldh() {
//    LDH (A8), A <-> TODO: SUPPORT LD (a8), A ???
//    LDH A, (A8) <-> TODO: SUPPORT LD A, (a8) ???
    increment_position(); // because instruction-specific token was already checked before calling the function

    const Token destinationToken = fetch();
    const Token commaToken = fetch_and_expect({TokenType::COMMA});
    const Token sourceToken = fetch();

    if (destinationToken.get_token_type() == TokenType::ADDRESS) { // LD (a8), A
        return create_unresolved_instruction([this, destinationToken]() {
            return LoadAIntoPortAddressImmediate(to_number_8_bit(destinationToken));
        });
    } else { // LD A, (a8)
        to_register_expect(destinationToken, Register8Bit::A);
        return create_unresolved_instruction([this, sourceToken]() {
            return LoadPortAddressImmediateIntoA(to_number_8_bit(sourceToken));
        });
    }
}

UnresolvedInstructionPtr Parser::parse_ldhl() {
    //    LDHL SP, s8 <-> LD HL, SP+s8
    increment_position(); // because instruction-specific token was already checked before calling the function

    const Token destinationToken = fetch();
    const Token commaToken = fetch_and_expect({TokenType::COMMA});
    const Token sourceToken = fetch();

    to_register_expect(destinationToken, Register16Bit::SP);
    return create_unresolved_instruction([this, sourceToken]() {
        return LoadSPShiftedByImmediateIntoHL(to_signed_number_8_bit(sourceToken));
    });
}

/**********************************/
/******** LOGICAL COMMANDS ********/
/**********************************/

UnresolvedInstructionPtr Parser::parse_and() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    if (read_next().get_token_type() == TokenType::COMMA) { // long version, e.g. AND A, B
        to_register_expect(fetch(), Register8Bit::A);
        const Token commaToken = fetch();
    } // else short version

    const Token sourceToken = fetch();

    if (is_register_8_bit(sourceToken)) {
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return AndAAnd8BitRegister(to_register_8_bit(sourceToken));
                }
        );
    } else { // number or symbol
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return AndAAndImmediate(to_number_8_bit(sourceToken));
                }
        );
    }
}

UnresolvedInstructionPtr Parser::parse_or() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    if (read_next().get_token_type() == TokenType::COMMA) { // long version, e.g. AND A, B
        to_register_expect(fetch(), Register8Bit::A);
        const Token commaToken = fetch();
    } // else short version

    const Token sourceToken = fetch();

    if (is_register_8_bit(sourceToken)) {
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return OrAAnd8BitRegister(to_register_8_bit(sourceToken));
                }
        );
    } else { // number or symbol
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return OrAAndImmediate(to_number_8_bit(sourceToken));
                }
        );
    }
}

UnresolvedInstructionPtr Parser::parse_xor() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    if (read_next().get_token_type() == TokenType::COMMA) { // long version, e.g. AND A, B
        to_register_expect(fetch(), Register8Bit::A);
        const Token commaToken = fetch();
    } // else short version

    const Token sourceToken = fetch();

    if (is_register_8_bit(sourceToken)) {
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return XorAAnd8BitRegister(to_register_8_bit(sourceToken));
                }
        );
    } else { // number or symbol
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return XorAAndImmediate(to_number_8_bit(sourceToken));
                }
        );
    }
}

UnresolvedInstructionPtr Parser::parse_cp() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    if (read_next().get_token_type() == TokenType::COMMA) { // long version, e.g. AND A, B
        to_register_expect(fetch(), Register8Bit::A);
        const Token commaToken = fetch();
    } // else short version

    const Token sourceToken = fetch();

    if (is_register_8_bit(sourceToken)) {
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return CompareAAnd8BitRegister(to_register_8_bit(sourceToken));
                }
        );
    } else { // number or symbol
        return create_unresolved_instruction(
                [this, sourceToken]() {
                    return CompareAAndImmediate(to_number_8_bit(sourceToken));
                }
        );
    }
}

UnresolvedInstructionPtr Parser::parse_cpl() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction(
            []() {
                return ComplementA();
            }
    );
}

UnresolvedInstructionPtr Parser::parse_daa() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction(
            []() {
                return DecimalAdjustA();
            }
    );
}

/**********************************/
/******** MACHINE COMMANDS ********/
/**********************************/

UnresolvedInstructionPtr Parser::parse_nop() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction(
            []() {
                return Nop();
            }
    );
}

UnresolvedInstructionPtr Parser::parse_stop(){
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction(
            []() {
                return Stop();
            }
    );
}

UnresolvedInstructionPtr Parser::parse_halt(){
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction(
            []() {
                return Halt();
            }
    );
}

UnresolvedInstructionPtr Parser::parse_scf(){
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction(
            []() {
                return SetCarry();
            }
    );
}

UnresolvedInstructionPtr Parser::parse_ccf(){
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction(
            []() {
                return FlipCarry();
            }
    );
}

UnresolvedInstructionPtr Parser::parse_ei(){
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction(
            []() {
                return EnableInterrupts();
            }
    );
}

UnresolvedInstructionPtr Parser::parse_di(){
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction(
            []() {
                return DisableInterrupts();
            }
    );
}

/***********************************/
/******** PUSH/POP COMMANDS ********/
/***********************************/

UnresolvedInstructionPtr Parser::parse_push() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token operandToken = fetch();
    return create_unresolved_instruction([this, operandToken]() {
        return Push16BitRegister(to_register_16_bit(operandToken));
    });
}

UnresolvedInstructionPtr Parser::parse_pop() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token operandToken = fetch();
    return create_unresolved_instruction([this, operandToken]() {
        return Pop16BitRegister(to_register_16_bit(operandToken));
    });
}

/***********************************/
/******** ROTATION COMMANDS ********/
/***********************************/

UnresolvedInstructionPtr Parser::parse_rr() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token operandToken = fetch();
    return create_unresolved_instruction([this, operandToken]() {
        return RotateRight8BitRegister(to_register_8_bit(operandToken));
    });
}

UnresolvedInstructionPtr Parser::parse_rl() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token operandToken = fetch();
    return create_unresolved_instruction([this, operandToken]() {
        return RotateLeft8BitRegister(to_register_8_bit(operandToken));
    });
}

UnresolvedInstructionPtr Parser::parse_rrc() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token operandToken = fetch();
    return create_unresolved_instruction([this, operandToken]() {
        return RotateRightCircular8BitRegister(to_register_8_bit(operandToken));
    });
}

UnresolvedInstructionPtr Parser::parse_rlc() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token operandToken = fetch();
    return create_unresolved_instruction([this, operandToken]() {
        return RotateLeftCircular8BitRegister(to_register_8_bit(operandToken));
    });
}

UnresolvedInstructionPtr Parser::parse_rla() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction([]() {
        return RotateLeftAAndClearZero();
    });
}

UnresolvedInstructionPtr Parser::parse_rra() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction([]() {
        return RotateRightAAndClearZero();
    });
}

UnresolvedInstructionPtr Parser::parse_rlca() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction([]() {
        return RotateLeftCircularAAndClearZero();
    });
}

UnresolvedInstructionPtr Parser::parse_rrca() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    return create_unresolved_instruction([]() {
        return RotateRightCircularAAndClearZero();
    });
}

/***********************************/
/******** SPECIFIC COMMANDS ********/
/***********************************/

void Parser::parse_equ() {
    const Token symbolicName = fetch();
    const Token equToken = fetch();
    const Token numericToken = fetch();

    expect_type(symbolicName, TokenType::IDENTIFIER);

    if (is_register(symbolicName)) { // registers may not be assigned
        throw_logic_error_and_highlight(symbolicName, "Parse error: Expression " + symbolicName.get_string() +
                                                      " cannot appear at left side of EQU command ");
    }

    expect_string(equToken, "EQU");
    symbol_emplace(to_number(numericToken), symbolicName);
}


