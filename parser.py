import math
import json
import os

koral_file = 'main.kor'

class Error:
    def __init__(self, type, extra, line):
        self.message = ''
        with open(koral_file, 'r') as f:
            lines = f.readlines()
            self.message = f'   File "{os.path.abspath(koral_file)}", line {line}:'
            self.message += f'\n\t{lines[line - 1]}'
            self.message += f'   {type}: {extra}'

class Parser:
    def __init__(self, tokens, ast_file):
        self.ast_file = ast_file
        self.tokens = tokens
        self.ast = {}
        self.errors = []

    def parse(self):
        self.check_syntax()
        self.generate_ast(self.ast_file, self.tokens)

    def check_syntax(self):
        pass

    def get_lines(self, tokens):
        result = []
        for line in range(1, tokens[-1].line + 1):
            result.append([token for token in tokens if token.line == line])
        return result

    def get_short(self, tokens):
        result = ''
        for token in tokens:
            result += token.type[0]
        return result

    def generate_ast(self, ast_file, tokens):
        self.ast = {
            "type": "Program",
            "body": []
        }

        lines = self.get_lines(tokens)

        for line in lines:
            short = self.get_short(line)
            for index, token in enumerate(line):
                if token.value == "var":
                    var_value = short[index + 3:]
                    if 'S' in var_value and 'N' in var_value:
                        self.errors.append(Error("Syntax error", "Invalid addition, cannot add string and numeric types", token.line))
                        return
                    name = line[index + 1].value
                    value = self.binary_expression(line[index + 3:])
                    self.ast['body'].append(self.declare_variable(name, value))
                if (token.type == 'Identifier' or token.value == "say") and index == 0:
                    template = {
                        "type": "ExpressionStatement",
                        "expression": {}
                    }
                    if line[index + 1].value == '=':
                        template['expression'] = self.assign_value(token.value, line[index + 2:])
                    elif line[index + 1].value == '(':
                        name = token.value
                        args = []
                        for arg in line[index + 2:]:
                            if arg.value == ')':
                                break
                            if arg.value == ',':
                                continue
                            args.append(self.binary_expression([arg]))
                        template['expression'] = self.call_function(name, *args)
                    self.ast['body'].append(template)

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
                    "init": {}
                }
            ],
            "kind": "var"
        }

        variable['declarations'][0]['init'] = value

        return variable
    
    def call_function(self, name, *args):
        template = {
            "type": "CallExpression",
            "callee": {
                "type": "Identifier",
                "name": f"{name}"
            },
            "arguments": []
        }

        for arg in args:
            template['arguments'].append(arg)

        return template

    def assign_value(self, variable, value):
        template = {
            "type": "AssignmentExpression",
            "operator": "=",
            "left": {
                "type": "Identifier",
                "name": f"{variable}"
            },
            "right": {}
        }

        template['right'] = self.binary_expression(value)

        return template

    def expression(self, tokens):
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
        left = self.binary_expression(tokens[:indexes[middle]])
        right = self.binary_expression(tokens[indexes[middle] + 1:])

        template['operator'] = operator
        template['left'] = left
        template['right'] = right

        return template

    def binary_expression(self, tokens):
        if len(tokens) == 1:
            is_identifier = tokens[0].type == "Identifier"
            try:
                value = int(tokens[0].value)
            except ValueError:
                try:
                    value = float(tokens[0].value)
                except ValueError:
                    if not is_identifier:
                        value = tokens[0].value.replace('"', '')
            if is_identifier:
                return {
                    "type": "Identifier",
                    "name": f"{tokens[0].value}"
                }
            template = {
                "type": "Literal",
                "value": value,
                "raw": tokens[0].value
            }
        else:
            template = self.expression(tokens)

        return template