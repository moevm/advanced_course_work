import os
import sys
import random
import string
import shutil

root_directory = "./files_minotaur"


def search_file(file_full, file_name_array, result_array):
    with open(file_full, 'r', encoding='utf-8') as file:
        file = file.readlines()
        for line in file:
            result_array.append(file_full)
            if line == 'Minotaur':
                return True
            if line == 'Deadlock':
                result_array.pop()
                return False
            line = line.replace('\n', '').split(' ')[1]
            file_name, extension = os.path.splitext(line)
            print(file_name, extension[1:])
            if search_file(file_name_array[file_name] + '/' + line, file_name_array, result_array) == True:
                return True
            result_array.pop()



def solve():
    file_name_array = {}
    for root, dirs, files in os.walk(root_directory):
        for file in files:
            # print(root, file)
            name, extension = file.split('.')
            if (extension == "txt"):
                file_name_array[name] = root  # delete "." from root
    print(file_name_array)
    result_array = []
    search_file(file_name_array['file'] + '/file.txt', file_name_array, result_array)
    print(result_array)

solve()
