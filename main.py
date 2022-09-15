import os
import sys
from src.lexer import Lexer
from src.parser import Parser
from src.interpreter import Interpreter

koral_file = sys.argv[1]
token_file = os.path.join('data', 'token_base.json')
ast_file = os.path.join('data', 'ast.json')

def format_error(error):
    error.message = f'   File "{os.path.abspath(koral_file)}", line {error.line}:'
    
    with open(koral_file, 'r') as f:
        lines = f.readlines()
        line = lines[error.line - 1]
        error.message += f'\n\t{line}'
        if line[-1] != '\n':
            error.message += '\n'
        error.message += f'   Syntax error: {error.error_message}'
    
    return error.message

def main():
    lexer = Lexer(koral_file, token_file)
    lexer.execute()

    parser = Parser(lexer.tokens, ast_file)
    parser.parse()
    if parser.errors:
        for error in parser.errors:
            print(format_error(error))
        return

    interpreter = Interpreter(parser.ast)
    interpreter.execute()
    if interpreter.errors:
        for error in interpreter.errors:
            print(format_error(error))

if __name__ == '__main__':
    main()