class Error:
    def __init__(self, error_message, line):
        self.message = ''
        self.error_message = error_message
        self.line = line

class Variable:
    def __init__(self, name, type, value=''):
        self.name = name
        self.type = type
        self.value = value
    
    def assign(self, value):
        self.value = value

class Interpreter:
    def __init__(self, ast):
        self.ast = ast
        self.variables = []
        self.errors = []
        self.functions = []
        self.functions.append('say')

    def get_variable_type(self, value):
        try:
            float(value)
        except ValueError:
            return 'String'
        return 'Numeric'

    def add_variable(self, name, type, value=''):
        self.variables.append(Variable(name, type, value))

    def get_variable(self, name):
        for variable in self.variables:
            if variable.name == name:
                return variable
        return None

    def solve_expression(self, expression):
        if expression['type'] == 'Literal':
            return expression['value']
        elif expression['type'] == 'BinaryExpression':
            left = expression['left']
            right = expression['right']
            operator = expression['operator']

            if left['type'] == 'Literal':
                left = left['value']
            elif left['type'] == 'Identifier':
                variable = self.get_variable(left['name'])
                if variable:
                    if self.get_variable_type(variable.value) == 'Numeric':
                        left = float(variable.value)
                    else:
                        left = variable.value
                else:
                    self.errors.append(Error(f'Variable "{left["name"]}" not found'))
                    return
            else:
                left = self.solve_expression(left)

            if right['type'] == 'Literal':
                right = right['value']
            elif right['type'] == 'Identifier':
                variable = self.get_variable(right['name'])
                if variable:
                    if self.get_variable_type(variable.value) == 'Numeric':
                        right = float(variable.value)
                    else:
                        right = variable.value
                else:
                    self.errors.append(Error(f'Variable "{right["name"]}" not found'))
                    return
            else:
                right = self.solve_expression(right)

            if self.get_variable_type(left) == 'Numeric' and self.get_variable_type(right) == 'Numeric':
                if operator == '+':
                    result = left + right
                elif operator == '-':
                    result = left - right
                elif operator == '*':
                    result = left * right
                elif operator == '/':
                    result = left / right
                elif operator == '%':
                    result = left % right
                
                if result * 10 % 10 == 0:
                    return int(result)
            elif self.get_variable_type(left) == 'String' and self.get_variable_type(right) == 'String':
                if operator == '+':
                    result = left + right
                else:
                    self.errors.append(Error(f'Operator "{operator}" not supported for strings', expression['line']))
                    return

            return result

    def execute(self):
        for node in self.ast['body']:
            if node['type'] == 'VariableDeclaration':
                for variable in node['declarations']:
                    if variable['init']['type'] == 'Literal':
                        value = variable['init']['value']
                        type = self.get_variable_type(value)
                    elif variable['init']['type'] == 'Identifier':
                        variable_value = self.get_variable(variable['init']['name'])
                        if variable_value:
                            value = variable_value.value
                            type = variable_value.type
                        else:
                            self.errors.append(Error(f'Variable "{variable["init"]["name"]}" not found', node['line']))
                            return
                    else:
                        value = self.solve_expression(variable['init'])
                        type = self.get_variable_type(value)
                    self.add_variable(variable['id']['name'], type, value)
            elif node['type'] == 'ExpressionStatement':
                if node['expression']['type'] == 'AssignmentExpression':
                    variable = self.get_variable(node['expression']['left']['name'])
                    if variable:
                        if node['expression']['right']['type'] == 'Literal':
                            variable.assign(node['expression']['right']['raw'])
                        elif node['expression']['right']['type'] == 'Identifier':
                            variable_value = self.get_variable(node['expression']['right']['name'])
                            if variable_value:
                                variable.assign(variable_value.value)
                            else:
                                self.errors.append(Error(f'Variable "{node["expression"]["right"]["name"]}" not found', node['line']))
                                return
                        else:
                            variable.assign(self.solve_expression(node['expression']['right']))
                    else:
                        self.errors.append(Error(f'Variable "{node["expression"]["left"]["name"]}" not found', node['line']))
                        return
                elif node['expression']['type'] == 'CallExpression':
                    name = node['expression']['callee']['name']
                    args = node['expression']['arguments']
                    arguments = []

                    for arg in args:
                        if arg['type'] == 'Literal':
                            arguments.append(arg['value'])
                        elif arg['type'] == 'Identifier':
                            identifier = self.get_variable(arg['name'])
                            if identifier:
                                arguments.append(identifier.value)
                            else:
                                self.errors.append(Error(f'Variable "{arg["name"]}" not found', node['line']))
                                return
                        else:
                            arguments.append(self.solve_expression(arg))

                    if name in self.functions:
                        if name == 'say':
                            self.say(arguments)

    # built-in functions
    def say(self, args):
        for index, arg in enumerate(args):
            arg_end = ' '
            if index == len(args) - 1:
                arg_end = ''
            new_lines = []
            arg = str(arg)
            for i in range(len(arg)):
                if arg[i:i+2] == '\\n':
                    new_lines.append(i)
                    arg = arg[:i] + arg[i+2:]
            for i in range(len(arg)):
                if i in new_lines:
                    print()
                print(arg[i], end='')
            print(end=arg_end)
        print()