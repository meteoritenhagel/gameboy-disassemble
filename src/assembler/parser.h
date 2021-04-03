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

    /**
     * Parses the _tokenVector and returns the _instructionVector by moving.
     * This invalidates the current _instructionVector, as ownership is passed
     * to the outside of the class.
     * @throws std::logic_error containing an error message and highlighted code
     * @return vector of parsed instructions
     */
    InstructionVector parse() {
        build_symbol_table();
        //reparse_missing_symbols();

        return std::move(_instructionVector);
    }

private:

    void build_symbol_table() {
        while (!is_finished()) {

            if (std::optional<InstructionPtr> instruction = parse_gameboy_instruction()) { // GameBoy instruction
                // if an error occurs while parsing, the instruction is not constructed
                // and the address is not incremented
                _currentAddress += get_length(instruction.value());
                _instructionVector.push_back(std::move(*instruction)); // accesses value of std::optional
                continue;
            }

            if (parse_assembler_specific_commands()) { continue; } // assembler-specific instruction
            if (update_label()) { continue; } // label

            throw_logic_error_and_highlight(read_current(), "Parse error: Found unknown expression '" +
                                            read_current().get_string() + "'.");
        }
    }

    /**
     * Checks whether the current group of tokens are assembler specific commands,
     * (i.e. only changing the state of the parser without being actual GameBoy CPU commands,
     * e.g. EQU) and executes them.
     * @throws std::logic_error containing an error message and highlighted code passage in case of parsing error.
     */
    bool parse_assembler_specific_commands() {
        if (read_next().get_string() == "EQU") { parse_equ(); }
        else { return false; }

        expect_end_of_context(fetch()); // each valid instruction must end with newline or end of file
        return true;
    }

    /**
     * Checks whether the current token is a global or local label
     * and adds the corresponding symbol to the _symbolTable.
     * @throws std::logic_error containing an error message and highlighted code passage in case of parsing error.
     */
    bool update_label() {
        if (read_current().get_token_type() == TokenType::GLOBAL_LABEL)
        { // if global label, update symbolic table and advance to next token
            _currentGlobalLabel = read_current();
            _symbolicTable.emplace(remove_last_character(_currentGlobalLabel.get_string()), _currentAddress);
            increment_position();

        }
        else { return false; }

        expect_end_of_context(fetch());
        return true;
    }

    /**
     * Checks if the next instruction is a GameBoy specific instruction, parses and returns it.
     * @return an optional containing the currently parsed GameBoy CPU instruction if found, or an empty optional.
     */
    std::optional<InstructionPtr> parse_gameboy_instruction() {
        const Token currentToken = read_current();
        const std::string currStr = currentToken.get_string();

        std::optional<InstructionPtr> instruction{};

        if      (to_upper(currStr) == "ADD") { instruction = parse_add(); }
        else if (to_upper(currStr) == "ADC") { instruction = parse_adc(); }
        else if (to_upper(currStr) == "BIT") { instruction = parse_bit(); }
        else if (to_upper(currStr) == "INC") { instruction = parse_inc(); }
        else if (to_upper(currStr) == "DEC") { instruction = parse_dec(); }
        else if (to_upper(currStr) == "JP")  { instruction = parse_jp();  }
        else                                 { return instruction; } // in case of no match we want to go on without checking for end_of_context

        expect_end_of_context(fetch());
        return instruction;
    }

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
     * Parses "BIT" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_bit();

    /**
     * Parses "INC" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_inc();

    /**
     * Parses "DEC" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_dec();

    /**
     * Parses "JP" commands
     * @return pointer to parsed instruction
     */
    InstructionPtr parse_jp();

    /**
     * Parses "EQU" commands specific to the assembler.
     * @return pointer to parsed instruction
     */
    void parse_equ();

    /**
     * Checks whether all tokens have already been consumed
     * @return true if there are no tokens left to parse.
     */
    bool is_finished() const noexcept;

    /**
     * Returns the current position in the token vector.
     * @return current position in the token vector
     */
    size_t get_current_position() const noexcept;

    /**
     * Increments the current position in the token vector,
     * but only if there are still tokens left.
     * Otherwise, nothing happens.
     */
    void increment_position();

    /**
     * Resets the current token to be the first one in the token vector.
     */
    void reset() noexcept;

    /**
     * Reads the current from the tokenizer.
     * If no tokens are left, the very last token of the vector is returned.
     * @return the retrieved token
     */
    Token read_current() const;

    /**
     * Reads the next current from the tokenizer.
     * If the next token would be outside the feasible range, returns the very last token of the vector.
     * @return the retrieved token
     */
    Token read_next() const;

    /**
     * Fetches the next token from the tokenizer, i.e. reads the token and advances the position to the next token.
     * @throws std::range_error if no tokens are left.
     * @return the retrieved token
     */
    Token fetch();

    /**
     * Fetches the next token from the tokenizer.
     * This token is expected to be of type @p expectedType.
     * @throws std::logic_error if token is not of @p expectedType.
     * @tparam T either TokenType or std::vector<TokenType>
     * @param expectedTypes expected token type(s)
     * @return the retrieved token
     */
    template<typename T>
    Token fetch_and_expect(const T expectedTypes);

    /**
     * Fetches the next token from the tokenizer.
     * This token is expected to be one of the types @p expectedTypes.
     * @throws std::logic_error if token is not of @p expectedTypes.
     * @param expectedTypes expected types
     * @return the retrieved token
     */
    Token fetch_and_expect(const std::vector<TokenType> expectedTypes);

    /**
     * Returns the source code from which the tokens are generated.
     * @return const reference to the source code
     */
    const std::string& get_code() const noexcept;

    /**
     * Throws a logic error exception containing a string, in which the token is highlighted.
     * @throws std::logic_error
     * @param token the token to highlight
     * @param errorMessage an error message printed before the highlighted line
     */
    void throw_logic_error_and_highlight(const Token &token, const std::string &errorMessage) const;

    /**
     * Throws an invalid argument exception containing a string, in which the token is highlighted.
     * This should be used for failed symbol resolution only.
     * @throws std::invalid_argument
     * @param token the token to highlight
     * @param errorMessage an error message printed before the highlighted line
     */
    void throw_invalid_argument_and_highlight(const Token &token, const std::string &errorMessage) const;

    /**
     * Tries to convert a token @p numToken into a long number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the long number retrieved from @p numToken
     */
    long to_number(const Token &numToken) const;

    /**
     * Tries to convert a token @p numToken into an 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the 8-bit number retrieved from @p numToken
     */
    byte to_number_8_bit(const Token &numToken) const;

    /**
     * Tries to convert a token @p numToken into an unsigned 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the unsigned 8-bit number retrieved from @p numToken
     */
    byte to_unsigned_number_8_bit(const Token &numToken) const;

    /**
     * Tries to convert a token @p numToken into a signed 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the signed 8-bit number retrieved from @p numToken
     */
    byte to_signed_number_8_bit(const Token &numToken) const;

    /**
     * Tries to convert a token @p numToken into a 16-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the 16-bit number retrieved from @p numToken
     */
    long to_number_16_bit(const Token &numToken) const;

    /**
     * Tries to convert a token @p numToken into an unsigned 16-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the unsigned 16-bit number retrieved from @p numToken
     */
    long to_unsigned_number_16_bit(const Token &numToken) const;

    /**
     * Tries to convert a token @p indexToken into a bit index (i.e. a number between 0 and 7).
     * @throws std::logic_error containing an error message and highlighted code
     * @param indexToken token
     * @return the bit index retrieved from @p numToken
     */
    byte to_index(const Token &indexToken) const;

    /**
     * Tries to convert a token @p conditionToken into a flag condition (i.e. NZ, Z, C, or NC)
     * @throws std::logic_error containing an error message and highlighted code
     * @param conditionToken token
     * @return the flag condition retrieved from @p conditionToken
     */
    FlagCondition to_flag_condition(const Token &conditionToken) const;

    /**
     * Tries to convert a token @p token into a GameBoy register.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the register retrieved from @p numToken
     */
    Register to_register(const Token &token) const;

    /**
     * Tries to convert a token @p numToken into an 8-bit register.
     * @throws std::logic_error containing an error message and highlighted code
     * @param token token
     * @return the 8-bit register retrieved from @p token
     */
    Register8Bit to_register_8_bit(const Token& token) const;

    /**
     * Tries to convert a token @p numToken into a 16-bit register.
     * @throws std::logic_error containing an error message and highlighted code
     * @param token token
     * @return the 16-bit register retrieved from @p token
     */
    Register16Bit to_register_16_bit(const Token& token) const;

    /**
     * Tries to convert a token @p numToken into the register @p reg.
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

    std::string _code{}; ///< the code which was used to generate the tokens
    TokenVector _tokenVector{}; ///< the tokens which are parsed by the parser

    size_t _currentTokenPosition{}; ///< the position of the current token in _tokenVector
    Address _currentAddress{0}; ///< the bytecode address of the current instruction
    Token _currentGlobalLabel{}; ///< the currently active global label. Is used for resolving the local labels.

    SymbolToNumeric _symbolicTable{}; ///< symbolic table, which contains all symbols, labels etc.
    InstructionVector _instructionVector{}; ///< InstructionVector, which is built and returned by parse()
};


#endif //GAMEBOY_DISASSEMBLE_PARSER_H
