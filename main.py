import os
from lexer import Lexer
from parser import Parser

def main():
    koral_file = 'main.kor'
    token_file = os.path.join('data', 'token_base.json')
    ast_file = os.path.join('data', 'ast.json')

    lexer = Lexer(koral_file, token_file)
    lexer.execute()

    parser = Parser(lexer.tokens, ast_file)
    parser.parse()
    if parser.errors:
        for error in parser.errors:
            print(f'Error: {error.message} on line {error.line}')

if __name__ == '__main__':
    main()