#pragma once

#include "./Token.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include <cassert>

class Lexer
{
public:
    Lexer(std::string content) : content(content) {};

    std::vector<std::shared_ptr<Token>> Lex();

    void Scan();

    void Evaluate();

    void PostProcess();

    std::string DetermineType(std::string lexeme);

    std::vector<std::string> ReadLines();

    bool AreForwarded(std::vector<std::shared_ptr<Token>> tokens, std::vector<std::string> expected);

    void AddToken(std::string& lexeme, size_t& line);

private:
    std::string content;
    std::vector<std::shared_ptr<Token>> tokens;
    
    const std::string operators = "+-*/%=";
    const std::string punctuation = ".,:;(){}[]";
    
    const std::vector<std::string> keywords = { "if", "else", "for", "while", "do", "return", "break", "continue" };
    const std::vector<std::string> types = { "int", "float", "char", "string", "bool" };
};