#include "Compiler.hpp"

int main(int argc, char* argv[])
{
    // TODO: Implement the new build system into the Koral compiler

    // TODO: Add a logging module, that works only in dev mode
    // NOTE: Will also be good to add a list of errors, so all instances of an error can be changed at one time

    Compiler *compiler = new Compiler(argc, argv);

    compiler->Compile();

    return 0;
}