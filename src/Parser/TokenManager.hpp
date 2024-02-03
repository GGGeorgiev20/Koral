#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../Token.hpp"

namespace TokenManager
{
    std::string GetTypeByIndex(std::vector<std::shared_ptr<Token>> tokens, size_t index);

    std::string GetValueByIndex(std::vector<std::shared_ptr<Token>> tokens, size_t index);
};