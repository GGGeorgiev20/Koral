import os
import json

PUNCTUATION = [ '+', '-', '*', '/', '=', '(', ')' ]
KEYWORDS = ['var', 'say']

class Token:
    def __init__(self, type, value):
        self.type = type
        self.value = value

class Lexer:
    def __init__(self, koral_file, token_file):
        self.koral_file = koral_file
        self.token_file = token_file
        self.lexemes = []
        self.tokens = []

    def execute(self):
        self.scan(self.koral_file)
        self.evaluate(self.lexemes, self.tokens)
        # self.generate_token_base(self.tokens, self.token_file)

    def scan(self, file):
        with open(file, 'r') as f:
            for line in f.readlines():
                indexes = {}

                line = line.replace(' ', '')
                for lex in PUNCTUATION:
                    while lex in line:
                        indexes[line.find(lex)] = lex
                        line = line.replace(lex, '¿', 1)
                
                for keyword in KEYWORDS:
                    while keyword in line:
                        indexes[line.find(keyword)] = keyword
                        line = line.replace(keyword, '¿', 1)

                while '¿' in line:
                    for index in sorted(indexes):
                        line = line.replace('¿', f' {indexes[index]} ', 1)

                for lexeme in line.split():
                    self.lexemes.append(lexeme)
                self.lexemes.append('\n')

    def post_process(self, tokens):
        for token in tokens:
            if token.type == 'Literal':
                if token.value.isdigit():
                    token.type = 'Numeric'
                elif token.value[0] == '\'' or token.value[0] == '\"':
                    token.type = 'String'
                else:
                    token.type = 'Identifier'

    def determine_type(self, lexeme):
        digits = '0123456789'
        type = {
            '=': 'Punctuator',
            '\'': 'Punctuator',
            '\"': 'Punctuator',
            '+': 'Operator',
            '-': 'Operator',
            '*': 'Operator',
            '/': 'Operator'
        }.get(lexeme, 'Identifier')
        return type

    def evaluate(self, lexemes, tokens):
        for lexeme in lexemes:
            type = self.determine_type(lexeme)

            if not type == 0:
                tokens.append(Token(type, lexeme))
        self.post_process(tokens)

    def generate_token_base(self, tokens, token_base):
        token_list = []
        with open(token_base, 'w') as f:
            for token in tokens:
                token_list.append({"type": token.type, "value": token.value})
            json.dump(token_list, f, indent=4)

def run():
    koral_file = 'main.kor'
    token_file = os.path.join('data', 'token_base.json')

    lexer = Lexer(koral_file, token_file)
    lexer.execute()
    print(lexer.lexemes)

run()