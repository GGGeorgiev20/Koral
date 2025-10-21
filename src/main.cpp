#include "Utils/Utils.hpp"
#include "Utils/Logger.hpp"
#include "Core/Lexer/Lexer.hpp"

#include <memory>
#include <cassert>
#include <filesystem>

int main(int argc, char* argv[])
{
    // todo: argument manager
    nassert(argc >= 2, "Argument count is less than two");
    nassert(std::filesystem::exists(argv[1]), "File doesn't exist");

    std::string content = Utils::ReadFileContent(argv[1]);
    nassert(!content.empty(), "File content is empty");

    auto lexer = std::make_unique<Lexer>(content);
    auto tokens = lexer->Scan();

    for (const auto& token : tokens)
    {
        Logger::Debug(fmt::format("Line {}: Type {} - Value {}", token.line, token.type, token.value));
    }

    return 0;
}
