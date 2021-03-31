cmake_minimum_required(VERSION 3.17)
project(gameboy_disassemble)

set(CMAKE_CXX_STANDARD 17)

file(GLOB Sourcefiles src/disassembler/decoder.cpp src/disassembler/decoder.h src/instructions/instructions.h src/instructions/constants.h src/instructions/auxiliary_and_conversions.h src/instructions/auxiliary_and_conversions.cpp src/instructions/instructions_load_8bit.h src/instructions/auxiliary_and_conversions.hpp src/instructions/instructions_load_16bit.h src/instructions/instructions_rotation.h src/instructions/instructions_increment_decrement.h src/instructions/interface.cpp src/instructions/interface.h src/instructions/instructions_jump.h src/instructions/instructions_add.h src/instructions/instructions_unused.h src/instructions/instructions_subtract.h src/instructions/instructions_logical.h src/instructions/instructions_shift_swap.h src/instructions/instructions_bit_complement.h src/instructions/instructions_set_reset.h src/instructions/instructions_push_pop.h src/instructions/instructions_machine.h src/instructions/instructions_parser.h src/assembler/tokenizer.cpp src/assembler/tokenizer.h src/assembler/token.cpp src/assembler/token.h src/assembler/parser.cpp src/assembler/parser.h src/instructions/constants.cpp src/disassembler/disassemble.cpp src/disassembler/disassemble.h src/assembler/parser_parsing.cpp src/assembler/assemble.cpp src/assembler/assemble.h src/assembler/auxiliary.cpp src/assembler/auxiliary.h src/assembler/pretty_format.cpp src/assembler/pretty_format.h)

add_executable(gameboy_disassemble src/main.cpp ${Sourcefiles})


## for catch2 tests:

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/tests_root.cpp ${Sourcefiles})
target_link_libraries(tests PRIVATE Catch2::Catch2)