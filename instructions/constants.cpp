#include "constants.h"

#include <stdexcept>

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

std::string to_string(const Register &reg) {
    if (is_register_8_bit(reg))
    {
        return to_string(std::get<Register8Bit>(reg));
    }
    else if (is_register_16_bit(reg))
    {
        return to_string(std::get<Register16Bit>(reg));
    }
    else
    {
        return "";
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

Register to_register(const std::string &str) {
    if (str == "B") return Register8Bit::B;
    if (str == "C") return Register8Bit::C;
    if (str == "D") return Register8Bit::D;
    if (str == "E") return Register8Bit::E;
    if (str == "H") return Register8Bit::H;
    if (str == "L") return Register8Bit::L;
    if (str == "(HL)") return Register8Bit::ADDRESS_HL;
    if (str == "A") return Register8Bit::A;
    if (str == "AF") return Register16Bit::AF;
    if (str == "BC") return Register16Bit::BC;
    if (str == "DE") return Register16Bit::DE;
    if (str == "HL") return Register16Bit::HL;
    if (str == "SP") return Register16Bit::SP;
    return{};
}

Register8Bit to_register_8_bit(const Register& reg)
{
    if (!is_register_8_bit(reg))
    {
        throw std::logic_error(std::string("Error: Found register ") + to_string(reg) + ". Expected 8-bit register.");
    }
    return std::get<Register8Bit>(reg);
}

Register16Bit to_register_16_bit(const Register& reg)
{
    if (!is_register_16_bit(reg))
    {
        throw std::logic_error(std::string("Error: Found register ") + to_string(reg) + ". Expected 16-bit register.");
    }
    return std::get<Register16Bit>(reg);
}

bool is_valid(const Register &reg) {
    return (reg.index() != 0);
}

bool is_register_8_bit(const Register &reg) {
    return (reg.index() == 1);
}

bool is_register_16_bit(const Register &reg) {
    return (reg.index() == 2);
}