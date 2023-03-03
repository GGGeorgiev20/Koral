import os
import sys
import platform
import subprocess

srcdir = "src"
objdir = "obj"
libdir = "lib"

cflags = f'-I{srcdir} -L{libdir}'
errflags = "-Wall -Wunused-variable -Wextra -Wno-enum-compare -g -ggdb -fdiagnostics-color=always -static-libstdc++"

run_automatically = True

out = "koral"
if platform.system() == "Windows":
    out += ".exe"
else:
    out += ".out"

koral_file = ""
if sys.argv[1]:
    koral_file = sys.argv[1]
else:
    print('ERROR: No file specified.\nExiting...')
    exit(1)

compiled = []

def run_command(*args):
    try:
        return subprocess.check_output(" ".join(args), shell=True).strip().decode("utf-8")
    except:
        print(f'ERROR: Error when compiling.\nExiting...')
        exit(1)

def compile(file):
    if (file.endswith(".cpp")):
        compiledFile = os.path.join(dir, file)
        objectFile = os.path.join(objdir, file.split('.')[0]) + '.o'

        run_command(f'g++ {cflags} {errflags} -c {compiledFile} -o {objectFile}')
        print(f'Compiled {compiledFile[4:]}')
        compiled.append(objectFile)

for [dir, subDirs, files] in os.walk(srcdir):
    for file in files:
        compile(file)

run_command(f'g++ {cflags} {errflags} -o bin/{out} {" ".join(compiled)}')

print("INFO: Build successful")

if run_automatically:
    print("\nINFO: Running program...")

    if platform.system() == "Windows":
        os.system(f"bin\\{out} {koral_file}")
    else:
        os.system(f"./bin/{out} {koral_file}")