#pragma once

#include "../Token.hpp"

#include <string>
#include <vector>
#include <memory>

namespace TokenManager {
    std::string GetTypeByIndex(const std::vector<std::shared_ptr<Token>>& tokens, const size_t& index);

    std::string GetValueByIndex(const std::vector<std::shared_ptr<Token>>& tokens, const size_t& index);
};