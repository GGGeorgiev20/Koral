import json

PUNCTUATION = [ '+', '-', '*', '/', '%', '=', ',', '(', ')' ]
KEYWORDS = ['var', 'say', 'if', 'else']

class Token:
    def __init__(self, type, value, line):
        self.type = type
        self.value = value
        self.line = line

class Lexer:
    def __init__(self, koral_file, token_file):
        self.koral_file = koral_file
        self.token_file = token_file
        self.lexemes = []
        self.tokens = []
        self.line = 1

    def execute(self):
        self.scan(self.koral_file)
        self.evaluate(self.lexemes, self.tokens)
        self.generate_token_base(self.tokens, self.token_file)

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

    def determine_type(self, lexeme):
        if lexeme in KEYWORDS:
            return 'Keyword'

        type = {
            '+': 'Operator',
            '-': 'Operator',
            '*': 'Operator',
            '/': 'Operator',
            '%': 'Operator',
            '=': 'Operator',
            ',': 'Punctuator',
            '(': 'Punctuator',
            ')': 'Punctuator'
        }.get(lexeme, 'Identifier')

        if type == 'Identifier':
            if lexeme[0] == '\'' or lexeme[0] == '\"':
                return 'String'
            try:
                float(lexeme)
            except:
                return type
            return 'Numeric'

        return type

    def evaluate(self, lexemes, tokens):
        for lexeme in lexemes:
            if lexeme == '\n':
                self.line += 1
                continue
            
            type = self.determine_type(lexeme)
            tokens.append(Token(type, lexeme, self.line))

    def generate_token_base(self, tokens, token_base):
        token_list = []
        with open(token_base, 'w') as f:
            for token in tokens:
                token_list.append({"type": token.type, "value": token.value})
            json.dump(token_list, f, indent=4)