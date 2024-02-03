#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include <algorithm>

#include "Token.hpp"

class Lexer
{
public:
    Lexer(std::string content) : content(content) {};

    std::vector<std::shared_ptr<Token>> Lex();

    void Scan();

    void Evaluate();

    void PostProcess();

    void ProccessCharacter(char character, std::string& lexeme, bool& inString, size_t line);

    std::string DetermineType(std::string lexeme);

    std::vector<std::string> ReadLines();

    bool AreForwarded(std::vector<std::shared_ptr<Token>> tokens, std::vector<std::string> expected);

    void AddToken(std::string& lexeme, size_t line);

private:
    std::string content;
    std::vector<std::shared_ptr<Token>> tokens;
    
    const std::string operators = "+-*/%=";
    const std::string punctuation = ".,:;(){}[]";
    
    const std::vector<std::string> keywords = { "if", "else", "for", "while", "do", "return", "break", "continue" };
    const std::vector<std::string> types = { "int", "float", "char", "string", "bool" };
};