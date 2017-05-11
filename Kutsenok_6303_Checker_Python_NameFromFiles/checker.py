import os
import sys
import random
import string
import shutil

RANDOM_FILES_COUNT_MAX = 20
RANDOM_WORD_SIZE_MIN = 5
RANDOM_WORD_SIZE_MAX = 10
FOLDER_COUNT_MIN = 3
FOLDER_COUNT_MAX = 6
FOLDER_DEPTH_MIN = 1
FOLDER_DEPTH_MAX = 5

TEST_SHOULD_PASS_CHANCE = 0.00

root_directory = "./files"


def random_word():
    return ''.join(random.choice(string.ascii_uppercase + string.ascii_lowercase) for i in
                   range(random.randrange(RANDOM_WORD_SIZE_MIN, RANDOM_WORD_SIZE_MAX)))


def clean_folders():
    # for root, dirs, files in os.walk("./files"):
    #     for file in files:
    #         os.unlink(root + "/" + file)
    for root, dirs, files in os.walk(root_directory):
        for dir in dirs:
            shutil.rmtree(root + "/" + dir)


def generate_sub_folders(directory_root, sub_directory_depth, directory_list):
    if (sub_directory_depth == 0):
        return
    folder_num = random.randrange(FOLDER_COUNT_MIN, FOLDER_COUNT_MAX)
    for i in range(folder_num):
        directory_root = directory_root + "/" + random_word()
        os.makedirs(directory_root)
        directory_list.append(directory_root)
        generate_sub_folders(directory_root, sub_directory_depth - 1, directory_list)


def generate_folders():
    folder_num = random.randrange(FOLDER_COUNT_MIN, FOLDER_COUNT_MAX)
    directory_list = []
    for i in range(folder_num):
        sub_directory_depth = random.randrange(FOLDER_DEPTH_MIN, FOLDER_DEPTH_MAX)
        # directory_root = root_directory + "/" + random_word()
        # os.makedirs(directory_root)
        # directory_list.append(directory_root)
        generate_sub_folders(root_directory, sub_directory_depth - 1, directory_list)
    return directory_list


def generate_file(name, directory_list):
    open(random.choice(directory_list) + "/" + name + ".txt", 'a').close()


def generate():
    clean_folders()  # generate random folders
    directory_list = generate_folders()
    # print(directory_list)

    rand_word = list(random_word())  # split main string by letters to be used as file names

    if (random.random() > TEST_SHOULD_PASS_CHANCE):  # if test should be valid
        for char in rand_word:
            generate_file(char, directory_list)

    for i in range(random.randrange(1, RANDOM_FILES_COUNT_MAX)):
        generate_file(random.choice(string.ascii_uppercase + string.ascii_lowercase), directory_list)

    return ''.join(rand_word)

def solve(string):
    file = sys.argv[0]
    # pathname = os.path.dirname(file)

    file_name_array = {}

    # string = list(input())
    #print(string)
    for root, dirs, files in os.walk(root_directory):
        for file in files:
            # print(root, file)
            name, extension = file.split('.')
            if (extension == "txt"):
                try:
                    file_name_array[name]
                except KeyError:
                    file_name_array[name] = []
                file_name_array[name].append(root[1:])  # delete "." from root
    #print(file_name_array)

    output = ""
    for char in string:
        try:
            file_name_array[char]
        except KeyError:
            sys.exit("error")

        try:
            dir = file_name_array[char].pop()
            # print(dir + "/" + char + ".txt")
            output += dir + "/" + char + ".txt"
            output += '\n'
        except:
            sys.exit("error")
    #print(output)
    return output


def check(reply, clue):  # clue - input word
    reply = reply.split(" ")
    clue = list(clue)
    file_name_array = {}
    for root, dirs, files in os.walk(root_directory):
        for file in files:
            name, extension = file.split('.')
            if (extension == "txt"):
                try:
                    file_name_array[name]
                except KeyError:
                    file_name_array[name] = []
                file_name_array[name].append(root[1:])  # delete "." from root
    #print(reply)
    for i in range(len(clue)):
        file = (reply[i].split("/"))[-1]
        file_directory = reply[i].split(".")[0]
        file_directory = file_directory[:-2]
        file_name, extension = file.split(".")
        if (extension == 'txt' and file_name == clue[i]):

            if (file_directory in file_name_array[clue[i]]):
                continue
            else:
                return 0
        else:
            return 2
    return 1


#print(check(solve(generate()), input()))