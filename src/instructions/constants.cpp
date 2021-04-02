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
        return "??";
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

FlagCondition to_flag_condition(const std::string &str) {
    if (str == "Z") return FlagCondition::ZERO;
    if (str == "NZ") return FlagCondition::NOT_ZERO;
    if (str == "C") return FlagCondition::CARRY;
    if (str == "NC") return FlagCondition::NOT_CARRY;

    throw std::logic_error("Error: String " + str + " cannot be converted to flag condition (i.e. Z, NZ, C or NC).");
}

bool is_flag_condition(const std::string &str) noexcept {
    try {
        to_flag_condition(str);
        return true;
    } catch(...) {
        return false;
    }
}

Register to_register(const std::string &str) noexcept {
    if (str == "B" || str == "b") return Register8Bit::B;
    if (str == "C" || str == "c") return Register8Bit::C;
    if (str == "D" || str == "d") return Register8Bit::D;
    if (str == "E" || str == "e") return Register8Bit::E;
    if (str == "H" || str == "h") return Register8Bit::H;
    if (str == "L" || str == "l") return Register8Bit::L;
    if (str == "(HL)" || str == "(hl)"
     || str == "[HL]" || str == "[hl]") return Register8Bit::ADDRESS_HL;
    if (str == "A" || str == "a") return Register8Bit::A;
    if (str == "AF" || str == "af") return Register16Bit::AF;
    if (str == "BC" || str == "bc") return Register16Bit::BC;
    if (str == "DE" || str == "de") return Register16Bit::DE;
    if (str == "HL" || str == "hl") return Register16Bit::HL;
    if (str == "SP" || str == "sp") return Register16Bit::SP;
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

bool is_valid(const Register &reg) noexcept {
    return (reg.index() != 0);
}

bool is_register_8_bit(const Register &reg) noexcept {
    return (reg.index() == 1);
}

bool is_register_16_bit(const Register &reg) noexcept {
    return (reg.index() == 2);
}