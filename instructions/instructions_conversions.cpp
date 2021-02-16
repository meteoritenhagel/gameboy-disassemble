#include "instructions_conversions.h"

#include <iomanip>
#include <iostream>
#include <string>

uint8_t get_least_significant_byte(const uint16_t word) {
    return static_cast<uint8_t>(word & 0x00FF);
}

uint8_t get_most_significant_byte(const uint16_t word) {
    return static_cast<uint8_t>(word >> 8);
}

uint16_t little_endian_to_number(const uint8_t lsb, const uint8_t msb) {
    return ((msb << 8) | lsb);
}

uint16_t big_endian_to_number(const uint8_t msb, const uint8_t lsb) {
    return ((msb << 8) | lsb);
}

std::string to_string(const Register_8_bit reg) {
    switch (reg)
    {
        case Register_8_bit::A: return "A"; break;
        case Register_8_bit::B: return "B"; break;
        case Register_8_bit::C: return "C"; break;
        case Register_8_bit::D: return "D"; break;
        case Register_8_bit::E: return "E"; break;
        case Register_8_bit::H: return "H"; break;
        case Register_8_bit::L: return "L"; break;
        default: return "?";
    }
}

std::string to_string(const Register_16_bit reg) {
    switch (reg)
    {
        case Register_16_bit::AF: return "AF"; break;
        case Register_16_bit::BC: return "BC"; break;
        case Register_16_bit::DE: return "DE"; break;
        case Register_16_bit::HL: return "HL"; break;
        case Register_16_bit::SP: return "SP"; break;
        default: return "??";
    }
}

bytestring to_bytestring_little_endian(const uint16_t number) {
    return bytestring{get_least_significant_byte(number), get_most_significant_byte(number)};
}

bytestring opcode_to_bytestring(const Opcode opcode) {
    if (0x0000 <= opcode && opcode <= 0x00FF)
    {
        return bytestring{static_cast<uint8_t>(opcode)};
    }
    else
    {
        // split into prefix and opcode
        return bytestring{get_most_significant_byte(opcode), get_least_significant_byte(opcode)};
    }
}

bytestring to_bytestring(const Opcode opcode, const bytestring &arguments) {
    bytestring bytestr = opcode_to_bytestring(opcode);
    bytestr.insert(bytestr.end(), arguments.cbegin(), arguments.cend());
    return bytestr;
}