#ifndef GAMEBOY_DEBUG_INSTRUCTIONS_H
#define GAMEBOY_DEBUG_INSTRUCTIONS_H

#include <string>
#include <vector>

using bytestring = std::vector<uint8_t>;

enum class Register_8_bit {
    A,
    B,
    C,
    D,
    E,
    H,
    L
};

enum class Register_16_bit {
    AF,
    BC,
    DE,
    HL,
    SP
};

std::string to_string(const Register_8_bit reg)
{
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

std::string to_string(const Register_16_bit reg)
{
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

std::string to_string_hex(const uint8_t byte, const uint8_t digits = 2)
{
    std::stringstream buffer;
    buffer << std::setw(digits) << std::setfill('0') << std::fixed
           << std::hex << std::uppercase
           << static_cast<int>(byte);
    return buffer.str();
}

class Instruction;
using InstructionPtr = std::unique_ptr<const Instruction>;

class Instruction
{
public:
    Instruction() = default;
    virtual ~Instruction() = default;

    virtual std::string str() const = 0;
    virtual bytestring bytestr() const = 0;

    //virtual void emulate(VirtualGameboy& gameboy) = 0;
    //virtual std::string additional_info() = 0;

};

class LoadImmediateA : public Instruction
{
public:
    static constexpr uint8_t OPCODE{0x3E};
    static constexpr char NAME[]{"LD A"};

    LoadImmediateA(const uint8_t immediate)
    : _immediate(immediate)
    {}

    std::string str() const
    {
        return NAME + (", " + to_string_hex(_immediate));
    }

    bytestring bytestr() const
    {
        return bytestring{OPCODE, _immediate};
    }

private:
    uint8_t _immediate;
};

//
//class LD_REG8_IMMEDIATE8 : public Instruction
//{
//public:
//    LD_REG8_IMMEDIATE8(const Register_8_bit destination, const uint8_t immediate)
//    : _destination(destination),
//    _immediate(immediate)
//    {}
//
//    ~LD_REG8_IMMEDIATE8() = default;
//
//    std::string str()
//    {
//        return "LD " + to_string(_destination) + ", " + to_string_hex(_immediate);
//    }
//
//    bytestring bytestr()
//    {
//        bytestring code(2);
//        switch (_destination)
//        {
//            case Register_8_bit::A: code[0] = 0x3E; break;
//            case Register_8_bit::B: code[0] = 0x06; break;
//            case Register_8_bit::C: code[0] = 0x0; break;
//            case Register_8_bit::D: code[0] = 0x0; break;
//            case Register_8_bit::E: code[0] = 0x0; break;
//            case Register_8_bit::H: code[0] = 0x0; break;
//            case Register_8_bit::L: code[0] = 0x0; break;
//
//        }
//        code[1] = _immediate;
//
//        return code;
//    }
//private:
//    Register_8_bit _destination;
//    uint8_t _immediate;
//};

class Nop : public Instruction
{
public:
    static constexpr uint8_t OPCODE{0x00};
    static constexpr char NAME[]{"NOP"};

    Nop() = default;
    ~Nop() = default;

    std::string str() const
    {
        return NAME;
    }

    bytestring bytestr() const
    {
        return bytestring{OPCODE};
    }
};

class Unknown : public Instruction
{
    static constexpr uint8_t OPCODE{0x00};
    static constexpr char NAME[]{"???"};
public:
    Unknown() = default;
    ~Unknown() = default; // 0xXY LD (immediate), SP

    std::string str()
    {
        return NAME;
    }

    bytestring bytestr()
    {
        return bytestring{OPCODE};
    }
};


#endif //GAMEBOY_DEBUG_INSTRUCTIONS_H
