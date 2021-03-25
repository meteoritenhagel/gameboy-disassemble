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

        switch (sourceToken.get_token_type()) {
            case TokenType::IDENTIFIER:
                return std::make_unique<AddAAnd8BitRegister>(to_register_8_bit(sourceToken));
            case TokenType::NUMBER:
                return std::make_unique<AddAAndImmediate>(to_number_8_bit(sourceToken));
            default: break;
        }
    }
    else if (is_register_16_bit(destinationToken)) // Case 2: 16-bit (destinationToken is HL or SP)
    {
        switch(sourceToken.get_token_type()) {
            case TokenType::IDENTIFIER: // ADD HL, Register16Bit
                to_register_expect(destinationToken, Register16Bit::HL);
                return std::make_unique<AddHLAnd16BitRegister>(to_register_16_bit(sourceToken));
            case TokenType::NUMBER: // ADD SP, +16-bit-immediate
                to_register_expect(destinationToken, Register16Bit::SP);
                return std::make_unique<AddSPAndImmediate>(to_signed_number_8_bit(sourceToken));
            default: break;
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

    switch (sourceToken.get_token_type()) {
        case TokenType::IDENTIFIER:
            return std::make_unique<AddWithCarryAAnd8BitRegister>(to_register_8_bit(sourceToken));
        case TokenType::NUMBER:
            return std::make_unique<AddWithCarryAAndImmediate>(to_number_8_bit(sourceToken));
        default: break;
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

