#ifndef GAMEBOY_DISASSEMBLE_TOKENIZER_H
#define GAMEBOY_DISASSEMBLE_TOKENIZER_H

#include "auxiliary.h"
#include "pretty_format.h"
#include "token.h"

#include <iostream>
#include <string>
#include <vector>

const char CHAR_EOF = 0x04;

/** Class Tokenizer. Takes GameBoy assembly source code and returns
 *  tokens one by one.
 *
 *  In case of a lexical error, a std::logic_error containing a string with
 *  the highlighted source code and an error message is thrown.
 */
class Tokenizer
{
public:

    /**
     * Constructor.
     * @param code Source code which should be tokenized / lexically analyzed.
     * @param startingPosition starting position in the code.
     */
    Tokenizer(const std::string &code, const size_t startingPosition = 0);

    Tokenizer(const Tokenizer&) = default;
    Tokenizer(Tokenizer&&) = default;
    Tokenizer& operator=(const Tokenizer&) = default;
    Tokenizer& operator=(Tokenizer&&) = default;

    /**
     * Tokenize the source code from @p _startingPosition to the end.
     * @return Vector of all tokens
     */
    TokenVector tokenize();

    /**
     * Returns a const reference to the source code.
     * @return const reference to source code.
     */
    const std::string& get_code() const noexcept;

private:
    /**
     * Returns next token from source code.
     *
     * @throws std::logic_error containing an error message and the
     * highlighted code passage in case of lexical error.
     * @return next token
     */
    Token get_next_token();

    /**
     * Checks whether the current position in outside the source code.
     * @return true if no characters are left
     */
    bool is_out_of_range() const noexcept;

    /**
     * Tokenizes characters to an IDENTIFIER or GLOBAL_LABEL token.
     * @return IDENTIFIER or GLOBAL_LABEL token
     */
    Token tokenize_identifier_or_global_label();

    /**
    * Tokenizes characters to a NUMBER token.
    * @return NUMBER token
    */
    Token tokenize_number();

    /**
    * Tokenizes characters to an ADDRESS token.
    * @return ADDRESS token
    */
    Token tokenize_address();

    /**
     * Tokenizes characters to a LOCAL_LABEL token.
     * @return LOCAL_LABEL token
     */
    Token tokenize_local_label();

    /**
     * Tokenizes characters to an SP_SHIFTED token.
     * @return SP_SHIFTED token
     */
    Token tokenize_sp_shifted();

    /**
    * Tokenizes characters to a END_OF_LINE token.
    * @return END_OF_LINE token
    */
    Token tokenize_end_of_line();

    /**
     * If possible, advances to the next character of the source code.
     * Else, do nothing.
     */
    void increment_position() noexcept;

    /**
     * Increases the line counter.
     */
    void increment_linecount() noexcept;

    /**
     * Reads the character in the code at position @param index.
     * If already out of range, return CHAR_EOF.
     * @param index index to read from
     * @return current character
     */
    char read_char(const size_t index) const noexcept;

    /**
     * Reads the character to which the tokenizer is currently pointing.
     * If already out of range, return CHAR_EOF.
     * @return current character
     */
    char read_current() const noexcept;

    /**
     * Read the next character without incrementing the position counter.
     * If already out of range, return CHAR_EOF.
     * @return next character
     */
    char read_next() const noexcept;

    /**
     * Reads the next character by incrementing the position counter.
     * If already out of range, return CHAR_EOF.
     * @return next character
     */
    char fetch() noexcept;

    /**
     * Advances to the next expectedCharacter by incrementing the position counter
     * and throws an error if the expectedCharacter is not the expected expectedCharacter.
     * @throws std::logic_error containing the error message and the highlighted line of source code.
     *
     * @param expectedCharacter expected character
     * @return expected character in case of success
     */
    char fetch_and_expect(const char expectedCharacter);

    /**
     * Advance position counter until no whitespace symbol (except new line character) is found.
     */
    void ignore_whitespace() noexcept;

    /**
     * Advance position counter until the end of the current line.
     */
    void ignore_until_end_of_line();

    /**
     * Returns current line position.
     * @return current line position
     */
    size_t get_line() const;

    /**
     * Returns current column position.
     * @return current column position
     */
    size_t get_column() const;

    /**
     * Returns the current position in the form lineNumber:columnNumber
     * @return string representation of token position
     */
    std::string get_position_string();

    void throw_logic_error_and_highlight(const size_t lineNumber, const size_t columnNumber, const std::string& errorMessage);

    /**
     * Tries to create a new token with the following properties.
     * In case of an error,
     * @throw std::logic_error containing an error message and the highlighted line of source code
     *
     * @param lineNumber line number
     * @param columnNumber column number
     * @param tokenType token type
     * @param tokenString token string
     * @return Token if successful
     */
    Token try_to_create_token(const size_t lineNumber, const size_t columnNumber, const TokenType tokenType, const std::string &tokenString);

    std::string _code{}; ///< source code used for lexical analysis
    size_t _currentPosition{0}; ///< current position in source code
    size_t _lineCount{0}; ///< line counter, i.e. the line the tokenizer currently operates in
    size_t _currentLineStart{0}; ///< the position of the character starting the current line
};

#endif //GAMEBOY_DISASSEMBLE_TOKENIZER_H
