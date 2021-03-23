#ifndef GAMEBOY_DISASSEMBLE_CONVERSIONS_H
#define GAMEBOY_DISASSEMBLE_CONVERSIONS_H

#include "constants.h"

#include <string>

template<typename T>
bool is_negative(const T number);

byte get_least_significant_byte(const word wrd);

byte get_most_significant_byte(const word wrd);

word little_endian_to_number(const byte lsb, const byte msb);

word big_endian_to_number(const byte msb, const byte lsb);

word extend_sign(const byte number);

template<typename T>
T twos_complement(const T number);

template<typename T>
std::string to_string_hex(const T number, const byte digits = 2 * sizeof(T));

template<typename T>
std::string to_string_dec(const T number);

template<typename T>
std::string to_string_hex_prefixed(const T number, const byte digits = 2 * sizeof(T));

template<typename T>
std::string to_string_hex_signed_prefixed(const T number, const byte digits = 2 * sizeof(T));

Bytestring to_bytestring_little_endian(const word number);

Bytestring to_bytestring_big_endian(const word number);

Bytestring opcode_to_bytestring(const Opcode opcode);

Bytestring to_bytestring(const Opcode opcode, const Bytestring &arguments);

#include "conversions.hpp"

#endif //GAMEBOY_DISASSEMBLE_CONVERSIONS_H
