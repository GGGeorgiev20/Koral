#pragma once

#include "../Token.hpp"

#include <string>
#include <vector>
#include <memory>

namespace TokenManager
{
    std::string GetTypeByIndex(std::vector<std::shared_ptr<Token>> tokens, size_t index);

    std::string GetValueByIndex(std::vector<std::shared_ptr<Token>> tokens, size_t index);
};