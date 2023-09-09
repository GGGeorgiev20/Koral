#pragma once

#include "../Token.hpp"
#include "../Util/ErrorManager.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_map>

namespace SyntaxManager
{
    void CheckIllegalRepeat(std::vector<std::shared_ptr<Token>>& tokens);

    void CheckIfExpected(std::vector<std::shared_ptr<Token>>& tokens);

    bool IsVariableNameValid(std::string name);

    bool IsExpressionValid(std::vector<std::shared_ptr<Token>>& tokens);
};

#define SYNTAX_ERROR(MSG, LINE) ErrorManager::GetInstance()->SyntaxError(MSG, LINE);