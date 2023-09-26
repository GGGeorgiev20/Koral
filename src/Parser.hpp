#pragma once

#include "./Lexer.hpp"
#include "./Nodes/NodeManager.hpp"

#include "./Parser/ExpressionConstructor.hpp"
#include "./Parser/SyntaxManager.hpp"
#include "./Parser/TokenManager.hpp"

class Parser
{
public:
    Parser(std::vector<std::shared_ptr<Token>>& tokens) : tokens(tokens) {};

    std::vector<std::shared_ptr<Node>> Parse();

    std::vector<std::vector<std::shared_ptr<Token>>> GetTokensLines();

    void AnalyzeSyntax();

    void GenerateAST();

    std::shared_ptr<Node> GetBinaryExpression(std::vector<std::shared_ptr<Token>>& tokens);
   
    template <typename N>
    std::shared_ptr<Node> AddNode(const std::vector<std::any>& attributes);

private:
    std::vector<std::shared_ptr<Token>> tokens;
    std::vector<std::shared_ptr<Node>> AST;
};