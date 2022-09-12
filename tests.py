import os

python_file = 'main.py'
koral_file = 'main.kor'

ast_file = os.path.join('data', 'ast.json')
tests_folder = 'tests'

tests = []
file_saves = [[]]

class Test:
    def __init__(self, *parameters):
        self.parameters = parameters
        self.index = len(tests) + 1
        tests.append(self)

    def check_success(self):
        with open(ast_file, 'r') as ast:
            with open(os.path.join(tests_folder, f"test_{self.index}.json"), 'r') as test:
                expected = test.readlines()
                for index, line in enumerate(ast.readlines()):
                    if line != expected[index]:
                        return False
        return True

    def run(self):
        if not self.parameters:
            raise Exception

        write_file(koral_file, self.parameters)
        os.system(f"python {python_file}")

        is_successfull = self.check_success()

        print(f"Test {self.index} ", end='')
        if is_successfull:
            print("passed ✓")
        else:
            print("failed ✗")

def save_file(file):
    with open(file, 'r') as f:
        index = len(file_saves) - 1
        file_saves.append([])
        for line in f.readlines():
            file_saves[index].append(line)

def write_file(file, *parameters):
    with open(file, 'w') as f:
        for index, line in enumerate(parameters):
            if index != 0:
                f.write('\n')
            for word in line:
                f.write(word)

def run_tests():
    for test in tests:
        test.run()

def main():
    save_file(koral_file)
    save_file(ast_file)

    test_one = Test('5 + 5')
    test_two = Test('5 + 5 * 5')
    test_three = Test('5 * 5 + 5')
    test_four = Test('5 + 5 * 5 - 2')
    test_five = Test('10 - 6 * 2 / 6 + 1 - 4 / 3')
    
    run_tests()

    write_file(koral_file, file_saves[0])
    write_file(ast_file, file_saves[1])

main()