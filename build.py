import os
import sys
import platform
import subprocess

dirs = {
    "src": "src",
    "obj": "obj",
    "bin": "bin"
}

cflags = f'-std=c++20 -I{dirs["src"]}'
errflags = "-Wall -Wunused-variable -Wextra -Wno-enum-compare -g -ggdb -fdiagnostics-color=always -static-libstdc++"

clear = False
run_automatically = True

out = "koral"

compiled = []

def get_flags():
    global errflags

    flags = [ "clear", "release" ]

    if len(sys.argv) != 3 or not sys.argv[2] in flags:
        print("INFO: No flags specified, using default flags")
        errflags += " -O0"
        return

    global clear
    clear = True

    print("INFO: Rebuiding all files...")

    if sys.argv[2] == "release":
        print("INFO: Building in release mode")
        errflags += " -O3"
    else:
        errflags += " -O0"

def get_properties():
    global out
    
    if platform.system() == "Windows":
        out += ".exe"
    else:
        out += ".out"

    global koral_file

    if len(sys.argv) >= 2:
        koral_file = sys.argv[1]
    else:
        print('ERROR: No file specified.\nExiting...')
        exit(1)
    
def create_folders():
    for key in dirs:
        if not os.path.exists(dirs[key]):
            os.makedirs(dirs[key])

def run_command(*args):
    try:
        return subprocess.check_output(" ".join(args), shell=True).strip().decode("utf-8")
    except:
        print(f'ERROR: Error when compiling.\nExiting...')
        exit(1)

def compile(dir, file):
    if (file.endswith(".cpp")):
        compiledFile = os.path.join(dir, file)
        objectFile = os.path.join(dirs["obj"], file.split('.')[0]) + '.o'

        compiled.append(objectFile)

        if not clear and os.path.exists(objectFile) and os.path.getmtime(compiledFile) < os.path.getmtime(objectFile):
            return
        
        run_command(f'g++ {cflags} {errflags} -c {compiledFile} -o {objectFile}')

        post_index = len(dirs["src"]) + 1
        print(f'BUILD: Compiled {compiledFile[post_index:]}')

def main():
    get_flags()
    create_folders()

    get_properties()

    for [dir, _, files] in os.walk(dirs["src"]):
        for file in files:
            compile(dir, file)

    run_command(f'g++ {cflags} {errflags} -o {dirs["bin"]}/{out} {" ".join(compiled)}')

    print("INFO: Build successful")

    if run_automatically:
        print("\nINFO: Running program...")

        if platform.system() == "Windows":
            os.system(f"bin\\{out} {koral_file}")
        else:
            os.system(f"./bin/{out} {koral_file}")

if __name__ == "__main__":
    main()