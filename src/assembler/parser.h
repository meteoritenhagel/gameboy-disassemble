#ifndef GAMEBOY_DISASSEMBLE_PARSER_H
#define GAMEBOY_DISASSEMBLE_PARSER_H

#include "auxiliary.h"
#include "tokenizer.h"
#include "../instructions/instructions.h"

#include "pretty_format.h"

#include <map>

/**
 * Class Parser. Used for parsing tokens which are provided by a tokenizer.
 * This tokenizer is passed via dependency injection.
 *
 * In case of a parsing error, a std::logic_error containing a string with
 * the highlighted source code and an error message is thrown.
 */
class Parser {
public:

    using SymbolToNumeric = std::map<std::string, long>;

    using Address = word;
    using TokenVectorPosition = size_t;

    /**
     * Default constructor
     * @param tokenizer tokenizer which is needed for retrieving the tokens
     */
    Parser(const std::string &code, const TokenVector& tokenVector)
    : _code(code),
      _tokenVector(tokenVector)
    {}

    InstructionVector parse() {
        InstructionVector instructionVector;

        Address currentAddress = 0;

        while (!is_finished()) {
            if (read_next().get_string() == "EQU") // if assembler-specific command EQU is found
            {
                parse_equ();
                expect_end_of_context(fetch());
                continue;
            }

            if (read_current().get_token_type() == TokenType::GLOBAL_LABEL)
            { // if global label, update symbolic table and advance to next token
                _symbolicTable.emplace(read_current().get_string(), currentAddress);
                increment_position();
                continue;
            }

            try { // to parse GameBoy instruction
                InstructionPtr currentInstruction = parse_next_instruction();
                // if an error occurs while parsing, the instruction is not constructed
                // and the address is not incremented
                currentAddress += get_length(currentInstruction);
                instructionVector.push_back(std::move(currentInstruction));
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
            }
        }

        return instructionVector;
    }

    /**
     * Parses the next instruction.
     * Tokens are retrieved from Tokenizer _tokenVector.
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

        if      (currStr == "add") { instruction = parse_add(); }
        else if (currStr == "adc") { instruction = parse_adc(); }
        else if (currStr == "bit") { instruction = parse_bit(); }
        // no feasible case was detected
        else { instruction = std::make_unique<Unknown>(); }

        expect_end_of_context(fetch()); // each valid instruction must end with newline or end of file

        return instruction;
    }

private:

    /**
     * Parses "add" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_add();

    /**
     * Parses "adc" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_adc();

    /**
     * Parses "bit" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_bit();

    /**
     * Parses "EQU" commands specific to the assembler.
     * @return pointer to parsed instruction
     */
    void parse_equ();

    /**
     * Checks whether all tokens have already been consumed
     * @return true if there are no tokens left to parse.
     */
    bool is_finished() const noexcept
    {
        return (_currentPosition >= _tokenVector.size());
    }

    /**
     * Returns the current position in the token vector.
     * @return current position in the token vector
     */
    size_t get_current_position() const noexcept {
        return _currentPosition;
    }

    /**
     * Increments the current position in the token vector,
     * but only if there are still tokens left.
     * Otherwise, nothing happens.
     */
    void increment_position() {
        if (!is_finished())
        {
            ++_currentPosition;
        }
    }

    /**
     * Resets the current token to be the first one in the token vector.
     */
    void reset() noexcept
    {
        _currentPosition = 0;
    }

    /**
     * Reads the current from the tokenizer.
     * If no tokens are left, the very last token of the vector is returned.
     * @return the retrieved token
     */
    Token read_current() const
    {
        if (get_current_position() < _tokenVector.size()) {
            return _tokenVector.at(get_current_position());
        } else {
            return _tokenVector.at(_tokenVector.size() - 1);
        }
    }

    /**
     * Reads the next current from the tokenizer.
     * If the next token would be outside the feasible range, returns the very last token of the vector.
     * @return the retrieved token
     */
    Token read_next() const
    {
        if (get_current_position() < _tokenVector.size() - 1) {
            return _tokenVector.at(get_current_position() + 1);
        } else {
            return _tokenVector.at(_tokenVector.size() - 1);
        }
    }

    /**
     * Fetches the next token from the tokenizer, i.e. reads the token and advances the position to the next token.
     * @throws std::range_error if no tokens are left.
     * @return the retrieved token
     */
    Token fetch()
    {
        const Token currentToken = read_current();
        increment_position();
        return currentToken;
    }

    /**
     * Fetches the next token from the tokenizer.
     * This token is expected to be of type @p expectedType.
     * @throws std::logic_error if token is not of @p expectedType.
     * @tparam T either TokenType or std::vector<TokenType>
     * @param expectedTypes expected token type(s)
     * @return the retrieved token
     */
    template<typename T>
    Token fetch_and_expect(const T expectedTypes)
    {
        const Token tkn = fetch();
        expect_type(tkn, expectedTypes);
        return tkn;
    }

    /**
     * Fetches the next token from the tokenizer.
     * This token is expected to be one of the types @p expectedTypes.
     * @throws std::logic_error if token is not of @p expectedTypes.
     * @param expectedTypes expected types
     * @return the retrieved token
     */
    Token fetch_and_expect(const std::vector<TokenType> expectedTypes)
    {
        const Token tkn = fetch();
        expect_type(tkn, expectedTypes);
        return tkn;
    }

    /**
     * Returns the source code from which the tokens are generated.
     * @return const reference to the source code
     */
    const std::string& get_code() const noexcept {
        return _code;
    }

//    /**
//     * Returns the bytecode address of the current instruction.
//     * @return address of current instruction
//     */
//    Address get_current_address() const {
//        return _currentAddress;
//    }

    /**
     * Throws a logic error containing a string, in which the token is highlighted.
     *
     * @param token the token to highlight
     * @param errorMessage an error message printed before the highlighted line
     */
    void throw_logic_error_and_highlight(const Token &token, const std::string &errorMessage) const;

    /**
     * Tries to convert a Token @p numToken into a long number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the long number retrieved from @p numToken
     */
    long to_number(const Token &numToken) const;

    /**
     * Tries to convert a Token @p numToken into an 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the 8-bit number retrieved from @p numToken
     */
    byte to_number_8_bit(const Token &numToken) const;

    /**
     * Tries to convert a Token @p numToken into an unsigned 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the unsigned 8-bit number retrieved from @p numToken
     */
    byte to_unsigned_number_8_bit(const Token &numToken) const;

    /**
     * Tries to convert a Token @p numToken into a signed 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the signed 8-bit number retrieved from @p numToken
     */
    byte to_signed_number_8_bit(const Token &numToken) const;

    /**
     * Tries to convert a Token @p numToken into a 16-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the 16-bit number retrieved from @p numToken
     */
    long to_number_16_bit(const Token &numToken) const;

    /**
     * Tries to convert a Token @p numToken into an unsigned 16-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the unsigned 16-bit number retrieved from @p numToken
     */
    long to_unsigned_number_16_bit(const Token &numToken) const;

    /**
     * Tries to convert a Token @p indexToken into a bit index (i.e. a number between 0 and 7).
     * @throws std::logic_error containing an error message and highlighted code
     * @param indexToken token
     * @return the bit index retrieved from @p numToken
     */
    byte to_index(const Token &indexToken) const;

    /**
     * Tries to convert a Token @p token into a GameBoy register.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the register retrieved from @p numToken
     */
    Register to_register(const Token &token) const;

    /**
     * Tries to convert a Token @p numToken into an 8-bit register.
     * @throws std::logic_error containing an error message and highlighted code
     * @param token token
     * @return the 8-bit register retrieved from @p token
     */
    Register8Bit to_register_8_bit(const Token& token) const;

    /**
     * Tries to convert a Token @p numToken into a 16-bit register.
     * @throws std::logic_error containing an error message and highlighted code
     * @param token token
     * @return the 16-bit register retrieved from @p token
     */
    Register16Bit to_register_16_bit(const Token& token) const;

    /**
     * Tries to convert a Token @p numToken into the register @p reg.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return @p reg in case of success
     */
    Register to_register_expect(const Token &token, const Register &reg) const;

    /**
     * Checks if the token @p token is of type @p expectedType and throws an error otherwise.
     *
     * @throws std::logic_error containing an error message and the line of code with the token highlighted
     *
     * @param token the token to investigate
     * @param expectedType the expected token type
     */
    void expect_type(const Token& token, const TokenType expectedType) const;

    /**
     * Checks if the token @p token is of one of the types in @p expectedTypes and throws an error otherwise.
     *
     * @throws std::logic_error containing an error message and the line of code with the token highlighted
     *
     * @param token the token to investigate
     * @param expectedTypes the vector of expected token types
     */
    void expect_type(const Token& token, const std::vector<TokenType> expectedTypes) const;

    /**
     * Checks if the token @p token contains the string @p expectedString and throws an error otherwise.
     *
     * @throws std::logic_error containing an error message and the line of code with the token highlighted
     *
     * @param token the token to investigate
     * @param expectedType the expected token type
     */
    void expect_string(const Token& token, const std::string &expectedString) const;

    /**
     * Checks if the token @p token contains one of the strings in @p expectedStrings and throws an error otherwise.
     *
     * @throws std::logic_error containing an error message and the line of code with the token highlighted
     *
     * @param token the token to investigate
     * @param expectedTypes the vector of expected token types
     */
    void expect_string(const Token& token, const std::vector<std::string> &expectedStrings) const;

    /**
     * Checks if the token @p token is either of type TokenType::END_OF_LINE or TokenType::END_OF_LINE.
     *
     * @throws std::logic_error containing an error message and the line of code with the token highlighted
     *
     * @param token the token which is expected to be of end-of-context type.
     */
    void expect_end_of_context(const Token& token) const;

    std::string _code; ///< the code which was used to generate the tokens
    TokenVector _tokenVector; ///< the tokens which are parsed by the parser
    size_t _currentPosition{}; ///< the position of the current token

    SymbolToNumeric _symbolicTable{};
};


#endif //GAMEBOY_DISASSEMBLE_PARSER_H
