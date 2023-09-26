#include "./TokenManager.hpp"

namespace TokenManager
{
    std::string GetTypeByIndex(const std::vector<std::shared_ptr<Token>>& tokens, const size_t& index)
    {
        if (index < tokens.size())
            return tokens[index]->GetType();
        else
            return "Null";
    }

    std::string GetValueByIndex(const std::vector<std::shared_ptr<Token>>& tokens, const size_t& index)
    {
        if (index < tokens.size())
            return tokens[index]->GetValue();
        else
            return "Null";
    }
};