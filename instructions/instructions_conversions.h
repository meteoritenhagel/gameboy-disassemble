#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_CONVERSIONS_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_CONVERSIONS_H

#include "instructions_constants.h"
#include <string>

uint8_t get_least_significant_byte(const uint16_t word);

uint8_t get_most_significant_byte(const uint16_t word);

uint16_t little_endian_to_number(const uint8_t lsb, const uint8_t msb);

uint16_t big_endian_to_number(const uint8_t msb, const uint8_t lsb);

std::string to_string(const Register_8_bit reg);

std::string to_string(const Register_16_bit reg);

template<typename T>
std::string to_string_hex(const T number, const uint8_t digits = 2*sizeof(T));

template<typename T>
std::string to_string_hex_prefixed(const T number, const uint8_t digits = 2*sizeof(T));

bytestring to_bytestring_little_endian(const uint16_t number);

bytestring opcode_to_bytestring(const Opcode opcode);

bytestring to_bytestring(const Opcode opcode, const bytestring& arguments);

#include "instructions_conversions.hpp"
#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_CONVERSIONS_H
