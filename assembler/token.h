#ifndef GAMEBOY_DISASSEMBLE_TOKEN_H
#define GAMEBOY_DISASSEMBLE_TOKEN_H

#include "../instructions/auxiliary_and_conversions.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

/**
 * Enumerator for all token types. Used for parsing.
 */
enum class TokenType {
    IDENTIFIER,
    COMMA,
    NUMBER,
    ADDRESS,
    END_OF_LINE,
    END_OF_FILE,
    GLOBAL_LABEL,
    LOCAL_LABEL,
    INVALID
};

/**
 * Returns a string representation of the corresponding token type,
 * i.e. to_string(TokenType::IDENTIFIER) = "IDENTIFIER"
 *
 * @param tokenType token type
 * @return string representation of @p tokenType
 */
std::string to_string(const TokenType tokenType);

class Token;
using VectorOfTokens = std::vector<Token>;

/**
 * Class Token. Used as "smallest unit" in the parsing process.
 * A token may be of certain types, i.e. representing an identifier,
 * a number or the end of a line in source code.
 */
class Token{
public:

    /**
     * Default constructor
     */
    Token() = default;

    /**
     * Constructor. Initializes the token with its properties, i.e. position in source code, token type etc.
     * @param lineNumber line number
     * @param columnNumber column number
     * @param tokenType
     * @param tokenString
     */
    Token(const size_t lineNumber, const size_t columnNumber, const TokenType tokenType, const std::string &tokenString);

    /**
     * Checks whether the token contains a numeric value.
     * @return true if the token returns a numeric value
     */
    bool has_numeric_value() const;

    /**
     * Returns the token's line position.
     * @return line position
     */
    size_t get_line() const;

    /**
     * Returns the token's column position.
     * @return column position
     */
    size_t get_column() const;

    /**
     * Returns the token's type.
     * @return token type
     */
    TokenType get_token_type() const;

    /**
     * Returns the token's string.
     * @return token string
     */
    std::string get_string() const;

    /**
     * Tries to retrieve an optional numeric value,
     * which should always exists if and only if
     * the token type is NUMBER or ADDRESS.
     *
     * @throws std::bad_optional_access if the token contains no numeric value
     * @return
     */
    long get_numeric() const;

    /**
     * Returns the token position in the form lineNumber:columnNumber
     * @return string representation of token position
     */
    std::string get_position_string() const;

private:
    size_t _lineNumber{0}; ///< line position in source code
    size_t _columnNumber{0}; ///< column position in source code
    TokenType _tokenType{TokenType::INVALID}; ///< token type
    std::string _tokenString{}; ///< the string from which the token has been constructed
    std::optional<long> _numericValue{}; ///< the token's numeric value, if it exists
};

#endif //GAMEBOY_DISASSEMBLE_TOKEN_H
