import math
import json

class Error:
    def __init__(self, message, line):
        self.message = message
        self.line = line

class Parser:
    def __init__(self, tokens, ast_file):
        self.ast_file = ast_file
        self.tokens = tokens
        self.ast = {}
        self.errors = []

    def parse(self):
        self.check_syntax()
        self.generate_ast(self.ast_file)

    def check_syntax(self):
        lines = self.get_lines(self.tokens)

    def get_lines(self, tokens):
        result = []
        for line in range(1, tokens[-1].line + 1):
            result.append([token for token in tokens if token.line == line])
        return result

    def generate_ast(self, ast_file):
        self.ast = {
            "type": "Program",
            "body": []
        }

        self.ast["body"].append(self.binary_expression(self.tokens))

        self.ast["sourceType"] = "script"
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

                    }
                }
            ],
            "kind": "var"
        }

        return variable

    def binary_expression(self, tokens):
        template = {
            "type": "BinaryExpression",
            "operator": ""
        }

        operators = []
        indexes = []
        different_strength = False

        has_low = False
        has_high = False
        for index, token in enumerate(tokens):
            if token.type == "Operator":
                if token.value in ['*', '/']:
                    has_high = True
                else:
                    has_low = True
                operators.append(token.value)
                indexes.append(index)
        
        different_strength = has_low and has_high

        middle = math.ceil((len(operators) - 1) / 2)
        if operators[middle] in ['*', '/']:
            if different_strength:
                i = middle
                found_middle = False
                while i < len(operators):
                    if operators[i] in ['+', '-']:
                        middle = i
                        found_middle = True
                        break
                    i += 1
                if not found_middle:
                    i = middle
                    while i >= 0:
                        if operators[i] in ['+', '-']:
                            middle = i
                            break
                        i -= 1

        operator = operators[middle]
        left = self.expression(tokens[:indexes[middle]])
        right = self.expression(tokens[indexes[middle] + 1:])

        template['operator'] = operator
        template['left'] = left
        template['right'] = right

        return template

    def expression(self, tokens):
        if len(tokens) == 1:
            template = {
                "type": "Literal",
                "value": tokens[0].value,
                "raw": tokens[0].value
            }
        else:
            template = self.binary_expression(tokens)

        return template