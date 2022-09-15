import os
import subprocess
import sys

python_file = 'main.py'
koral_file = 'main.kor'

ast_file = os.path.join('data', 'ast.json')
tests_folder = 'tests'

tests = []
file_saves = [[]]

class Test:
    def __init__(self, expected):
        self.expected = expected
        self.index = len(tests) + 1
        tests.append(self)

    def check_success(self):
        received = subprocess.run('python main.py main.kor', shell=True, stdout=subprocess.DEVNULL)
        expected = self.expected
        return received == expected

    def get_parameters(self):
        result = []
        with open(os.path.join(tests_folder, f"test_{self.index}.kor"), 'r') as f:
            for line in f.readlines():
                result.append(line)
        return result

    def run(self):
        if not self.expected:
            raise Exception

        write_file(koral_file, self.get_parameters())

        is_successful = self.check_success()

        print(f"Test {self.index} ", end='')
        if is_successful:
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

    test_one = Test('10')
    
    run_tests()

    write_file(koral_file, file_saves[0])
    write_file(ast_file, file_saves[1])

main()