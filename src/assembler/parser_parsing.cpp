#include "parser.h"

InstructionPtr Parser::parse_add() {
    const Token destinationToken = fetch();
    const Token commaToken = fetch();
    const Token sourceToken = fetch();

    // destinationToken must always be a register
    to_register(destinationToken);

    expect_type(commaToken, TokenType::COMMA);

    if (is_register_8_bit(destinationToken)) // Case 1: 8-bit (destinationToken is A)
    {
        to_register_expect(destinationToken, Register8Bit::A);

        if (is_register_8_bit(sourceToken)) {
            return std::make_unique<AddAAnd8BitRegister>(to_register_8_bit(sourceToken));
        } else { // is number or symbol
            return std::make_unique<AddAAndImmediate>(to_number_8_bit(sourceToken));
        }
    }
    else if (is_register_16_bit(destinationToken)) // Case 2: 16-bit (destinationToken is HL or SP)
    {
        if (is_register_16_bit(sourceToken)) {
            return std::make_unique<AddHLAnd16BitRegister>(to_register_16_bit(sourceToken));
        } else { // is number or symbol
            return std::make_unique<AddSPAndImmediate>(to_signed_number_8_bit(sourceToken));
        }
    }
    else
    {
        throw_logic_error_and_highlight(destinationToken, "Parse error: Invalid expression");
    }
}

InstructionPtr Parser::parse_adc() {
    const Token destinationToken = fetch();
    const Token commaToken = fetch();
    const Token sourceToken = fetch();

    // destinationToken must always be A
    to_register_expect(destinationToken, Register8Bit::A);
    expect_type(commaToken, TokenType::COMMA);

    if (is_register_8_bit(sourceToken)) {
        return std::make_unique<AddWithCarryAAnd8BitRegister>(to_register_8_bit(sourceToken));
    } else { // number or symbol
        return std::make_unique<AddWithCarryAAndImmediate>(to_number_8_bit(sourceToken));
    }
}

InstructionPtr Parser::parse_bit() {
    const Token indexToken = fetch();
    const Token commaToken = fetch();
    const Token registerToken = fetch();

    // BIT INDEX, 8BitRegister

    // index must be between 0 and 7
    const uint8_t index = to_index(indexToken);

    expect_type(commaToken, TokenType::COMMA);

    const Register8Bit reg = to_register_8_bit(registerToken);

    return std::make_unique<BitOf8BitRegisterComplementIntoZero>(index, reg);
}

////

void Parser::parse_equ() {
    const Token symbolicName = fetch();
    const Token equToken = fetch();
    const Token numericToken = fetch();

    expect_type(symbolicName, TokenType::IDENTIFIER);

    //TODO: exclude registers!

    expect_string(equToken, "EQU");

    const long numeric = to_number(numericToken);

    _symbolicTable.emplace(symbolicName.get_string(), numeric);
}


