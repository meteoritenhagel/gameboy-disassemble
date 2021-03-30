#ifndef GAMEBOY_DISASSEMBLE_AUXILIARY_AND_CONVERSIONS_H
#define GAMEBOY_DISASSEMBLE_AUXILIARY_AND_CONVERSIONS_H

#include "constants.h"

#include <string>

template<typename T>
using enable_if_is_integral = std::enable_if_t<std::is_integral_v<T>, bool>;

/**
 * Checks whether an integral number is negative by checking the most significant bit.
 *
 * @param number an integral number
 * @return true if @p number is negative
 */
template<typename T, enable_if_is_integral<T> = true>
bool is_negative(const T number);

/**
 * Checks whether an integral number is in the range of an unsigned 8-bit number.
 *
 * @param number an integral number
 * @return true if @p number is between 0 and 255
 */
template<typename T, enable_if_is_integral<T> = true>
bool is_unsigned_8_bit(const T number);


/**
 * Checks whether an integral number is in the range of a signed 8-bit number.
 *
 * @param number an integral number
 * @return true if @p number is between -128 and 127
 */
template<typename T, enable_if_is_integral<T> = true>
bool is_signed_8_bit(const T number);

/**
 * Checks whether an integral number is in the range of an 8-bit number.
 *
 * @param number an integral number
 * @return true if @p number is between -128 and 255
 */
template<typename T, enable_if_is_integral<T> = true>
bool is_8_bit(const T number);

/**
 * Checks whether an integral number is in the range of an unsigned 16-bit number.
 *
 * @param number an integral number
 * @return true if @p number is between 0 and 65535
 */
template<typename T, enable_if_is_integral<T> = true>
bool is_unsigned_16_bit(const T number);

/**
 * Checks whether an integral number is in the range of a signed 16-bit number.
 *
 * @param number an integral number
 * @return true if @p number is between -32768 and 32767
 */
template<typename T, enable_if_is_integral<T> = true>
bool is_signed_16_bit(const T number);

/**
 * Checks whether an integral number is in the range of a 16-bit number.
 *
 * @param number an integral number
 * @return true if @p number is between -32768 and 65535
 */
template<typename T, enable_if_is_integral<T> = true>
bool is_16_bit(const T number);

/**
 * Checks whether an integral number is between 0 and 7.
 *
 * @param number an integral number
 * @return true if @p number is between 0 and 7
 */
template<typename T, enable_if_is_integral<T> = true>
bool is_index(const T number);

/**
 * Calculates a number's two's complement.
 *
 * @param number an integral number
 * @return the two's complement of @p number
 */
template<typename T, enable_if_is_integral<T> = true>
T twos_complement(const T number);

/**
 * Converts an integral number @p number to its decimal string representation.
 *
 * I.e. to_string_hex(10) = "10"
 *
 * @param number a number
 * @return a string containing the decimal representation of @p number
 */
template<typename T>
std::string to_string_dec(const T number);

/**
 * Converts an integral number @p number to its hexadecimal string representation.
 *
 * I.e. to_string_hex(10)    = "0A"
 *      to_string_hex(10, 1) =  "A"
 *
 * @param number an integral number
 * @param digits number of digits to output in the string
 * @return a string containing the hexadecimal representation of @p number
 */
template<typename T, enable_if_is_integral<T> = true>
std::string to_string_hex(const T number, const byte digits = 2 * sizeof(T));

/**
 * Converts an integral number @p number to its hexadecimal string representation with prefix "0x".
 *
 * I.e. to_string_hex(10)    = "0x0A"
 *      to_string_hex(10, 1) =  "0xA"
 *
 * @param number a number
 * @return a string containing the prefixed hexadecimal representation of @p number
 */
template<typename T, enable_if_is_integral<T> = true>
std::string to_string_hex_prefixed(const T number, const byte digits = 2 * sizeof(T));

/**
 * Converts an integral number @p number to its signed and prefixed string representation with prefix "0x".
 *
 * I.e. for T = byte = uint8_t:
 *      to_string_hex(1)    =  "0x01"
 *      to_string_hex(255)  = "-0x01"
 *
 * @param number a number
 * @return a string containing the prefixed hexadecimal representation of @p number
 */
template<typename T, enable_if_is_integral<T> = true>
std::string to_string_hex_signed_prefixed(const T number, const byte digits = 2 * sizeof(T));

/**
 * Calculates a 16 bit number's least significant byte.
 *
 * @param wrd an integral 16-bit number
 * @return the least significant byte of @p word
 */
byte get_least_significant_byte(const word wrd);

/**
 * Calculates a 16 bit number's most significant byte.
 *
 * @param wrd an integral 16-bit number
 * @return the most significant byte of @p word
 */
byte get_most_significant_byte(const word wrd);

/**
 * Takes to consecutive bytes and interprets them to be of little endian format,
 * i.e. LSB first and then MSB.
 *
 * @param lsb least significant byte
 * @param msb most significant byte
 * @return the little endian representation of [msb, lsb]
 */
word little_endian_to_number(const byte lsb, const byte msb);

/**
 * Takes to consecutive bytes and interprets them to be of big endian format,
 * i.e. MSB first and then LSB.
 *
 * @param msb most significant byte
 * @param lsb least significant byte
 * @return the big endian representation of [msb, lsb]
 */
word big_endian_to_number(const byte msb, const byte lsb);

/**
 * Converts a signed 8-bit number into a signed 16-bit number with the same value.
 *
 * @param number a signed 8-bit number
 * @return the signed 16-bit number with the same value as @p number
 */
int16_t extend_sign(const int8_t number);

/**
 * Converts a 16-bit word into a bytestring of little endian format,
 * i.e. [LSB, MSB]
 *
 * @param wrd 16 bit word
 * @return the bytestring corresponding to @p wrd stored in little endian format
 */
Bytestring to_bytestring_little_endian(const word wrd);

/**
 * Converts a 16-bit word into a bytestring of big endian format,
 * i.e. [MSB, LSB]
 *
 * @param wrd 16 bit word
 * @return the bytestring corresponding to @p wrd stored in big endian format
 */
Bytestring to_bytestring_big_endian(const word wrd);

/**
 * Converts an 8 or 16-bit opcode to a bytestring.
 *
 * 8-bit opcodes get converted to a one-element bytestring containing the opcode,
 * and 16-bit opcodes get converted to a two-element bytestring in big endian format.
 *
 * I.e. 0x00XY -> {0xXY}
 *      0xWXYZ -> {0xWX, 0xYZ}
 *
 * @param opcode an 8 or 16-bit opcode
 * @return the bytestring corresponding to @p opcode
 */
Bytestring opcode_to_bytestring(const Opcode opcode);

/**
 * Appends bytestring @p other to @p baseString.
 *
 * @param baseString bytestring to which is appended
 * @param other bytestring which is appended
 */
void append_to_bytestring(Bytestring &baseString, const Bytestring &other);

/**
 * Convert an opcode and the following arguments to a bytestring.
 *
 * Merges and opcode @p opcode and a bytestring @p arguments into a bytestring
 * and returns it.
 *
 * @param opcode an opcode
 * @param arguments the arguments of @p opcode
 * @return the resulting bytestring
 */
Bytestring merge_to_bytestring(const Opcode opcode, const Bytestring &arguments);

#include "auxiliary_and_conversions.hpp"

#endif //GAMEBOY_DISASSEMBLE_AUXILIARY_AND_CONVERSIONS_H
