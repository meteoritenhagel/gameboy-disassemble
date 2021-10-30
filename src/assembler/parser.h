#ifndef GAMEBOY_DISASSEMBLE_PARSER_H
#define GAMEBOY_DISASSEMBLE_PARSER_H

#include "auxiliary.h"
#include "numericfromtoken.h"
#include "tokenizer.h"
#include "unresolvedinstruction.h"
#include "../instructions/instructions.h"

#include "pretty_format.h"

#include <functional>
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
    using SymbolToNumeric = std::map<std::string, NumericFromToken>;
    using Address = word;
    using TokenVectorPosition = size_t;
    using ReturnedInstruction = std::function<InstructionPtr(void)>;

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
        const std::vector<UnresolvedInstructionPtr> unresolvedInstructions = std::move(pre_parse());
        return resolve_symbols(std::move(unresolvedInstructions));
    }

private:

    void symbol_emplace(const long number, const Token &token)
    {
        // TODO: change from map: string -> number
        //           to some map: string -> token
        if (token.get_token_type() == TokenType::GLOBAL_LABEL) {
            // since global labels have the form 'GLOBALLABEL:',
            // the trailing colon has to be removed
            _symbolicTable.emplace(remove_last_character(token.get_string()), NumericFromToken(number, token));
        } else {
            _symbolicTable.emplace(token.get_string(), NumericFromToken(number, token));
        }
    }

    /**
     * Looks up a token in the symbolic table and returns it if found.
     * @throws std::logic_error containing an error message and highlighted code passage in case of parsing error.
     * @param token token to look up in the symbolic table
     * @return the numeric value associated with the token
     */
    NumericFromToken symbol_lookup(const Token &token) const
    {
        try {
            return _symbolicTable.at(token.get_string());
        } catch (...) {
            throw_logic_error_and_highlight(token, "Parse error: Using the symbol \"" + token.get_string() + "\" which has not been assigned yet");
        }
    }

    /**
     * Takes a vector of UnresolvedInstructionPtr, resolves them and returns the vector of resolved instructions
     * @param unresolvedInstructions Vector of unresolved instructions
     * @return vector containing resolved instructions
     */
    InstructionVector resolve_symbols(const std::vector<UnresolvedInstructionPtr> &unresolvedInstructions) {
        InstructionVector resolvedInstructions(unresolvedInstructions.size());
        std::transform(unresolvedInstructions.cbegin(), unresolvedInstructions.cend(), resolvedInstructions.begin(),
                       [](const UnresolvedInstructionPtr &f) { return std::move(f->resolve()); });
        return resolvedInstructions;
    }

    /**
     * Builds a vector of unresolved instructions from the available tokens.
     * @throws std::logic_error containing an error message and highlighted code passage in case of parsing error.
     * @return Vector of unresolved instructions
     */
    std::vector<UnresolvedInstructionPtr> pre_parse() {
        std::vector<UnresolvedInstructionPtr> returnVector{};

        while (!is_finished()) {

            if (std::optional<UnresolvedInstructionPtr> unresolvedInstruction = parse_gameboy_instruction()) { // GameBoy instruction
                // if an error occurs while parsing, the instruction is not constructed
                // and the address is not incremented
                _currentAddress += unresolvedInstruction.value()->length();
                returnVector.push_back(std::move(unresolvedInstruction.value()));
                continue;
            }

            if (parse_assembler_specific_commands()) { continue; } // assembler-specific instruction
            if (update_label()) { continue; } // label

            throw_logic_error_and_highlight(read_current(), "Parse error: Found unknown expression '" +
                                            read_current().get_string() + "'.");
        }

        return returnVector;
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
        const Token currentToken = read_current();
        if (   currentToken.get_token_type() == TokenType::GLOBAL_LABEL
            || currentToken.get_token_type() == TokenType::LOCAL_LABEL) {
            // if current token is a label, update symbolic table and advance to next token
            _currentGlobalLabel = currentToken;
            symbol_emplace(_currentAddress, currentToken);
            increment_position();
        } else {
            return false;
        }

        // TODO: Really necessary to have end of context after newline?
        //       Do we even want the assembly code to end at a label?
        //       -> points to invalid position?!
        expect_end_of_context(fetch());
        return true;
    }

    /**
     * Checks if the next instruction is a GameBoy specific instruction, parses and returns it.
     * @return TODO
     */
    std::optional<UnresolvedInstructionPtr> parse_gameboy_instruction() {
        const Token firstTokenOfInstruction = read_current();
        const std::string currStr = to_upper(firstTokenOfInstruction.get_string());

        std::optional<UnresolvedInstructionPtr> instruction{};

//        try {
            if      (currStr == "ADD") { instruction = parse_add(); }
            else if (currStr == "ADC") { instruction = parse_adc(); }
            else if (currStr == "BIT") { instruction = parse_bit(); }
            else if (currStr == "INC") { instruction = parse_inc(); }
            else if (currStr == "DEC") { instruction = parse_dec(); }
            else if (currStr == "JP")  { instruction = parse_jp();  }
            else if (currStr == "JR")  { instruction = parse_jr();  }
            else if (currStr == "LD")  { instruction = parse_ld();  }
            else if (currStr == "LDI") { instruction = parse_ldi(); }
            else if (currStr == "LDD") { instruction = parse_ldd(); }
            else if (currStr == "LDH") { instruction = parse_ldh(); }
            else if (currStr == "LDHL"){ instruction = parse_ldhl();}

        if (instruction.has_value()) { // only check for end of context in case that an actual GameBoy instruction has been found
            expect_end_of_context(fetch());
        }

        return instruction;
    }

    /**
     * Parses "ADD" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_add();

    /**
     * Parses "ADC" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_adc();

    /**
     * Parses "BIT" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_bit();

    /**
     * Parses "INC" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_inc();

    /**
     * Parses "DEC" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_dec();

    /**
     * Parses "JP" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_jp();

    /**
     * Parses "JR" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_jr();

    /**
     * Parses "LD" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_ld();

    /**
     * Parses "LDI" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_ldi();

    /**
     * Parses "LDD" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_ldd();

    /**
     * Parses "LDH" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_ldh();

    /**
     * Parses "LDHL" commands
     * @return pointer to parsed instruction
     */
    UnresolvedInstructionPtr parse_ldhl();

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
    size_t get_current_token_position() const noexcept;

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

    // TODO: Documentation
    Token local_to_global(const Token &localLabel)
    {
        // For a local label depending on a global label we must ensure that the
        // contained string is changed to a global label 'GLOBALLABEL.LOCALLABEL'.
        if (_currentGlobalLabel.is_invalid())
            throw_logic_error_and_highlight(localLabel, "Parse error: Local label \"" + localLabel.get_string() + "\" has no parent global label");

        Token globalLabel(localLabel.get_line(), localLabel.get_column(), localLabel.get_token_type(), _currentGlobalLabel.get_string() + localLabel.get_string());
        return localLabel;
    }

    /**
     * Reads the token at position @param index in the token vector.
     * If i is not a feasible value, the very last token of the vector is returned.
     * If the currently read token is a local label, it is converted to a global label.
     * @param index index to read from
     * @return the retrieved token
     */
    Token read_token(const size_t index);

    /**
     * Reads the current token from the token vector.
     * If no tokens are left, the very last token of the vector is returned.
     * @return the retrieved token
     */
    Token read_current();

    /**
     * Reads the next current from the token vector.
     * If the next token would be outside the feasible range, returns the very last token of the vector.
     * @return the retrieved token
     */
    Token read_next();

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
     * Throws a logic error exception containing a string, in which the token is highlighted.
     * Additionally, the token @p referenceToken which is referenced by @p token is mentioned in the error message.
     * @throws std::logic_error
     * @param token the token to highlight
     * @param errorMessage an error message printed before the highlighted line
     */
    void throw_logic_error_and_highlight_with_reference(const Token &token, const Token &referenceToken, const std::string &errorMessage) const;

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
     * Tries to convert a token @p numToken into a long number fulfilling a certain condition.
     * @throws std::logic_error containing an error message and highlighted code
     * @param numToken token
     * @return the long number retrieved from @p numToken
     */
    long to_number_conditional(const Token &numToken, const std::function<bool(long)> &condition, const std::string &errorStr) const;

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
     * Calculates the relative offset in bytes between the @p positionToken (e.g. a local or global label)
     * and the @p referenceAddress. Then, this offset is tried to be converted to a signed 8-bit number.
     * @throws std::logic_error containing an error message and highlighted code
     * @param positionToken token indicating the position
     * @param referenceAddress the reference address to which the offset is calculated
     * @return the signed 8-bit offset retrieved from the distance between the token and the reference address
     */
    byte to_relative_offset(const Token &positionToken, const size_t referenceAddress) const;

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
};


#endif //GAMEBOY_DISASSEMBLE_PARSER_H
