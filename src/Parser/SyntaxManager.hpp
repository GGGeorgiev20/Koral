#pragma once

#include "../Token.hpp"
#include "../Util/ErrorManager.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_map>

// TODO: Rework the whole syntax manager

namespace SyntaxManager
{
    void CheckIllegalRepeat(std::vector<std::shared_ptr<Token>> tokens);

    void CheckIfExpected(std::vector<std::shared_ptr<Token>> tokens);

    bool IsExpressionValid(std::vector<std::shared_ptr<Token>> tokens);

    bool IsVariableNameValid(std::string name);
};

#define SYNTAX_ERROR(MSG, LINE) ErrorManager::GetInstance()->SyntaxError(MSG, LINE);