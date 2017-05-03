#!/usr/bin/python3

import os
import random
import string
import fnmatch
import shutil

#Управление максимальной длиной пути
MAX_PATH_LEN = 200
#Управление размером названия файла
MIN_FILENAME = 1
MAX_FILENAME = 20
#Управление количеством директорий на текущем уровне
MIN_DIRS = 1
MAX_DIRS = 3
#Управление глубиной
MIN_DIR_DEPTH = 1
MAX_DIR_DEPTH = 3
#Управление количеством файлов на текущем уровне
MIN_FILES = 1
MAX_FILES = 3
#Управление количеством чисел в одном файле
MIN_NUMBERS_IN_FILE = 1
MAX_NUMBERS_IN_FILE = 4
#Управление диапазоном чисел
MIN_NUMBER = -2147483648
MAX_NUMBER = 2147483647
#Управление названиями директорий
DIR_ADD = "add"
DIR_MUL = "mul"
#Управление вероятностью созданий директорий
MIN_PROB = 0
MAX_PROB = 10

#Функция генерирует название файла
def generateFileName():
    result = ""
    for x in range(random.randint(MIN_FILENAME, MAX_FILENAME)):
        result += random.choice(string.ascii_uppercase + string.ascii_lowercase)
    result += ".txt"
    return result

#Функция генерирует название директории (add или mult)
def generateDirName():
     result = ""
     if random.randint(0, 1) == 0:
         result = DIR_ADD
     else:
         result = DIR_MUL
     return result

#Функция генерирует случайное число для файла
def generateNumber():
    result = int(random.uniform(MIN_NUMBER, MAX_NUMBER))
    return result

#Функция генерирует содержимое файла
def generateFileContent():
    result = ""
    for x in range (random.randint(MIN_NUMBERS_IN_FILE, MAX_NUMBERS_IN_FILE) - 1):
        result += str(generateNumber()) + " "
    result += str(generateNumber())
    return result

#Функция генерирует файлы в директории path
def generateFiles(path):
    for x in range(random.randint(MIN_FILES, MAX_FILES)):
        file_path = path + "/" + generateFileName()
        file_to_generate = open(file_path, 'w')
        file_to_generate.write(generateFileContent())
        file_to_generate.close()

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
            dir_to_generate = str(path) + "/" + generateDirName()
            if (not os.path.exists(dir_to_generate)) and (len(dir_to_generate) < MAX_PATH_LEN):
                os.makedirs(dir_to_generate)
                generateFiles(dir_to_generate)

def generate():
    #current_dir = str(os.getcwd())
    root_dir = os.getcwd() + "/Cases" + "/" + generateDirName()
    os.makedirs(root_dir)
    generateDirsAndFilesOnCurrentLevel(root_dir)
    for x in range(random.randint(MIN_DIR_DEPTH, MAX_DIR_DEPTH)):
        for root, dirs, files in os.walk(root_dir, topdown=False):
            for name in dirs:
                generateDirsAndFilesOnCurrentLevel(os.path.join(root, name))
    return root_dir

def solve(root_dir):
    pattern = '*.txt'
    files_tree = []
    for root, dirs, files in os.walk(root_dir):
        # for filename in fnmatch.filter(files, pattern):
        #     files_tree.append(os.path.join(root, filename))
        for name in dirs:
            #print(os.path.join(root, name))
            print (name)
    #print (files_tree)
# def check(reply, clue):
#     return str(reply) == str(clue)

#shutil.rmtree(os.getcwd() + "/Cases")
dataset  = generate()
solve(dataset)
