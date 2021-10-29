#ifndef GAMEBOY_DISASSEMBLE_NUMERICFROMTOKEN_H
#define GAMEBOY_DISASSEMBLE_NUMERICFROMTOKEN_H

#include "token.h"

/**
 * Class NumericFromToken. Used for encapsulating a token with an associated value, so that
 * it can easily be placed into the symbolic lookup table. Instead of only taking the associated long value,
 * the token is saved in order to allow for more specific error messages when an exception is thrown.
 */
class NumericFromToken {
public:

    /**
     * Default constructor
     * @param numeric Numeric value associated with the token @token
     * @param token the token
     */
    NumericFromToken(const long numeric, const Token &token)
    : _numeric(numeric), _token(token) {}

    /**
     * Returns the current instance's numeric value.
     * @return numeric value
     */
    long get_numeric() const
    {
        return _numeric;
    }

    /**
     * Returns the current instance's Token
     * @return token
     */
    Token get_token() const
    {
        return _token;
    }

private:
    long _numeric; ///< the numeric value associated with the token
    Token _token; ///< the token, saved to provide additional information in case of an error
};

#endif //GAMEBOY_DISASSEMBLE_NUMERICFROMTOKEN_H
