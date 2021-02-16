#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H

#include "instructions_constants.h"
#include "instructions_conversions.h"

class IncrementB : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"INC B"};
};

class DecrementB : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"DEC B"};
};

class IncrementC : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"INC C"};
};

class DecrementC : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"DEC C"};
};

//

class IncrementBC : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"INC BC"};
};

class DecrementBC : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"DEC BC"};
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H
