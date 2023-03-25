#pragma once

#include "Lexer.hpp"
#include "./Nodes/NodeManager.hpp"
#include "./Util/ErrorManager.hpp"

#include <unordered_map>

class Parser
{
public:
    Parser(std::vector<std::shared_ptr<Token>>& tokens) : tokens(tokens) {};

    std::vector<std::shared_ptr<Node>> Parse();

    void AnalyzeSyntax();

    void GenerateAST();

    void CheckIllegalRepeat(std::vector<std::shared_ptr<Token>>& tokens);

    void CheckIfExpected(std::vector<std::shared_ptr<Token>>& tokens);

    std::vector<std::vector<std::shared_ptr<Token>>> GetTokensLines();

    std::shared_ptr<Node> GetBinaryExpression(std::vector<std::shared_ptr<Token>>& tokens);

    std::string GetTypeByIndex(const std::vector<std::shared_ptr<Token>>& tokens, const size_t& index);
    std::string GetValueByIndex(const std::vector<std::shared_ptr<Token>>& tokens, const size_t& index);
    
    template <typename N>
    std::shared_ptr<Node> AddNode(const std::vector<std::any>& attributes);

private:
    std::vector<std::shared_ptr<Token>> tokens;
    std::vector<std::shared_ptr<Node>> AST;

    const std::unordered_map<std::string, std::vector<std::string>> expectedAfter = {
        { "Keyword", { "Null" } },
        { "Identifier", { "Operator", "Punctuation" } },
        { "Type", { "Identifier" } },
        { "Punctuation", { "Identifier", "Numeric", "String", "Punctuation" } },
        { "Operator", { "Identifier", "Numeric", "String" } },
        { "Numeric", { "Operator", "Punctuation" } },
        { "String", { "Operator", "Punctuation" } }
    };

    const std::vector<std::string> illegalRepeats = { "Keyword", "Identifier", "Numeric", "String", "Operator" };
};

#define SYNTAX_ERROR(MSG, LINE) ErrorManager::GetInstance()->SyntaxError(MSG, LINE);