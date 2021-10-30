//
// Created by tristan on 16.02.21.
//

#ifndef GAMEBOY_DISASSEMBLE_CONSTANTS_H
#define GAMEBOY_DISASSEMBLE_CONSTANTS_H

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>

using byte = uint8_t;
using word = uint16_t;

using Bytestring = std::vector<byte>;
using BytestringPtr = std::unique_ptr<Bytestring>;

using Opcode = word; // must be literal type, so that it can be used with switch statements

enum class Register8Bit {
    B,
    C,
    D,
    E,
    H,
    L,
    ADDRESS_HL,
    A
};

enum class Register16Bit {
    AF,
    BC,
    DE,
    HL,
    SP
};

enum class RegisterInvalid {
    INVALID
};

using Register = std::variant<Register8Bit, Register16Bit, RegisterInvalid>;

enum class FlagCondition {
    ZERO,
    NOT_ZERO,
    CARRY,
    NOT_CARRY
};

std::string to_string(const Register8Bit reg);

std::string to_string(const Register16Bit reg);

std::string to_string(const Register &reg);

std::string to_string(const FlagCondition flagCondition);

FlagCondition to_flag_condition(const std::string &str);

bool is_flag_condition(const std::string &str) noexcept;

Register to_register(const std::string &str) noexcept;

Register8Bit to_register_8_bit(const Register &reg);

Register16Bit to_register_16_bit(const Register &reg);

bool is_valid(const Register &reg) noexcept;

bool is_register_8_bit(const Register &reg) noexcept;

bool is_register_16_bit(const Register &reg) noexcept;

namespace opcodes {
    constexpr Opcode NOP                                        {0x00};
    constexpr Opcode LOAD_IMMEDIATE_INTO_BC                     {0x01};
    constexpr Opcode LOAD_A_INTO_ADDRESS_BC                     {0x02};
    constexpr Opcode INCREMENT_BC                               {0x03};
    constexpr Opcode INCREMENT_B                                {0x04};
    constexpr Opcode DECREMENT_B                                {0x05};
    constexpr Opcode LOAD_IMMEDIATE_INTO_B                      {0x06};
    constexpr Opcode ROTATE_LEFT_CIRCULAR_A_AND_CLEAR_ZERO      {0x07};
    constexpr Opcode LOAD_SP_INTO_ADDRESS_IMMEDIATE             {0x08};
    constexpr Opcode ADD_HL_AND_BC                              {0x09};
    constexpr Opcode LOAD_ADDRESS_BC_INTO_A                     {0x0A};
    constexpr Opcode DECREMENT_BC                               {0x0B};
    constexpr Opcode INCREMENT_C                                {0x0C};
    constexpr Opcode DECREMENT_C                                {0x0D};
    constexpr Opcode LOAD_IMMEDIATE_INTO_C                      {0x0E};
    constexpr Opcode ROTATE_RIGHT_CIRCULAR_A_AND_CLEAR_ZERO     {0x0F};

    constexpr Opcode STOP                                       {0x10};
    constexpr Opcode LOAD_IMMEDIATE_INTO_DE                     {0x11};
    constexpr Opcode LOAD_A_INTO_ADDRESS_DE                     {0x12};
    constexpr Opcode INCREMENT_DE                               {0x13};
    constexpr Opcode INCREMENT_D                                {0x14};
    constexpr Opcode DECREMENT_D                                {0x15};
    constexpr Opcode LOAD_IMMEDIATE_INTO_D                      {0x16};
    constexpr Opcode ROTATE_LEFT_A_AND_CLEAR_ZERO               {0x17};
    constexpr Opcode JUMP_RELATIVE                              {0x18};
    constexpr Opcode ADD_HL_AND_DE                              {0x19};
    constexpr Opcode LOAD_ADDRESS_DE_INTO_A                     {0x1A};
    constexpr Opcode DECREMENT_DE                               {0x1B};
    constexpr Opcode INCREMENT_E                                {0x1C};
    constexpr Opcode DECREMENT_E                                {0x1D};
    constexpr Opcode LOAD_IMMEDIATE_INTO_E                      {0x1E};
    constexpr Opcode ROTATE_RIGHT_A_AND_CLEAR_ZERO              {0x1F};

    constexpr Opcode JUMP_RELATIVE_IF_NOT_ZERO                  {0x20};
    constexpr Opcode LOAD_IMMEDIATE_INTO_HL                     {0x21};
    constexpr Opcode LOAD_A_INTO_ADDRESS_HL_INCREMENT           {0x22};
    constexpr Opcode INCREMENT_HL                               {0x23};
    constexpr Opcode INCREMENT_H                                {0x24};
    constexpr Opcode DECREMENT_H                                {0x25};
    constexpr Opcode LOAD_IMMEDIATE_INTO_H                      {0x26};
    constexpr Opcode DECIMAL_ADJUST_A                           {0x27};
    constexpr Opcode JUMP_RELATIVE_IF_ZERO                      {0x28};
    constexpr Opcode ADD_HL_AND_HL                              {0x29};
    constexpr Opcode LOAD_ADDRESS_HL_INCREMENT_INTO_A           {0x2A};
    constexpr Opcode DECREMENT_HL                               {0x2B};
    constexpr Opcode INCREMENT_L                                {0x2C};
    constexpr Opcode DECREMENT_L                                {0x2D};
    constexpr Opcode LOAD_IMMEDIATE_INTO_L                      {0x2E};
    constexpr Opcode COMPLEMENT_A                               {0x2F};

    constexpr Opcode JUMP_RELATIVE_IF_NOT_CARRY                 {0x30};
    constexpr Opcode LOAD_IMMEDIATE_INTO_SP                     {0x31};
    constexpr Opcode LOAD_A_INTO_ADDRESS_HL_DECREMENT           {0x32};
    constexpr Opcode INCREMENT_SP                               {0x33};
    constexpr Opcode INCREMENT_ADDRESS_HL                       {0x34};
    constexpr Opcode DECREMENT_ADDRESS_HL                       {0x35};
    constexpr Opcode LOAD_IMMEDIATE_INTO_ADDRESS_HL             {0x36};
    constexpr Opcode SET_CARRY                                  {0x37};
    constexpr Opcode JUMP_RELATIVE_IF_CARRY                     {0x38};
    constexpr Opcode ADD_HL_AND_SP                              {0x39};
    constexpr Opcode LOAD_ADDRESS_HL_DECREMENT_INTO_A           {0x3A};
    constexpr Opcode DECREMENT_SP                               {0x3B};
    constexpr Opcode INCREMENT_A                                {0x3C};
    constexpr Opcode DECREMENT_A                                {0x3D};
    constexpr Opcode LOAD_IMMEDIATE_INTO_A                      {0x3E};
    constexpr Opcode FLIP_CARRY                                 {0x3F};

    constexpr Opcode LOAD_B_INTO_B                              {0x40};
    constexpr Opcode LOAD_C_INTO_B                              {0x41};
    constexpr Opcode LOAD_D_INTO_B                              {0x42};
    constexpr Opcode LOAD_E_INTO_B                              {0x43};
    constexpr Opcode LOAD_H_INTO_B                              {0x44};
    constexpr Opcode LOAD_L_INTO_B                              {0x45};
    constexpr Opcode LOAD_ADDRESS_HL_INTO_B                     {0x46};
    constexpr Opcode LOAD_A_INTO_B                              {0x47};
    constexpr Opcode LOAD_B_INTO_C                              {0x48};
    constexpr Opcode LOAD_C_INTO_C                              {0x49};
    constexpr Opcode LOAD_D_INTO_C                              {0x4A};
    constexpr Opcode LOAD_E_INTO_C                              {0x4B};
    constexpr Opcode LOAD_H_INTO_C                              {0x4C};
    constexpr Opcode LOAD_L_INTO_C                              {0x4D};
    constexpr Opcode LOAD_ADDRESS_HL_INTO_C                     {0x4E};
    constexpr Opcode LOAD_A_INTO_C                              {0x4F};

    constexpr Opcode LOAD_B_INTO_D                              {0x50};
    constexpr Opcode LOAD_C_INTO_D                              {0x51};
    constexpr Opcode LOAD_D_INTO_D                              {0x52};
    constexpr Opcode LOAD_E_INTO_D                              {0x53};
    constexpr Opcode LOAD_H_INTO_D                              {0x54};
    constexpr Opcode LOAD_L_INTO_D                              {0x55};
    constexpr Opcode LOAD_ADDRESS_HL_INTO_D                     {0x56};
    constexpr Opcode LOAD_A_INTO_D                              {0x57};
    constexpr Opcode LOAD_B_INTO_E                              {0x58};
    constexpr Opcode LOAD_C_INTO_E                              {0x59};
    constexpr Opcode LOAD_D_INTO_E                              {0x5A};
    constexpr Opcode LOAD_E_INTO_E                              {0x5B};
    constexpr Opcode LOAD_H_INTO_E                              {0x5C};
    constexpr Opcode LOAD_L_INTO_E                              {0x5D};
    constexpr Opcode LOAD_ADDRESS_HL_INTO_E                     {0x5E};
    constexpr Opcode LOAD_A_INTO_E                              {0x5F};

    constexpr Opcode LOAD_B_INTO_H                              {0x60};
    constexpr Opcode LOAD_C_INTO_H                              {0x61};
    constexpr Opcode LOAD_D_INTO_H                              {0x62};
    constexpr Opcode LOAD_E_INTO_H                              {0x63};
    constexpr Opcode LOAD_H_INTO_H                              {0x64};
    constexpr Opcode LOAD_L_INTO_H                              {0x65};
    constexpr Opcode LOAD_ADDRESS_HL_INTO_H                     {0x66};
    constexpr Opcode LOAD_A_INTO_H                              {0x67};
    constexpr Opcode LOAD_B_INTO_L                              {0x68};
    constexpr Opcode LOAD_C_INTO_L                              {0x69};
    constexpr Opcode LOAD_D_INTO_L                              {0x6A};
    constexpr Opcode LOAD_E_INTO_L                              {0x6B};
    constexpr Opcode LOAD_H_INTO_L                              {0x6C};
    constexpr Opcode LOAD_L_INTO_L                              {0x6D};
    constexpr Opcode LOAD_ADDRESS_HL_INTO_L                     {0x6E};
    constexpr Opcode LOAD_A_INTO_L                              {0x6F};

    constexpr Opcode LOAD_B_INTO_ADDRESS_HL                     {0x70};
    constexpr Opcode LOAD_C_INTO_ADDRESS_HL                     {0x71};
    constexpr Opcode LOAD_D_INTO_ADDRESS_HL                     {0x72};
    constexpr Opcode LOAD_E_INTO_ADDRESS_HL                     {0x73};
    constexpr Opcode LOAD_H_INTO_ADDRESS_HL                     {0x74};
    constexpr Opcode LOAD_L_INTO_ADDRESS_HL                     {0x75};
    constexpr Opcode HALT                                       {0x76};
    constexpr Opcode LOAD_A_INTO_ADDRESS_HL                     {0x77};
    constexpr Opcode LOAD_B_INTO_A                              {0x78};
    constexpr Opcode LOAD_C_INTO_A                              {0x79};
    constexpr Opcode LOAD_D_INTO_A                              {0x7A};
    constexpr Opcode LOAD_E_INTO_A                              {0x7B};
    constexpr Opcode LOAD_H_INTO_A                              {0x7C};
    constexpr Opcode LOAD_L_INTO_A                              {0x7D};
    constexpr Opcode LOAD_ADDRESS_HL_INTO_A                     {0x7E};
    constexpr Opcode LOAD_A_INTO_A                              {0x7F};

    constexpr Opcode ADD_A_AND_B                                {0x80};
    constexpr Opcode ADD_A_AND_C                                {0x81};
    constexpr Opcode ADD_A_AND_D                                {0x82};
    constexpr Opcode ADD_A_AND_E                                {0x83};
    constexpr Opcode ADD_A_AND_H                                {0x84};
    constexpr Opcode ADD_A_AND_L                                {0x85};
    constexpr Opcode ADD_A_AND_ADDRESS_HL                       {0x86};
    constexpr Opcode ADD_A_AND_A                                {0x87};
    constexpr Opcode ADD_WITH_CARRY_A_AND_B                     {0x88};
    constexpr Opcode ADD_WITH_CARRY_A_AND_C                     {0x89};
    constexpr Opcode ADD_WITH_CARRY_A_AND_D                     {0x8A};
    constexpr Opcode ADD_WITH_CARRY_A_AND_E                     {0x8B};
    constexpr Opcode ADD_WITH_CARRY_A_AND_H                     {0x8C};
    constexpr Opcode ADD_WITH_CARRY_A_AND_L                     {0x8D};
    constexpr Opcode ADD_WITH_CARRY_A_AND_ADDRESS_HL            {0x8E};
    constexpr Opcode ADD_WITH_CARRY_A_AND_A                     {0x8F};

    constexpr Opcode SUBTRACT_A_AND_B                           {0x90};
    constexpr Opcode SUBTRACT_A_AND_C                           {0x91};
    constexpr Opcode SUBTRACT_A_AND_D                           {0x92};
    constexpr Opcode SUBTRACT_A_AND_E                           {0x93};
    constexpr Opcode SUBTRACT_A_AND_H                           {0x94};
    constexpr Opcode SUBTRACT_A_AND_L                           {0x95};
    constexpr Opcode SUBTRACT_A_AND_ADDRESS_HL                  {0x96};
    constexpr Opcode SUBTRACT_A_AND_A                           {0x97};
    constexpr Opcode SUBTRACT_WITH_CARRY_A_AND_B                {0x98};
    constexpr Opcode SUBTRACT_WITH_CARRY_A_AND_C                {0x99};
    constexpr Opcode SUBTRACT_WITH_CARRY_A_AND_D                {0x9A};
    constexpr Opcode SUBTRACT_WITH_CARRY_A_AND_E                {0x9B};
    constexpr Opcode SUBTRACT_WITH_CARRY_A_AND_H                {0x9C};
    constexpr Opcode SUBTRACT_WITH_CARRY_A_AND_L                {0x9D};
    constexpr Opcode SUBTRACT_WITH_CARRY_A_AND_ADDRESS_HL       {0x9E};
    constexpr Opcode SUBTRACT_WITH_CARRY_A_AND_A                {0x9F};

    constexpr Opcode AND_A_AND_B                                {0xA0};
    constexpr Opcode AND_A_AND_C                                {0xA1};
    constexpr Opcode AND_A_AND_D                                {0xA2};
    constexpr Opcode AND_A_AND_E                                {0xA3};
    constexpr Opcode AND_A_AND_H                                {0xA4};
    constexpr Opcode AND_A_AND_L                                {0xA5};
    constexpr Opcode AND_A_AND_ADDRESS_HL                       {0xA6};
    constexpr Opcode AND_A_AND_A                                {0xA7};
    constexpr Opcode XOR_A_AND_B                                {0xA8};
    constexpr Opcode XOR_A_AND_C                                {0xA9};
    constexpr Opcode XOR_A_AND_D                                {0xAA};
    constexpr Opcode XOR_A_AND_E                                {0xAB};
    constexpr Opcode XOR_A_AND_H                                {0xAC};
    constexpr Opcode XOR_A_AND_L                                {0xAD};
    constexpr Opcode XOR_A_AND_ADDRESS_HL                       {0xAE};
    constexpr Opcode XOR_A_AND_A                                {0xAF};

    constexpr Opcode OR_A_AND_B                                 {0xB0};
    constexpr Opcode OR_A_AND_C                                 {0xB1};
    constexpr Opcode OR_A_AND_D                                 {0xB2};
    constexpr Opcode OR_A_AND_E                                 {0xB3};
    constexpr Opcode OR_A_AND_H                                 {0xB4};
    constexpr Opcode OR_A_AND_L                                 {0xB5};
    constexpr Opcode OR_A_AND_ADDRESS_HL                        {0xB6};
    constexpr Opcode OR_A_AND_A                                 {0xB7};
    constexpr Opcode COMPARE_A_AND_B                            {0xB8};
    constexpr Opcode COMPARE_A_AND_C                            {0xB9};
    constexpr Opcode COMPARE_A_AND_D                            {0xBA};
    constexpr Opcode COMPARE_A_AND_E                            {0xBB};
    constexpr Opcode COMPARE_A_AND_H                            {0xBC};
    constexpr Opcode COMPARE_A_AND_L                            {0xBD};
    constexpr Opcode COMPARE_A_AND_ADDRESS_HL                   {0xBE};
    constexpr Opcode COMPARE_A_AND_A                            {0xBF};

    constexpr Opcode RETURN_IF_NOT_ZERO                         {0xC0};
    constexpr Opcode POP_BC                                     {0xC1};
    constexpr Opcode JUMP_IF_NOT_ZERO                           {0xC2};
    constexpr Opcode JUMP                                       {0xC3};
    constexpr Opcode CALL_IF_NOT_ZERO                           {0xC4};
    constexpr Opcode PUSH_BC                                    {0xC5};
    constexpr Opcode ADD_A_AND_IMMEDIATE                        {0xC6};
    constexpr Opcode RESTART_0                                  {0xC7};
    constexpr Opcode RETURN_IF_ZERO                             {0xC8};
    constexpr Opcode RETURN                                     {0xC9};
    constexpr Opcode JUMP_IF_ZERO                               {0xCA};
    constexpr Opcode UNUSED_0                                   {0xCB};
    constexpr Opcode CALL_IF_ZERO                               {0xCC};
    constexpr Opcode CALL                                       {0xCD};
    constexpr Opcode ADD_WITH_CARRY_A_AND_IMMEDIATE             {0xCE};
    constexpr Opcode RESTART_1                                  {0xCF};

    constexpr Opcode RETURN_IF_NOT_CARRY                        {0xD0};
    constexpr Opcode POP_DE                                     {0xD1};
    constexpr Opcode JUMP_IF_NOT_CARRY                          {0xD2};
    constexpr Opcode UNUSED_1                                   {0xD3};
    constexpr Opcode CALL_IF_NOT_CARRY                          {0xD4};
    constexpr Opcode PUSH_DE                                    {0xD5};
    constexpr Opcode SUBTRACT_A_AND_IMMEDIATE                   {0xD6};
    constexpr Opcode RESTART_2                                  {0xD7};
    constexpr Opcode RETURN_IF_CARRY                            {0xD8};
    constexpr Opcode RETURN_FROM_INTERRUPT                      {0xD9};
    constexpr Opcode JUMP_IF_CARRY                              {0xDA};
    constexpr Opcode UNUSED_2                                   {0xDB};
    constexpr Opcode CALL_IF_CARRY                              {0xDC};
    constexpr Opcode UNUSED_3                                   {0xDD};
    constexpr Opcode SUBTRACT_WITH_CARRY_A_AND_IMMEDIATE        {0xDE};
    constexpr Opcode RESTART_3                                  {0xDF};

    constexpr Opcode LOAD_A_INTO_PORT_ADDRESS_IMMEDIATE         {0xE0};
    constexpr Opcode POP_HL                                     {0xE1};
    constexpr Opcode LOAD_A_INTO_PORT_ADDRESS_C                 {0xE2};
    constexpr Opcode UNUSED_4                                   {0xE3};
    constexpr Opcode UNUSED_5                                   {0xE4};
    constexpr Opcode PUSH_HL                                    {0xE5};
    constexpr Opcode AND_A_AND_IMMEDIATE                        {0xE6};
    constexpr Opcode RESTART_4                                  {0xE7};
    constexpr Opcode ADD_SP_AND_IMMEDIATE                       {0xE8};
    constexpr Opcode JUMP_TO_HL                                 {0xE9};
    constexpr Opcode LOAD_A_INTO_ADDRESS_IMMEDIATE              {0xEA};
    constexpr Opcode UNUSED_6                                   {0xEB};
    constexpr Opcode UNUSED_7                                   {0xEC};
    constexpr Opcode UNUSED_8                                   {0xED};
    constexpr Opcode XOR_A_AND_IMMEDIATE                        {0xEE};
    constexpr Opcode RESTART_5                                  {0xEF};

    constexpr Opcode LOAD_PORT_ADDRESS_IMMEDIATE_INTO_A         {0xF0};
    constexpr Opcode POP_AF                                     {0xF1};
    constexpr Opcode LOAD_PORT_ADDRESS_C_INTO_A                 {0xF2};
    constexpr Opcode DISABLE_INTERRUPTS                         {0xF3};
    constexpr Opcode UNUSED_9                                   {0xF4};
    constexpr Opcode PUSH_AF                                    {0xF5};
    constexpr Opcode OR_A_AND_IMMEDIATE                         {0xF6};
    constexpr Opcode RESTART_6                                  {0xF7};
    constexpr Opcode LOAD_SP_SHIFTED_BY_IMMEDIATE_INTO_HL       {0xF8};
    constexpr Opcode LOAD_HL_INTO_SP                            {0xF9};
    constexpr Opcode LOAD_ADDRESS_IMMEDIATE_INTO_A              {0xFA};
    constexpr Opcode ENABLE_INTERRUPTS                          {0xFB};
    constexpr Opcode UNUSED_10                                  {0xFC};
    constexpr Opcode UNUSED_11                                  {0xFD};
    constexpr Opcode COMPARE_A_AND_IMMEDIATE                    {0xFE};
    constexpr Opcode RESTART_7                                  {0xFF};

    //

    constexpr Opcode ROTATE_LEFT_CIRCULAR_B                     {0xCB00};
    constexpr Opcode ROTATE_LEFT_CIRCULAR_C                     {0xCB01};
    constexpr Opcode ROTATE_LEFT_CIRCULAR_D                     {0xCB02};
    constexpr Opcode ROTATE_LEFT_CIRCULAR_E                     {0xCB03};
    constexpr Opcode ROTATE_LEFT_CIRCULAR_H                     {0xCB04};
    constexpr Opcode ROTATE_LEFT_CIRCULAR_L                     {0xCB05};
    constexpr Opcode ROTATE_LEFT_CIRCULAR_ADDRESS_HL            {0xCB06};
    constexpr Opcode ROTATE_LEFT_CIRCULAR_A                     {0xCB07};
    constexpr Opcode ROTATE_RIGHT_CIRCULAR_B                    {0xCB08};
    constexpr Opcode ROTATE_RIGHT_CIRCULAR_C                    {0xCB09};
    constexpr Opcode ROTATE_RIGHT_CIRCULAR_D                    {0xCB0A};
    constexpr Opcode ROTATE_RIGHT_CIRCULAR_E                    {0xCB0B};
    constexpr Opcode ROTATE_RIGHT_CIRCULAR_H                    {0xCB0C};
    constexpr Opcode ROTATE_RIGHT_CIRCULAR_L                    {0xCB0D};
    constexpr Opcode ROTATE_RIGHT_CIRCULAR_ADDRESS_HL           {0xCB0E};
    constexpr Opcode ROTATE_RIGHT_CIRCULAR_A                    {0xCB0F};

    constexpr Opcode ROTATE_LEFT_B                              {0xCB10};
    constexpr Opcode ROTATE_LEFT_C                              {0xCB11};
    constexpr Opcode ROTATE_LEFT_D                              {0xCB12};
    constexpr Opcode ROTATE_LEFT_E                              {0xCB13};
    constexpr Opcode ROTATE_LEFT_H                              {0xCB14};
    constexpr Opcode ROTATE_LEFT_L                              {0xCB15};
    constexpr Opcode ROTATE_LEFT_ADDRESS_HL                     {0xCB16};
    constexpr Opcode ROTATE_LEFT_A                              {0xCB17};
    constexpr Opcode ROTATE_RIGHT_B                             {0xCB18};
    constexpr Opcode ROTATE_RIGHT_C                             {0xCB19};
    constexpr Opcode ROTATE_RIGHT_D                             {0xCB1A};
    constexpr Opcode ROTATE_RIGHT_E                             {0xCB1B};
    constexpr Opcode ROTATE_RIGHT_H                             {0xCB1C};
    constexpr Opcode ROTATE_RIGHT_L                             {0xCB1D};
    constexpr Opcode ROTATE_RIGHT_ADDRESS_HL                    {0xCB1E};
    constexpr Opcode ROTATE_RIGHT_A                             {0xCB1F};

    constexpr Opcode SHIFT_LEFT_ARITHMETICAL_B                  {0xCB20};
    constexpr Opcode SHIFT_LEFT_ARITHMETICAL_C                  {0xCB21};
    constexpr Opcode SHIFT_LEFT_ARITHMETICAL_D                  {0xCB22};
    constexpr Opcode SHIFT_LEFT_ARITHMETICAL_E                  {0xCB23};
    constexpr Opcode SHIFT_LEFT_ARITHMETICAL_H                  {0xCB24};
    constexpr Opcode SHIFT_LEFT_ARITHMETICAL_L                  {0xCB25};
    constexpr Opcode SHIFT_LEFT_ARITHMETICAL_ADDRESS_HL         {0xCB26};
    constexpr Opcode SHIFT_LEFT_ARITHMETICAL_A                  {0xCB27};
    constexpr Opcode SHIFT_RIGHT_ARITHMETICAL_B                 {0xCB28};
    constexpr Opcode SHIFT_RIGHT_ARITHMETICAL_C                 {0xCB29};
    constexpr Opcode SHIFT_RIGHT_ARITHMETICAL_D                 {0xCB2A};
    constexpr Opcode SHIFT_RIGHT_ARITHMETICAL_E                 {0xCB2B};
    constexpr Opcode SHIFT_RIGHT_ARITHMETICAL_H                 {0xCB2C};
    constexpr Opcode SHIFT_RIGHT_ARITHMETICAL_L                 {0xCB2D};
    constexpr Opcode SHIFT_RIGHT_ARITHMETICAL_ADDRESS_HL        {0xCB2E};
    constexpr Opcode SHIFT_RIGHT_ARITHMETICAL_A                 {0xCB2F};

    constexpr Opcode SWAP_B                                     {0xCB30};
    constexpr Opcode SWAP_C                                     {0xCB31};
    constexpr Opcode SWAP_D                                     {0xCB32};
    constexpr Opcode SWAP_E                                     {0xCB33};
    constexpr Opcode SWAP_H                                     {0xCB34};
    constexpr Opcode SWAP_L                                     {0xCB35};
    constexpr Opcode SWAP_ADDRESS_HL                            {0xCB36};
    constexpr Opcode SWAP_A                                     {0xCB37};
    constexpr Opcode SHIFT_RIGHT_LOGICAL_B                      {0xCB38};
    constexpr Opcode SHIFT_RIGHT_LOGICAL_C                      {0xCB39};
    constexpr Opcode SHIFT_RIGHT_LOGICAL_D                      {0xCB3A};
    constexpr Opcode SHIFT_RIGHT_LOGICAL_E                      {0xCB3B};
    constexpr Opcode SHIFT_RIGHT_LOGICAL_H                      {0xCB3C};
    constexpr Opcode SHIFT_RIGHT_LOGICAL_L                      {0xCB3D};
    constexpr Opcode SHIFT_RIGHT_LOGICAL_ADDRESS_HL             {0xCB3E};
    constexpr Opcode SHIFT_RIGHT_LOGICAL_A                      {0xCB3F};

    constexpr Opcode BIT_0_OF_B_COMPLEMENT_INTO_ZERO            {0xCB40};
    constexpr Opcode BIT_0_OF_C_COMPLEMENT_INTO_ZERO            {0xCB41};
    constexpr Opcode BIT_0_OF_D_COMPLEMENT_INTO_ZERO            {0xCB42};
    constexpr Opcode BIT_0_OF_E_COMPLEMENT_INTO_ZERO            {0xCB43};
    constexpr Opcode BIT_0_OF_H_COMPLEMENT_INTO_ZERO            {0xCB44};
    constexpr Opcode BIT_0_OF_L_COMPLEMENT_INTO_ZERO            {0xCB45};
    constexpr Opcode BIT_0_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   {0xCB46};
    constexpr Opcode BIT_0_OF_A_COMPLEMENT_INTO_ZERO            {0xCB47};
    constexpr Opcode BIT_1_OF_B_COMPLEMENT_INTO_ZERO            {0xCB48};
    constexpr Opcode BIT_1_OF_C_COMPLEMENT_INTO_ZERO            {0xCB49};
    constexpr Opcode BIT_1_OF_D_COMPLEMENT_INTO_ZERO            {0xCB4A};
    constexpr Opcode BIT_1_OF_E_COMPLEMENT_INTO_ZERO            {0xCB4B};
    constexpr Opcode BIT_1_OF_H_COMPLEMENT_INTO_ZERO            {0xCB4C};
    constexpr Opcode BIT_1_OF_L_COMPLEMENT_INTO_ZERO            {0xCB4D};
    constexpr Opcode BIT_1_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   {0xCB4E};
    constexpr Opcode BIT_1_OF_A_COMPLEMENT_INTO_ZERO            {0xCB4F};

    constexpr Opcode BIT_2_OF_B_COMPLEMENT_INTO_ZERO            {0xCB50};
    constexpr Opcode BIT_2_OF_C_COMPLEMENT_INTO_ZERO            {0xCB51};
    constexpr Opcode BIT_2_OF_D_COMPLEMENT_INTO_ZERO            {0xCB52};
    constexpr Opcode BIT_2_OF_E_COMPLEMENT_INTO_ZERO            {0xCB53};
    constexpr Opcode BIT_2_OF_H_COMPLEMENT_INTO_ZERO            {0xCB54};
    constexpr Opcode BIT_2_OF_L_COMPLEMENT_INTO_ZERO            {0xCB55};
    constexpr Opcode BIT_2_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   {0xCB56};
    constexpr Opcode BIT_2_OF_A_COMPLEMENT_INTO_ZERO            {0xCB57};
    constexpr Opcode BIT_3_OF_B_COMPLEMENT_INTO_ZERO            {0xCB58};
    constexpr Opcode BIT_3_OF_C_COMPLEMENT_INTO_ZERO            {0xCB59};
    constexpr Opcode BIT_3_OF_D_COMPLEMENT_INTO_ZERO            {0xCB5A};
    constexpr Opcode BIT_3_OF_E_COMPLEMENT_INTO_ZERO            {0xCB5B};
    constexpr Opcode BIT_3_OF_H_COMPLEMENT_INTO_ZERO            {0xCB5C};
    constexpr Opcode BIT_3_OF_L_COMPLEMENT_INTO_ZERO            {0xCB5D};
    constexpr Opcode BIT_3_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   {0xCB5E};
    constexpr Opcode BIT_3_OF_A_COMPLEMENT_INTO_ZERO            {0xCB5F};

    constexpr Opcode BIT_4_OF_B_COMPLEMENT_INTO_ZERO            {0xCB60};
    constexpr Opcode BIT_4_OF_C_COMPLEMENT_INTO_ZERO            {0xCB61};
    constexpr Opcode BIT_4_OF_D_COMPLEMENT_INTO_ZERO            {0xCB62};
    constexpr Opcode BIT_4_OF_E_COMPLEMENT_INTO_ZERO            {0xCB63};
    constexpr Opcode BIT_4_OF_H_COMPLEMENT_INTO_ZERO            {0xCB64};
    constexpr Opcode BIT_4_OF_L_COMPLEMENT_INTO_ZERO            {0xCB65};
    constexpr Opcode BIT_4_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   {0xCB66};
    constexpr Opcode BIT_4_OF_A_COMPLEMENT_INTO_ZERO            {0xCB67};
    constexpr Opcode BIT_5_OF_B_COMPLEMENT_INTO_ZERO            {0xCB68};
    constexpr Opcode BIT_5_OF_C_COMPLEMENT_INTO_ZERO            {0xCB69};
    constexpr Opcode BIT_5_OF_D_COMPLEMENT_INTO_ZERO            {0xCB6A};
    constexpr Opcode BIT_5_OF_E_COMPLEMENT_INTO_ZERO            {0xCB6B};
    constexpr Opcode BIT_5_OF_H_COMPLEMENT_INTO_ZERO            {0xCB6C};
    constexpr Opcode BIT_5_OF_L_COMPLEMENT_INTO_ZERO            {0xCB6D};
    constexpr Opcode BIT_5_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   {0xCB6E};
    constexpr Opcode BIT_5_OF_A_COMPLEMENT_INTO_ZERO            {0xCB6F};

    constexpr Opcode BIT_6_OF_B_COMPLEMENT_INTO_ZERO            {0xCB70};
    constexpr Opcode BIT_6_OF_C_COMPLEMENT_INTO_ZERO            {0xCB71};
    constexpr Opcode BIT_6_OF_D_COMPLEMENT_INTO_ZERO            {0xCB72};
    constexpr Opcode BIT_6_OF_E_COMPLEMENT_INTO_ZERO            {0xCB73};
    constexpr Opcode BIT_6_OF_H_COMPLEMENT_INTO_ZERO            {0xCB74};
    constexpr Opcode BIT_6_OF_L_COMPLEMENT_INTO_ZERO            {0xCB75};
    constexpr Opcode BIT_6_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   {0xCB76};
    constexpr Opcode BIT_6_OF_A_COMPLEMENT_INTO_ZERO            {0xCB77};
    constexpr Opcode BIT_7_OF_B_COMPLEMENT_INTO_ZERO            {0xCB78};
    constexpr Opcode BIT_7_OF_C_COMPLEMENT_INTO_ZERO            {0xCB79};
    constexpr Opcode BIT_7_OF_D_COMPLEMENT_INTO_ZERO            {0xCB7A};
    constexpr Opcode BIT_7_OF_E_COMPLEMENT_INTO_ZERO            {0xCB7B};
    constexpr Opcode BIT_7_OF_H_COMPLEMENT_INTO_ZERO            {0xCB7C};
    constexpr Opcode BIT_7_OF_L_COMPLEMENT_INTO_ZERO            {0xCB7D};
    constexpr Opcode BIT_7_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   {0xCB7E};
    constexpr Opcode BIT_7_OF_A_COMPLEMENT_INTO_ZERO            {0xCB7F};

    constexpr Opcode RESET_BIT_0_OF_B                           {0xCB80};
    constexpr Opcode RESET_BIT_0_OF_C                           {0xCB81};
    constexpr Opcode RESET_BIT_0_OF_D                           {0xCB82};
    constexpr Opcode RESET_BIT_0_OF_E                           {0xCB83};
    constexpr Opcode RESET_BIT_0_OF_H                           {0xCB84};
    constexpr Opcode RESET_BIT_0_OF_L                           {0xCB85};
    constexpr Opcode RESET_BIT_0_OF_ADDRESS_HL                  {0xCB86};
    constexpr Opcode RESET_BIT_0_OF_A                           {0xCB87};
    constexpr Opcode RESET_BIT_1_OF_B                           {0xCB88};
    constexpr Opcode RESET_BIT_1_OF_C                           {0xCB89};
    constexpr Opcode RESET_BIT_1_OF_D                           {0xCB8A};
    constexpr Opcode RESET_BIT_1_OF_E                           {0xCB8B};
    constexpr Opcode RESET_BIT_1_OF_H                           {0xCB8C};
    constexpr Opcode RESET_BIT_1_OF_L                           {0xCB8D};
    constexpr Opcode RESET_BIT_1_OF_ADDRESS_HL                  {0xCB8E};
    constexpr Opcode RESET_BIT_1_OF_A                           {0xCB8F};

    constexpr Opcode RESET_BIT_2_OF_B                           {0xCB90};
    constexpr Opcode RESET_BIT_2_OF_C                           {0xCB91};
    constexpr Opcode RESET_BIT_2_OF_D                           {0xCB92};
    constexpr Opcode RESET_BIT_2_OF_E                           {0xCB93};
    constexpr Opcode RESET_BIT_2_OF_H                           {0xCB94};
    constexpr Opcode RESET_BIT_2_OF_L                           {0xCB95};
    constexpr Opcode RESET_BIT_2_OF_ADDRESS_HL                  {0xCB96};
    constexpr Opcode RESET_BIT_2_OF_A                           {0xCB97};
    constexpr Opcode RESET_BIT_3_OF_B                           {0xCB98};
    constexpr Opcode RESET_BIT_3_OF_C                           {0xCB99};
    constexpr Opcode RESET_BIT_3_OF_D                           {0xCB9A};
    constexpr Opcode RESET_BIT_3_OF_E                           {0xCB9B};
    constexpr Opcode RESET_BIT_3_OF_H                           {0xCB9C};
    constexpr Opcode RESET_BIT_3_OF_L                           {0xCB9D};
    constexpr Opcode RESET_BIT_3_OF_ADDRESS_HL                  {0xCB9E};
    constexpr Opcode RESET_BIT_3_OF_A                           {0xCB9F};

    constexpr Opcode RESET_BIT_4_OF_B                           {0xCBA0};
    constexpr Opcode RESET_BIT_4_OF_C                           {0xCBA1};
    constexpr Opcode RESET_BIT_4_OF_D                           {0xCBA2};
    constexpr Opcode RESET_BIT_4_OF_E                           {0xCBA3};
    constexpr Opcode RESET_BIT_4_OF_H                           {0xCBA4};
    constexpr Opcode RESET_BIT_4_OF_L                           {0xCBA5};
    constexpr Opcode RESET_BIT_4_OF_ADDRESS_HL                  {0xCBA6};
    constexpr Opcode RESET_BIT_4_OF_A                           {0xCBA7};
    constexpr Opcode RESET_BIT_5_OF_B                           {0xCBA8};
    constexpr Opcode RESET_BIT_5_OF_C                           {0xCBA9};
    constexpr Opcode RESET_BIT_5_OF_D                           {0xCBAA};
    constexpr Opcode RESET_BIT_5_OF_E                           {0xCBAB};
    constexpr Opcode RESET_BIT_5_OF_H                           {0xCBAC};
    constexpr Opcode RESET_BIT_5_OF_L                           {0xCBAD};
    constexpr Opcode RESET_BIT_5_OF_ADDRESS_HL                  {0xCBAE};
    constexpr Opcode RESET_BIT_5_OF_A                           {0xCBAF};

    constexpr Opcode RESET_BIT_6_OF_B                           {0xCBB0};
    constexpr Opcode RESET_BIT_6_OF_C                           {0xCBB1};
    constexpr Opcode RESET_BIT_6_OF_D                           {0xCBB2};
    constexpr Opcode RESET_BIT_6_OF_E                           {0xCBB3};
    constexpr Opcode RESET_BIT_6_OF_H                           {0xCBB4};
    constexpr Opcode RESET_BIT_6_OF_L                           {0xCBB5};
    constexpr Opcode RESET_BIT_6_OF_ADDRESS_HL                  {0xCBB6};
    constexpr Opcode RESET_BIT_6_OF_A                           {0xCBB7};
    constexpr Opcode RESET_BIT_7_OF_B                           {0xCBB8};
    constexpr Opcode RESET_BIT_7_OF_C                           {0xCBB9};
    constexpr Opcode RESET_BIT_7_OF_D                           {0xCBBA};
    constexpr Opcode RESET_BIT_7_OF_E                           {0xCBBB};
    constexpr Opcode RESET_BIT_7_OF_H                           {0xCBBC};
    constexpr Opcode RESET_BIT_7_OF_L                           {0xCBBD};
    constexpr Opcode RESET_BIT_7_OF_ADDRESS_HL                  {0xCBBE};
    constexpr Opcode RESET_BIT_7_OF_A                           {0xCBBF};

    constexpr Opcode SET_BIT_0_OF_B                             {0xCBC0};
    constexpr Opcode SET_BIT_0_OF_C                             {0xCBC1};
    constexpr Opcode SET_BIT_0_OF_D                             {0xCBC2};
    constexpr Opcode SET_BIT_0_OF_E                             {0xCBC3};
    constexpr Opcode SET_BIT_0_OF_H                             {0xCBC4};
    constexpr Opcode SET_BIT_0_OF_L                             {0xCBC5};
    constexpr Opcode SET_BIT_0_OF_ADDRESS_HL                    {0xCBC6};
    constexpr Opcode SET_BIT_0_OF_A                             {0xCBC7};
    constexpr Opcode SET_BIT_1_OF_B                             {0xCBC8};
    constexpr Opcode SET_BIT_1_OF_C                             {0xCBC9};
    constexpr Opcode SET_BIT_1_OF_D                             {0xCBCA};
    constexpr Opcode SET_BIT_1_OF_E                             {0xCBCB};
    constexpr Opcode SET_BIT_1_OF_H                             {0xCBCC};
    constexpr Opcode SET_BIT_1_OF_L                             {0xCBCD};
    constexpr Opcode SET_BIT_1_OF_ADDRESS_HL                    {0xCBCE};
    constexpr Opcode SET_BIT_1_OF_A                             {0xCBCF};

    constexpr Opcode SET_BIT_2_OF_B                             {0xCBD0};
    constexpr Opcode SET_BIT_2_OF_C                             {0xCBD1};
    constexpr Opcode SET_BIT_2_OF_D                             {0xCBD2};
    constexpr Opcode SET_BIT_2_OF_E                             {0xCBD3};
    constexpr Opcode SET_BIT_2_OF_H                             {0xCBD4};
    constexpr Opcode SET_BIT_2_OF_L                             {0xCBD5};
    constexpr Opcode SET_BIT_2_OF_ADDRESS_HL                    {0xCBD6};
    constexpr Opcode SET_BIT_2_OF_A                             {0xCBD7};
    constexpr Opcode SET_BIT_3_OF_B                             {0xCBD8};
    constexpr Opcode SET_BIT_3_OF_C                             {0xCBD9};
    constexpr Opcode SET_BIT_3_OF_D                             {0xCBDA};
    constexpr Opcode SET_BIT_3_OF_E                             {0xCBDB};
    constexpr Opcode SET_BIT_3_OF_H                             {0xCBDC};
    constexpr Opcode SET_BIT_3_OF_L                             {0xCBDD};
    constexpr Opcode SET_BIT_3_OF_ADDRESS_HL                    {0xCBDE};
    constexpr Opcode SET_BIT_3_OF_A                             {0xCBDF};

    constexpr Opcode SET_BIT_4_OF_B                             {0xCBE0};
    constexpr Opcode SET_BIT_4_OF_C                             {0xCBE1};
    constexpr Opcode SET_BIT_4_OF_D                             {0xCBE2};
    constexpr Opcode SET_BIT_4_OF_E                             {0xCBE3};
    constexpr Opcode SET_BIT_4_OF_H                             {0xCBE4};
    constexpr Opcode SET_BIT_4_OF_L                             {0xCBE5};
    constexpr Opcode SET_BIT_4_OF_ADDRESS_HL                    {0xCBE6};
    constexpr Opcode SET_BIT_4_OF_A                             {0xCBE7};
    constexpr Opcode SET_BIT_5_OF_B                             {0xCBE8};
    constexpr Opcode SET_BIT_5_OF_C                             {0xCBE9};
    constexpr Opcode SET_BIT_5_OF_D                             {0xCBEA};
    constexpr Opcode SET_BIT_5_OF_E                             {0xCBEB};
    constexpr Opcode SET_BIT_5_OF_H                             {0xCBEC};
    constexpr Opcode SET_BIT_5_OF_L                             {0xCBED};
    constexpr Opcode SET_BIT_5_OF_ADDRESS_HL                    {0xCBEE};
    constexpr Opcode SET_BIT_5_OF_A                             {0xCBEF};

    constexpr Opcode SET_BIT_6_OF_B                             {0xCBF0};
    constexpr Opcode SET_BIT_6_OF_C                             {0xCBF1};
    constexpr Opcode SET_BIT_6_OF_D                             {0xCBF2};
    constexpr Opcode SET_BIT_6_OF_E                             {0xCBF3};
    constexpr Opcode SET_BIT_6_OF_H                             {0xCBF4};
    constexpr Opcode SET_BIT_6_OF_L                             {0xCBF5};
    constexpr Opcode SET_BIT_6_OF_ADDRESS_HL                    {0xCBF6};
    constexpr Opcode SET_BIT_6_OF_A                             {0xCBF7};
    constexpr Opcode SET_BIT_7_OF_B                             {0xCBF8};
    constexpr Opcode SET_BIT_7_OF_C                             {0xCBF9};
    constexpr Opcode SET_BIT_7_OF_D                             {0xCBFA};
    constexpr Opcode SET_BIT_7_OF_E                             {0xCBFB};
    constexpr Opcode SET_BIT_7_OF_H                             {0xCBFC};
    constexpr Opcode SET_BIT_7_OF_L                             {0xCBFD};
    constexpr Opcode SET_BIT_7_OF_ADDRESS_HL                    {0xCBFE};
    constexpr Opcode SET_BIT_7_OF_A                             {0xCBFF};

    constexpr Opcode INVALID_OPCODE                             {0xFFFF};
}

#endif //GAMEBOY_DISASSEMBLE_CONSTANTS_H
