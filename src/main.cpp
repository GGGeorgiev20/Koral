#include "Compiler.hpp"

int main(int argc, char* argv[])
{
    Compiler *compiler = new Compiler(argc, argv);

    compiler->Compile();

    return 0;
}