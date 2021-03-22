cmake_minimum_required(VERSION 3.17)
project(gameboy_disassemble)

set(CMAKE_CXX_STANDARD 17)

add_executable(gameboy_debug main.cpp decoder.cpp decoder.h instructions/instructions.h instructions/constants.h instructions/conversions.h instructions/conversions.cpp instructions/instructions_load_8bit.h instructions/conversions.hpp instructions/instructions_load_16bit.h instructions/instructions_rotation.h instructions/instructions_increment_decrement.h instructions/interface.cpp instructions/interface.h instructions/instructions_jump.h instructions/instructions_add.h instructions/instructions_unused.h instructions/instructions_subtract.h instructions/instructions_logical.h instructions/instructions_shift_swap.h instructions/instructions_bit_complement.h instructions/instructions_set_reset.h instructions/instructions_push_pop.h instructions/instructions_machine.h tokenizer.cpp tokenizer.h token.cpp token.h parser.cpp parser.h instructions/constants.cpp)