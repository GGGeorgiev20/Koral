#pragma once

#include <functional>

#include "Lexer.hpp"
#include "Nodes/NodeManager.hpp"

#include "Parser/NodeConstructor.hpp"
#include "Parser/ExpressionConstructor.hpp"
#include "Parser/SyntaxManager.hpp"
#include "Parser/TokenManager.hpp"

class Parser
{
public:
    Parser(std::vector<std::shared_ptr<Token>> tokens) : tokens(tokens) {};

    std::vector<std::shared_ptr<Node>> Parse();

    void AnalyzeSyntax();

    void GenerateAST();

    void ProcessLine(std::vector<std::shared_ptr<Token>> line);

    std::vector<std::vector<std::shared_ptr<Token>>> GetTokensLines();
   
    template <typename N>
    std::shared_ptr<Node> AddNode(std::vector<std::any> attributes);

private:
    std::vector<std::shared_ptr<Token>> tokens;
    std::vector<std::shared_ptr<Node>> AST;
};