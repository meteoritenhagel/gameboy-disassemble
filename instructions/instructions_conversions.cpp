#include "instructions_conversions.h"

#include <string>

byte get_least_significant_byte(const word wrd) {
    return static_cast<byte>(wrd & 0x00FF);
}

byte get_most_significant_byte(const word wrd) {
    return static_cast<byte>(wrd >> 8);
}

word little_endian_to_number(const byte lsb, const byte msb) {
    return ((msb << 8) | lsb);
}

word big_endian_to_number(const byte msb, const byte lsb) {
    return ((msb << 8) | lsb);
}

word extend_sign(const byte number) {
    return is_negative(number) ? (0xFF00 | number) : (0x0000 | number);
}

std::string to_string(const Register8Bit reg) {
    switch (reg)
    {
        case Register8Bit::A: return "A"; break;
        case Register8Bit::B: return "B"; break;
        case Register8Bit::C: return "C"; break;
        case Register8Bit::D: return "D"; break;
        case Register8Bit::E: return "E"; break;
        case Register8Bit::H: return "H"; break;
        case Register8Bit::L: return "L"; break;
        case Register8Bit::ADDRESS_HL: return "(HL)"; break;
        default: return "?";
    }
}

std::string to_string(const Register16Bit reg) {
    switch (reg)
    {
        case Register16Bit::AF: return "AF"; break;
        case Register16Bit::BC: return "BC"; break;
        case Register16Bit::DE: return "DE"; break;
        case Register16Bit::HL: return "HL"; break;
        case Register16Bit::SP: return "SP"; break;
        default: return "??";
    }
}

std::string to_string(const FlagCondition flagCondition) {
    switch (flagCondition)
    {
        case FlagCondition::ZERO: return "Z"; break;
        case FlagCondition::NOT_ZERO: return "NZ"; break;
        case FlagCondition::CARRY: return "C"; break;
        case FlagCondition::NOT_CARRY: return "NC"; break;
        default: return "??";
    }
}

bytestring to_bytestring_little_endian(const word number) {
    return bytestring{get_least_significant_byte(number), get_most_significant_byte(number)};
}

bytestring opcode_to_bytestring(const Opcode opcode) {
    if (0x0000 <= opcode && opcode <= 0x00FF)
    {
        return bytestring{static_cast<byte>(opcode)};
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