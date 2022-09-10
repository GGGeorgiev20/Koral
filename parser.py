import json

class Error:
    def __init__(self, message, line):
        self.message = message
        self.line = line

class Parser:
    def __init__(self, tokens, ast_file):
        self.ast_file = ast_file
        self.tokens = tokens
        self.current = None
        self.index = -1
        self.ast = {}
        self.errors = []
        self.result = ''
        self.advance()

    def parse(self):
        self.check_syntax()
        self.generate_ast(self.ast_file)

    def check_syntax(self):
        lines = self.get_lines(self.tokens)
        for line in lines:
           print(self.generate_expression(line))

    def get_lines(self, tokens):
        result = []
        for line in range(1, tokens[-1].line + 1):
            result.append([token for token in tokens if token.line == line])
        return result

    def generate_ast(self, ast_file):
        self.ast = {
            "type": "Program",
            "body": [],
            "sourceType": "script"
        }

        with open(ast_file, 'w') as f:
            json.dump(self.ast, f, indent=4)

    def declare_variable(self, name, value):
        variable = {
            "type": "VariableDeclaration",
            "declarations": [
                {
                    "type": "VariableDeclarator",
                    "id": {
                        "type": "Identifier",
                        "name": f"{name}"
                    },
                    "init": {
                        "type": "Literal",
                        "value": value,
                        "raw": f"{value}"
                    }
                }
            ],
            "kind": "var"
        }

        self.ast['body'].append(variable)

    def generate_expression(self, tokens, res=''):
        result = res
        result += f" {tokens[0].value}"
        if tokens[0].value not in '+-' and res != '': 
            result += ')'
        if len(tokens) > 1:
            result = self.generate_expression(tokens[1:], result)
        else:
            result = '(' * result.count(')') + result[1:]
        return result

    def advance(self):
        self.index += 1
        if self.index < len(self.tokens):
            self.current = self.tokens[self.index]