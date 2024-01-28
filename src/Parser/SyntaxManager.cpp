#include "SyntaxManager.hpp"

namespace SyntaxManager
{
    const std::vector<std::string> illegalRepeats = { "Keyword", "Identifier", "Number", "String", "Operator" };

    const std::unordered_map<std::string, std::vector<std::string>> expectedAfter = {
        { "Keyword", { "Null" } },
        { "Identifier", { "Operator", "Punctuation" } },
        { "Type", { "Identifier" } },
        { "Punctuation", { "Identifier", "Number", "String", "Operator", "Punctuation" } },
        { "Operator", { "Identifier", "Number", "String", "Punctuation" } },
        { "Number", { "Operator", "Punctuation" } },
        { "String", { "Operator", "Punctuation" } }
    };

    void CheckIllegalRepeat(std::vector<std::shared_ptr<Token>> tokens)
    {
        std::string type = tokens[0]->GetType();

        if (std::find(illegalRepeats.begin(), illegalRepeats.end(), type) == illegalRepeats.end() && tokens.size() == 2)
            return;

        for (auto token : tokens)
        {
            if (token->GetType() != type)
                return;
        }

        std::transform(type.begin(), type.end(), type.begin(), ::tolower);

        std::string message = "Unexpected " + type;
        size_t line = tokens[0]->GetLine();

        SYNTAX_ERROR(message, line);
    }

    void CheckIfExpected(std::vector<std::shared_ptr<Token>> tokens)
    {
        std::string type = tokens[0]->GetType();
        std::string nextType = tokens[1]->GetType();

        const auto key = expectedAfter.find(type);

        if (key != expectedAfter.end())
        {
            const auto& expected = key->second;

            bool found = false;

            for (auto& expectedType : expected)
            {
                if (nextType == expectedType)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                std::transform(type.begin(), type.end(), type.begin(), ::tolower);
                std::transform(nextType.begin(), nextType.end(), nextType.begin(), ::tolower);

                std::string message = "Unexpected " + nextType + " after " + type;
                size_t line = tokens[0]->GetLine();

                SYNTAX_ERROR(message, line);
            }
        }
    }

    bool IsExpressionValid(std::vector<std::shared_ptr<Token>> tokens)
    {
        int operandCount = 0;
        int operatorCount = 0;
        int leftParenthesisCount = 0;
        int rightParenthesisCount = 0;

        for (auto& token : tokens)
        {
            if (token->GetType() == "Operator")
                operatorCount++;
            else if (token->GetType() == "Number" || token->GetType() == "String" || token->GetType() == "Identifier")
                operandCount++;
            else if (token->GetValue() == "(")
                leftParenthesisCount++;
            else if (token->GetValue() == ")")
                rightParenthesisCount++;
            else
                return false;
        }

        if (operandCount != operatorCount + 1)
            return false;
        
        if (leftParenthesisCount != rightParenthesisCount)
            return false;
        
        return true;
    }

    bool IsVariableNameValid(std::string name)
    {
        if (name.size() == 0)
            return false;

        if (name[0] >= '0' && name[0] <= '9')
            return false;

        for (auto& c : name)
        {
            if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '_'))
                return false;
        }

        return true;
    }
};