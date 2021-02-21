#ifndef GAMEBOY_DISASSEMBLE_ASSEMBLER_H
#define GAMEBOY_DISASSEMBLE_ASSEMBLER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Token = std::string;

//enum class TokenType {
//    IDENTIFIER,
//    COMMA,
//    NUMBER,
//};
//
//enum class TokenizerState {
//    DETERMINE_STATE,
//
//};
//
//class Tokenizer
//{
//public:
//    Tokenizer(const std::string str)
//    : _string(str)
//    {
//
//    }
//
//private:
//    std::string _string{};
//    size_t _currentPosition{0};
//
//};

using VectorOfTokens = std::vector<Token>;

//class Token {
//};

VectorOfTokens tokenize_line(const std::string& line)
{

    VectorOfTokens outputVector;
    outputVector.reserve(20);

    std::string currentToken{};

    bool inComment = false;

    for (const auto character : line)
    {
        if (inComment) {
            if (character == '\n')
            {
                inComment = false;
            }
            continue;
        }

        if (isspace(character))
        {
            if (!currentToken.empty())
            {
                outputVector.push_back(currentToken);
                currentToken = "";
            }
        }
        else if (character == '(')
        {
            if (!currentToken.empty())
            {
                outputVector.push_back(currentToken);
            }

            currentToken = character;
            outputVector.push_back(currentToken);
            currentToken = "";
        }
        else if (character == ')')
        {
            if (!currentToken.empty())
            {
                outputVector.push_back(currentToken);
            }

            currentToken = character;
            outputVector.push_back(currentToken);
            currentToken = "";
        }
        else if (character == ',')
        {
            if (!currentToken.empty())
            {
                outputVector.push_back(currentToken);
            }

            currentToken = character;
            outputVector.push_back(currentToken);
            currentToken = "";
        }
        else if (character == ';')
        {
            if (!currentToken.empty())
            {
                outputVector.push_back(currentToken);
            }

            currentToken = "";
            inComment = true;
        }
        else {
            currentToken += character;
        }
    }

    if (!currentToken.empty())
    {
        outputVector.push_back(currentToken);
    }

    return outputVector;

}

void print_vector_of_tokens(const VectorOfTokens& vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << "Token " << i << " : " << vec[i] << std::endl;
    }
}



#endif //GAMEBOY_DISASSEMBLE_ASSEMBLER_H
