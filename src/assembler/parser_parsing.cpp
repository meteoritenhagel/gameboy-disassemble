#include "parser.h"

typename Parser::UnresolvedInstruction Parser::parse_add() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    UnresolvedInstruction returnedInstruction;

    if (read_next().get_token_type() == TokenType::COMMA) { // if comma on second position, then long version, e.g. "ADD A, B" or "ADD SP, -0x01"
        const Token destinationToken = fetch();
        const Token commaToken = fetch();
        const Token sourceToken = fetch();

        to_register(destinationToken); // destinationToken must always be a register

        if (is_register_8_bit(destinationToken)) { // Case 1: 8-bit (destinationToken is A)
            to_register_expect(destinationToken, Register8Bit::A);

            if (is_register_8_bit(sourceToken)) {
                returnedInstruction = [this, sourceToken](){ return create_instruction<AddAAnd8BitRegister>(to_register_8_bit(sourceToken)); };
            } else { // is number or symbol
                returnedInstruction = [this, sourceToken](){ return create_instruction<AddAAndImmediate>(to_number_8_bit(sourceToken)); };
            }
        } else if (is_register_16_bit(destinationToken)) { // Case 2: 16-bit (destinationToken is HL or SP)
            if (is_register_16_bit(sourceToken)) {
                returnedInstruction = [this, sourceToken](){ return create_instruction<AddHLAnd16BitRegister>(to_register_16_bit(sourceToken)); };
            } else { // is number or symbol
                returnedInstruction = [this, sourceToken](){ return create_instruction<AddSPAndImmediate>(to_signed_number_8_bit(sourceToken)); };
            }
        }
    } else { // short version, e.g. "ADD B", ONLY for 8-bit contexts
        const Token sourceToken = fetch();

        if (is_register_8_bit(sourceToken)) {
            returnedInstruction = [this, sourceToken](){ return create_instruction<AddAAnd8BitRegister>(to_register_8_bit(sourceToken)); };
        } else { // is number or symbol
            returnedInstruction = [this, sourceToken](){ return create_instruction<AddAAndImmediate>(to_number_8_bit(sourceToken)); };
        }
    }

    return returnedInstruction;
}

typename Parser::UnresolvedInstruction Parser::parse_adc() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    if (read_next().get_token_type() == TokenType::COMMA) { // long version, e.g. ADC A, B
        to_register_expect(fetch(), Register8Bit::A);
        const Token commaToken = fetch();
    } // else short version

    const Token sourceToken = fetch();

    if (is_register_8_bit(sourceToken)) {
        return [this, sourceToken](){ return create_instruction<AddWithCarryAAnd8BitRegister>(to_register_8_bit(sourceToken)); };
    } else { // number or symbol
        return [this, sourceToken](){ return create_instruction<AddWithCarryAAndImmediate>(to_number_8_bit(sourceToken)); };
    }
}

typename Parser::UnresolvedInstruction Parser::parse_bit() {
    increment_position(); // because instruction-specific token was already checked before calling the function

    const Token indexToken = fetch();
    const Token commaToken = fetch();
    const Token registerToken = fetch();

    // BIT INDEX, 8BitRegister

    expect_type(commaToken, TokenType::COMMA);

    return [this, indexToken, registerToken]() { return create_instruction<BitOf8BitRegisterComplementIntoZero>(to_index(indexToken), to_register_8_bit(registerToken)); };
}

typename Parser::UnresolvedInstruction Parser::parse_inc() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token registerToken = fetch();
    return [this, registerToken](){ return create_instruction<IncrementRegister>(to_register(registerToken)); };
}

typename Parser::UnresolvedInstruction Parser::parse_dec() {
    increment_position(); // because instruction-specific token was already checked before calling the function
    const Token registerToken = fetch();
    return [this, registerToken](){ return create_instruction<DecrementRegister>(to_register(registerToken)); };
}

typename Parser::UnresolvedInstruction Parser::parse_jp() {
    increment_position(); // because instruction-specific token was already checked before calling the function

    if (read_next().get_token_type() == TokenType::COMMA) { // conditioned version, e.g. JP NZ, 0x1234
        const Token conditionToken = fetch();
        const Token commaToken = fetch();
        const Token addressToken = fetch();

        return [this, conditionToken, addressToken](){ return create_instruction<JumpConditional>(to_flag_condition(conditionToken), to_number_16_bit(addressToken)); };
    } else { // short version
        const Token addressToken = fetch();

        if (is_register(addressToken)) { // JP HL
            to_register_expect(addressToken, Register16Bit::HL);
            return [](){ return create_instruction<JumpToHL>(); };
        }
        else { // has to be numeric value
            return [this, addressToken](){ return create_instruction<Jump>(to_number_16_bit(addressToken)); };
        }
    }
}

////

void Parser::parse_equ() {
    const Token symbolicName = fetch();
    const Token equToken = fetch();
    const Token numericToken = fetch();

    expect_type(symbolicName, TokenType::IDENTIFIER);

    if (is_register(symbolicName)) { // registers may not be assigned
        throw_logic_error_and_highlight(symbolicName, "Parse error: Expression " + symbolicName.get_string() + " cannot appear at left side of EQU command ");
    }

    expect_string(equToken, "EQU");

    const long numeric = to_number(numericToken);

    _symbolicTable.emplace(symbolicName.get_string(), numeric);
}


