#!/usr/bin/python3

import os
import random
import string
import fnmatch
import shutil

#Управление количеством тестов
TESTS = 20
#Управление максимальной длиной пути
MAX_PATH_LEN = 100
#Управление размером названия файла
MIN_FILENAME = 1
MAX_FILENAME = 4
#Управление количеством директорий на текущем уровне
MIN_DIRS = 1
MAX_DIRS = 3
#Управление глубиной
MIN_DIR_DEPTH = 1
MAX_DIR_DEPTH = 3
#Управление количеством файлов на текущем уровне
MIN_FILES = 1
MAX_FILES = 3
#Управление диной текста
MIN_TEXT_LEN = 1
MAX_TEXT_LEN = 3
#Управление диапазоном чисел
MIN_NUMBER = -100
MAX_NUMBER = 100
#Управление длиной названий директорий
MIN_DIR_NAME = 1
MAX_DIR_NAME = 4

#Функция генерирует название файла
def generateFileName():
    result = ""
    for x in range(random.randint(MIN_FILENAME, MAX_FILENAME)):
        result += random.choice(string.ascii_uppercase + string.ascii_lowercase)
    result += ".txt"
    return result

#Функция генерирует символьную строку
def generateString(min, max):
     result = ""
     for x in range (random.randint(min, max)):
         result += random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits)
     return result

#Функция генерирует случайное число для файла
def generateNumber():
        result = int(random.randint(MIN_NUMBER, MAX_NUMBER))
        return result
#Функция генерирует содержимое файла
def generateFileContent():
    result = str(generateNumber()) + " " + generateString(MIN_TEXT_LEN, MAX_TEXT_LEN)
    return result

#Функция генерирует файлы в директории path
def generateFiles(path):
    for x in range(random.randint(MIN_FILES, MAX_FILES)):
        file_path = path + "/" + generateFileName()
        file_to_generate = open(file_path, 'w')
        file_to_generate.write(generateFileContent())
        file_to_generate.close()

#Функция генерирует набор директорий в текущей директории
def generateDirsAndFilesOnCurrentLevel(path):
    for i in range(random.randint(MIN_DIRS, MAX_DIRS)):
        if random.random():
            dir_to_generate = str(path) + "/" + generateString(MIN_DIR_NAME, MAX_DIR_NAME)
            if (not os.path.exists(dir_to_generate)) and (len(dir_to_generate) < MAX_PATH_LEN):
                os.makedirs(dir_to_generate)
                generateFiles(dir_to_generate)

def generate():
    #current_dir = str(os.getcwd())
    root_dir = os.getcwd() + "/Cases"
    os.makedirs(root_dir)
    generateFiles(root_dir)
    generateDirsAndFilesOnCurrentLevel(root_dir)

    for x in range(random.randint(MIN_DIR_DEPTH, MAX_DIR_DEPTH)):
        for root, dirs, files in os.walk(root_dir, topdown=False):
            for name in dirs:
                generateDirsAndFilesOnCurrentLevel(os.path.join(root, name))
    return root_dir

def solve(root_dir):
    pattern = '*.txt'
    list_of_files_content = [] #Лист для хранения данных из файлов
    pair = []
    for root, dirs, files in os.walk(root_dir):
        for filename in fnmatch.filter(files, pattern):
            file_to_read = open(os.path.join(root, filename), 'r')
            number, string = file_to_read.read().split(" ")
            pair.append(int(number))
            pair.append(string)
            list_of_files_content.append(pair)
            file_to_read.close()
            pair = []
    #Сортировка по числу
    list_of_files_content.sort(key=lambda item: item[0])
    solution = ""
    list_length = len(list_of_files_content)
    for x in range(list_length):
         solution += str(list_of_files_content[x][0]) + " " + list_of_files_content[x][1]
         if x < list_length - 1:
             solution += "\n"
    return solution

def clean():
    shutil.rmtree(os.getcwd()+"/Cases/")
    os.remove('./solution')
    os.remove('./result_file')

def check():
    for x in range(TESTS):
        generate()
        clue = solve('./Cases')
        os.system('gcc solution.c -o solution')
        os.system('./solution > result_file')
        result_file = open('./result_file', 'r')
        reply = str(result_file.read())
        if (reply != clue):
            print("Test {} - correct".format(x))
        else:
            print('Failed test {}'.format(x))
            break
    clean()
check()
