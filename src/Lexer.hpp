#pragma once

#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>
#include <cassert>

class Token
{
public:
    Token(std::string& value, size_t& line);

    void SetType(std::string& type) { this->type = type; }
    void SetValue(std::string& value) { this->value = value; }

    std::string GetType() { return type; }
    std::string GetValue() { return value; }
    size_t GetLine() { return line; };

private:
    std::string type;
    std::string value;
    size_t line;
};

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
    
    const std::string operators = "+-*/%&|!^~<>=";
    const std::string punctuation = ".,:;(){}[]";
    
    const std::vector<std::string> keywords = { "if", "else", "for", "while", "do", "return", "break", "continue" };
    const std::vector<std::string> types = { "int", "float", "char", "string", "bool" };
};