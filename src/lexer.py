import json

PUNCTUATION = [ '+', '-', '*', '/', '%', '=', ',', '(', ')' ]
KEYWORDS = [ 'var' ]

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
        self.lines = []

    def execute(self):
        self.scan(self.koral_file)
        self.evaluate(self.lexemes, self.tokens)
        self.generate_token_base(self.tokens, self.token_file)

    def scan(self, file):
        with open(file, 'r') as f:
            in_string = False
            lexeme_count = len(self.lexemes)
            for index, line in enumerate(f.readlines()):
                current = ''
                for i in range(len(line)):
                    if line[i] == '"':
                        current += line[i]
                        if in_string:
                            self.lexemes.append(current)
                            current = ''
                        in_string = not in_string
                    elif line[i] in PUNCTUATION and not in_string:
                        if current != '':
                            self.lexemes.append(current)
                        self.lexemes.append(line[i])
                        current = ''
                    elif line[i] != ' ' or in_string:
                        current += line[i]
                    if current in KEYWORDS:
                        self.lexemes.append(current)
                        current = ''
                    if i == len(line) - 1 and (in_string or current != ''):
                        self.lexemes.append(current)
                    if line[i] == ' ' and not in_string:
                        if current != '':
                            self.lexemes.append(current)
                        current = ''
                    for i in range(len(self.lexemes) - lexeme_count):
                        self.lines.append(index + 1)
                    lexeme_count = len(self.lexemes)

    def process_unary(self, tokens):
        for index, token in enumerate(tokens):
            if tokens[index-1].type == 'Operator' and token.type == 'Operator' and tokens[index+1].type == 'Numeric':
                token.value += tokens[index+1].value
                token.type = 'Numeric'
                tokens.pop(index+1)

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
        for index, lexeme in enumerate(lexemes):
            if lexeme == '\n':
                continue
            
            type = self.determine_type(lexeme)
            tokens.append(Token(type, lexeme, self.lines[index]))
        self.process_unary(tokens)

    def generate_token_base(self, tokens, token_base):
        token_list = []
        with open(token_base, 'w') as f:
            for token in tokens:
                token_list.append({"type": token.type, "value": token.value})
            json.dump(token_list, f, indent=4)