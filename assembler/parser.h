#ifndef GAMEBOY_DISASSEMBLE_PARSER_H
#define GAMEBOY_DISASSEMBLE_PARSER_H

#include "auxiliiary.h"
#include "tokenizer.h"
#include "../instructions/instructions.h"

#include "pretty_format.h"

/**
 * Class Parser. Used for parsing tokens which are provided by a tokenizer.
 * This tokenizer is passed via dependency injection.
 *
 * In case of a parsing error, a std::logic_error containing a string with
 * the highlighted source code and an error message is thrown.
 */
class Parser {
public:
    /**
     * Default constructor
     * @param tokenizer tokenizer which is needed for retrieving the tokens
     */
    Parser(const Tokenizer& tokenizer)
    : _tokenizer(tokenizer)
    {}

    /**
     * Checks whether the parsing process has ended, i.e. no tokens are left.
     * @return true if no tokens are left
     */
    bool is_finished() const noexcept
    {
        return _tokenizer.is_finished();
    }

    /**
     * Parses the next instruction.
     * Tokens are retrieved from Tokenizer _tokenizer.
     *
     * @throws std::logic_error containing an error message and the
     * highlighted code passage in case of parsing error.
     * @return pointer to the parsed instruction
     */
    InstructionPtr parse_next_instruction()
    {
        // All valid commands must start with an identifier
        const Token currentToken = fetch_and_expect(TokenType::IDENTIFIER);

        const std::string currStr = currentToken.get_string();

        InstructionPtr instruction;

        if      (currStr == "ADD") { instruction = parse_add(); }
        else if (currStr == "ADC") { instruction = parse_adc(); }
        else if (currStr == "BIT") { instruction = parse_bit(); }

        expect_end_of_context(fetch()); // each valid instruction must end with newline or end of file

        return instruction;
    }

private:

    /**
     * Parses "ADD" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_add();

    /**
     * Parses "ADC" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_adc();

    /**
     * Parses "ADC" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_bit();

    /**
     * Fetches the next token from the tokenizer.
     * @throws std::logic_error if lexical analysis failed.
     * @return the retrieved token
     */
    Token fetch()
    {
        return _tokenizer.get_next_token();
    }

    /**
     * Fetches the next token from the tokenizer.
     * This token is expected to be of type @p expectedType.
     *
     * @throws std::logic_error if token is not of @p expectedType.
     * @return the retrieved token
     */
    Token fetch_and_expect(const TokenType expectedType)
    {
        const Token tkn = fetch();
        expect_type(tkn, expectedType);
        return tkn;
    }

    /**
     * Returns the source code from which the tokens are generated.
     * @return const reference to the source code
     */
    const std::string& get_code() const noexcept {
        return _tokenizer.get_code();
    }

    /**
     * Throws a logic error containing a string, in which the token is highlighted.
     *
     * @param token the token to highlight
     * @param errorMessage an error message printed before the highlighted line
     */
    void throw_logic_error_and_highlight(const Token &token, const std::string &errorMessage);

    /**
     * Tries to convert a Token @p numToken into an 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the 8-bit number retrieved from @p numToken
     */
    byte to_number_8_bit(const Token &numToken);

    /**
     * Tries to convert a Token @p numToken into an unsigned 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the unsigned 8-bit number retrieved from @p numToken
     */
    byte to_unsigned_number_8_bit(const Token &numToken);

    /**
     * Tries to convert a Token @p numToken into a signed 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the signed 8-bit number retrieved from @p numToken
     */
    byte to_signed_number_8_bit(const Token &numToken);

    /**
     * Tries to convert a Token @p numToken into a 16-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the 16-bit number retrieved from @p numToken
     */
    long to_number_16_bit(const Token &numToken);

    /**
     * Tries to convert a Token @p numToken into an unsigned 16-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the unsigned 16-bit number retrieved from @p numToken
     */
    long to_unsigned_number_16_bit(const Token &numToken);

    /**
     * Tries to convert a Token @p indexToken into a bit index (i.e. a number between 0 and 7).
     * @throws std::logic_error containing an error message and highlighted code
     * @param indexToken token
     * @return the bit index retrieved from @p numToken
     */
    byte to_index(const Token &indexToken);

    /**
     * Tries to convert a Token @p token into a GameBoy register.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the register retrieved from @p numToken
     */
    Register to_register(const Token &token);

    /**
     * Tries to convert a Token @p numToken into an 8-bit register.
     * @throws std::logic_error containing an error message and highlighted code
     * @param token token
     * @return the 8-bit register retrieved from @p token
     */
    Register8Bit to_register_8_bit(const Token& token);

    /**
     * Tries to convert a Token @p numToken into a 16-bit register.
     * @throws std::logic_error containing an error message and highlighted code
     * @param token token
     * @return the 16-bit register retrieved from @p token
     */
    Register16Bit to_register_16_bit(const Token& token);

    /**
     * Tries to convert a Token @p numToken into the register @p reg.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return @p reg in case of success
     */
    Register to_register_expect(const Token &token, const Register &reg);

    /**
     * Checks if the token @p token is of type @p expected type and throws an error otherwise.
     *
     * @throws std::logic_error containing an error message and the line of code with the token highlighted
     *
     * @param token the token to highlight
     * @param expectedType the expected token type
     */
    void expect_type(const Token& token, const TokenType expectedType);

    /**
     * Checks if the token @p token is either of type TokenType::END_OF_LINE or TokenType::END_OF_LINE.
     *
     * @throws std::logic_error containing an error message and the line of code with the token highlighted
     *
     * @param token the token which is expected to be of end-of-context type.
     */
    void expect_end_of_context(const Token& token);

    Tokenizer _tokenizer; ///< the tokenizer used to get the tokens for parsing individually
};


#endif //GAMEBOY_DISASSEMBLE_PARSER_H
