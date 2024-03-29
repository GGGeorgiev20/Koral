#include "TokenManager.hpp"

namespace TokenManager
{
    std::string GetTypeByIndex(std::vector<std::shared_ptr<Token>> tokens, size_t index)
    {
        if (index < tokens.size())
            return tokens[index]->GetType();
        else
            return "Null";
    }

    std::string GetValueByIndex(std::vector<std::shared_ptr<Token>> tokens, size_t index)
    {
        if (index < tokens.size())
            return tokens[index]->GetValue();
        else
            return "Null";
    }
};