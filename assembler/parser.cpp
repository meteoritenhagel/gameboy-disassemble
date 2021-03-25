#include "parser.h"

void Parser::throw_logic_error_and_highlight(const Token &token, const std::string &errorMessage)
{
    ::throw_logic_error_and_highlight(get_code(), token.get_line(), token.get_column(), errorMessage, token.get_string().size());
}

byte Parser::to_number_8_bit(const Token &numToken) {
    const long num = numToken.get_numeric();
    if (!is_8_bit(num))
    {
        throw_logic_error_and_highlight(numToken, "Parse error: Number " + std::to_string(num) + " is expected to be 8-bit");
    }
    return static_cast<byte>(num);
}

byte Parser::to_unsigned_number_8_bit(const Token &numToken) {
    const long num = numToken.get_numeric();
    if (!is_unsigned_8_bit(num))
    {
        throw_logic_error_and_highlight(numToken, "Parse error: Number " + std::to_string(num) + " is expected to be unsigned 8-bit");
    }
    return static_cast<byte>(num);
}

byte Parser::to_signed_number_8_bit(const Token &numToken) {
    const long num = numToken.get_numeric();
    if (!is_signed_8_bit(num))
    {
        throw_logic_error_and_highlight(numToken, "Parse error: Number " + std::to_string(num) + " is expected to be signed 8-bit");
    }
    return static_cast<byte>(num);
}

long Parser::to_number_16_bit(const Token &numToken) {
    const long num = numToken.get_numeric();
    if (!((-32768 <= num && num <= 32767) || (0 <= num && num <= 65535)))
    {
        throw_logic_error_and_highlight(numToken, "Parse error: Number " + std::to_string(num) + " is expected to be 16-bit");
    }
    return num;
}

long Parser::to_unsigned_number_16_bit(const Token &numToken) {
    const long num = numToken.get_numeric();
    if (!(is_signed_16_bit(num) || is_unsigned_16_bit(num)))
    {
        throw_logic_error_and_highlight(numToken, "Parse error: Number " + std::to_string(num) + " is expected to be 16-bit");
    }
    return num;
}


Register Parser::to_register(const Token &token) {
    const std::string str = token.get_string();
    if (!is_register(token))
    {
        throw_logic_error_and_highlight(token, "Parse error: Found expression \"" + str +
                                               "\" but expected register");
    }
    return ::to_register(str);
}

Register8Bit Parser::to_register_8_bit(const Token &token) {
    const std::string str = token.get_string();
    if (!is_register_8_bit(token))
    {
        throw_logic_error_and_highlight(token, "Parse error: Found expression \"" + str + "\" but expected 8-bit register");
    }
    return ::to_register_8_bit(::to_register(str));
}

Register16Bit Parser::to_register_16_bit(const Token &token) {
    const std::string str = token.get_string();
    if (!is_register_16_bit(token))
    {
        throw_logic_error_and_highlight(token, "Parse error: Found expression \"" + str + "\" but expected 16-bit register");
    }
    return ::to_register_16_bit(::to_register(str));
}

Register Parser::to_register_expect(const Token &token, const Register &reg) {
    const Register tokenRegister = to_register(token);

    if (tokenRegister != reg)
    {
        throw_logic_error_and_highlight(token, "Parse error: Found expression \"" + token.get_string() +
                                               "\" but expected register \"" + to_string(reg) + "\"");
    }
    return tokenRegister;
}

byte Parser::to_index(const Token &indexToken) {
    const long num = indexToken.get_numeric();
    if (!is_index(num))
    {
        throw_logic_error_and_highlight(indexToken, "Parse error: Found expression \"" + indexToken.get_string() +
                                                    "\" but expected index (0, ..., 7)");
    }
    return num;
}

void Parser::expect_type(const Token &token, const TokenType expectedType) {
    const TokenType currentType = token.get_token_type();
    if (currentType != expectedType)
    {
        throw_logic_error_and_highlight(token, "Parse error: Found \"" + to_string(currentType) +
                                               "\" but expected \"" + to_string(expectedType) + "\"");
    }
}

void Parser::expect_end_of_context(const Token &token) {
    const TokenType currentType = token.get_token_type();
    if (currentType != TokenType::END_OF_LINE && currentType != TokenType::END_OF_FILE)
    {
        throw_logic_error_and_highlight(token, "Parse error: Found \"" + to_string(currentType) + "\" but expected newline or end of file");
    }
}