import os
from random import randint
from signal import SIGSEGV

def get_test_files():

    os.system("find tests -name \"*.s\" > files")
    f = open("files", "r")
    if f == None:
        exit(84)
    files = f.readlines()
    for i in range(len(files)):
        files[i] = files[i][:-1]
    f.close()
    os.system("rm -f files")
    return files

def print_red():
    print("\033[31m", end="")
def print_green():
    print("\033[32m", end="")
def print_white():
    print("\033[37m", end="")

def get_my_rval(test_file):
    my_rval = os.system("cd my; ./asm " + test_file + " > /dev/null 2> /dev/null")
    my_rval = os.WEXITSTATUS(my_rval)
    has_crashed = 1 if (os.WIFSIGNALED(my_rval) and os.WTERMSIG(my_rval) == SIGSEGV) else 0
    if (my_rval == 0):
        os.system("mv my/*.cor ./my_cor")
    return my_rval, has_crashed

def get_ref_rval(test_file):
    my_rval = os.system("cd ref; ./asm " + test_file + " > /dev/null 2> /dev/null")
    my_rval = os.WEXITSTATUS(my_rval)
    if (my_rval == 0):
        os.system("mv ref/*.cor ./ref_cor")
    return my_rval

def create_failed_dir():
    rnd = randint(0, 10000)
    dir = "./failed/test_%d" %rnd
    while os.system("ls " + dir + " > /dev/null 2> /dev/null") == 0:
        rnd = randint(0, 10000)
        dir = "./failed/test_%d" %rnd
    os.system("mkdir " + dir)
    os.system("cp my_cor ref_cor " + dir)
    return rnd

def get_max_file_length(files):
    max = 0
    for file in files:
        file_to_print = file.split("/")[-1]
        if (len(file_to_print) > max):
            max = len(file_to_print)
    return max

files = get_test_files()
nb_test = len(files)

failed = 0
succeeded = 0
crashed = 0

os.system("rm -rf failed/*")

for file in files:
    test_file = "../" + file
    file_to_print = test_file.split("/")[-1]
    max = get_max_file_length(files)

    my_rval, has_crashed = get_my_rval(test_file)
    ref_rval = get_ref_rval(test_file)
    crashed += has_crashed
    if (my_rval != ref_rval):
        failed += 1
        print_red()
        print("%s:%s Test failed. Expected exit status %d, got %d." %(file_to_print, (" " * (max - len(file_to_print))), ref_rval, my_rval))
    elif (my_rval == 0 and os.WEXITSTATUS(os.system("diff my_cor ref_cor > /dev/null 2> /dev/null")) != 0):
        failed += 1
        print_red()
        dir_nb = create_failed_dir()
        print("%s:%s Test failed. File differs. See results in ./failed/test_%d/." %(file_to_print, (" " * (max - len(file_to_print))), dir_nb))
    else:
        succeeded += 1
        print_green()
        print("%s:%s Test passed." %(file_to_print, (" " * (max - len(file_to_print)))))

    print_white()
    os.system("rm -f my_cor ref_cor")

formatted = "Passed: \033[32m%d\033[37m, Failed: \033[31m%d\033[37m, Crashed: \033[31m%d\033[37m." %(succeeded, failed, crashed)

print("=" * len(formatted))
print(formatted)
print("=" * len(formatted))
