import os
import json

class Token:
    def __init__(self, type, value):
        self.type = type
        self.value = value

class Error:
    def __init__(self, file, line, message):
        self.file = file
        self.line = line
        self.message = f"    File \"{os.path.join(os.getcwd(), file)}\", line {self.line} {message}"

class Lexer:
    def __init__(self, bace_file, token_file):
        self.bace_file = bace_file
        self.token_file = token_file
        self.lexemes = []
        self.tokens = []
        self.errors = []
        self.line = 1
        self.is_defining = False

    def execute(self):
        self.scan(self.bace_file)
        self.evaluate(self.lexemes, self.tokens)
        self.generate_token_base(self.tokens, self.token_file)

    def scan(self, file):
        with open(file, 'r') as f:
            for line in f.readlines():
                for lexeme in line.split():
                    self.lexemes.append(lexeme)
                self.lexemes.append('\n')

    # def pre_process(self, lexemes):
    #     for index, lexeme in enumerate(lexemes):
    #         pass

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
        type = {
            'var': 'Keyword',
            '=': 'Punctuator',
            '\'': 'Punctuator',
            '\"': 'Punctuator',
            '+': 'Operator',
            '-': 'Operator',
            '*': 'Operator',
            '/': 'Operator'
        }.get(lexeme, 'Identifier')

        if lexeme == '\n':
            self.line += 1
            self.is_defining = False
            return 0

        if self.is_defining == True and type == 'Identifier':
            type = 'Literal'
        
        if type == 'Identifier':
            self.is_defining = True

        return type

    def evaluate(self, lexemes, tokens):
        # self.pre_process(lexemes)
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
            json.dump(token_list, f, indent = 4)

def run():
    bace_file = 'main.kor'
    token_file = os.path.join('data', 'token_base.json')

    lexer = Lexer(bace_file, token_file)
    lexer.execute()

run()