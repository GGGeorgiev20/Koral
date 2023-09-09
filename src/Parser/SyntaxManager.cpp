#include "SyntaxManager.hpp"

namespace SyntaxManager
{
    const std::vector<std::string> illegalRepeats = { "Keyword", "Identifier", "Numeric", "String", "Operator" };

    const std::unordered_map<std::string, std::vector<std::string>> expectedAfter = {
        { "Keyword", { "Null" } },
        { "Identifier", { "Operator", "Punctuation" } },
        { "Type", { "Identifier" } },
        { "Punctuation", { "Identifier", "Numeric", "String", "Operator", "Punctuation" } },
        { "Operator", { "Identifier", "Numeric", "String", "Punctuation" } },
        { "Numeric", { "Operator", "Punctuation" } },
        { "String", { "Operator", "Punctuation" } }
    };

    void CheckIllegalRepeat(std::vector<std::shared_ptr<Token>>& tokens)
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

    void CheckIfExpected(std::vector<std::shared_ptr<Token>>& tokens)
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

    bool IsExpressionValid(std::vector<std::shared_ptr<Token>>& tokens)
    {
        int operandCount = 0;
        int operatorCount = 0;
        int leftParanthesisCount = 0;
        int rightParanthesisCount = 0;

        for (auto& token : tokens)
        {
            if (token->GetType() == "Operator")
                operatorCount++;
            else if (token->GetType() == "Numeric" || token->GetType() == "String" || token->GetType() == "Identifier")
                operandCount++;
            else if (token->GetValue() == "(")
                leftParanthesisCount++;
            else if (token->GetValue() == ")")
                rightParanthesisCount++;
            else
                return false;
        }

        if (operandCount != operatorCount + 1)
            return false;
        
        if (leftParanthesisCount != rightParanthesisCount)
            return false;
        
        return true;
    }
};