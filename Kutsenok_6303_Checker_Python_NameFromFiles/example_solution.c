#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

#define INITIAL_LIST_SIZE 100

typedef struct NameDirs {
    char* name;
    char** dirs;
    int size;
} NameDirs;

typedef struct FileDirsList {
    NameDirs** list;
    int size;
} FileDirsList;

int list_dir(FileDirsList* file_dirs_list, const char* path);

void dir_add(FileDirsList* dir_list, const char* dir, int index);

void file_dir_add(FileDirsList* dir_list, const char* name, const char* dir);

int find_file_dir(FileDirsList* dir_list, const char* name);

int dir_exists(NameDirs* dir_list, const char* dir);

char* get_directory(NameDirs* dir);

FileDirsList* init_list();


void find_files(FileDirsList* pList, char* input);

int main() {
    FileDirsList* file_dirs_list = init_list();
    list_dir(file_dirs_list, "./files");
//    for(int i = 0; i < file_dirs_list->size; i++) {
//        for(int j = 0; j < file_dirs_list->list[i]->size; ++j) {
//            printf("%s %s\n", file_dirs_list->list[i]->name, file_dirs_list->list[i]->dirs[j]);
//        }
//    }
    char* input = (char*) malloc(INITIAL_LIST_SIZE* sizeof(char));
    scanf("%s", input);
    find_files(file_dirs_list, input);
    return 0;
}

void find_files(FileDirsList* file_dirs_list, char* input) {
    size_t len = strlen(input);
    int result = 0;
    char* temp = (char*) malloc(2 * sizeof(char));
    temp[1] = '\0';
    for(int i = 0; i < len; ++i) {
        temp[0] = input[i];
        result = find_file_dir(file_dirs_list, temp);
        if(result >= 0) {
            printf("%s/%s.txt\n", get_directory(file_dirs_list->list[result]), file_dirs_list->list[result]->name);
        }
    }
    return;
}


char* get_directory(NameDirs* dir) {
    return ++(dir->dirs[--dir->size]);
}

int list_dir(FileDirsList* file_dirs_list, const char* path) {
    struct dirent* entry;
    DIR* dir = opendir(path);
    int result = 0;
    char* file_name = NULL;
    while((entry = readdir(dir))) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            if(!(entry->d_type & DT_DIR)) {
                //printf("%s/%s\n", path, entry->d_name);
                file_name = strtok(entry->d_name, ".");
                result = find_file_dir(file_dirs_list, file_name);
                if(result < 0) {
                    file_dir_add(file_dirs_list, file_name, path);
                } else {
                    dir_add(file_dirs_list, path, result);
                }
            }
            if(entry->d_type & DT_DIR) {
                char dir_path[PATH_MAX];
                sprintf(dir_path, "%s/%s", path, entry->d_name);
                list_dir(file_dirs_list, dir_path);
            }
        }

    }
    closedir(dir);
    return 0;
}

void dir_add(FileDirsList* dir_list, const char* dir, int index) {
    dir_list->list[index]->dirs[dir_list->list[index]->size] = (char*) malloc(INITIAL_LIST_SIZE * sizeof(char));
    strcpy(dir_list->list[index]->dirs[dir_list->list[index]->size++], dir);
}

void file_dir_add(FileDirsList* dir_list, const char* name, const char* dir) {
    dir_list->list[dir_list->size] = (NameDirs*) malloc(sizeof(NameDirs));
    dir_list->list[dir_list->size]->dirs = (char**) malloc(INITIAL_LIST_SIZE * sizeof(char*));
    dir_list->list[dir_list->size]->size = 1;
    dir_list->list[dir_list->size]->name = (char*) malloc(INITIAL_LIST_SIZE * sizeof(char));
    strcpy(dir_list->list[dir_list->size]->name, name);
    dir_list->list[dir_list->size]->dirs[0] = (char*) malloc(INITIAL_LIST_SIZE * sizeof(char));
    strcpy(dir_list->list[dir_list->size]->dirs[0], dir);
    dir_list->size++;
}

int find_file_dir(FileDirsList* dir_list, const char* name) {
    for(int i = 0; i < dir_list->size; i++) {
        if(strcmp(dir_list->list[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int dir_exists(NameDirs* dir_list, const char* dir) {
    for(int i = 0; i < dir_list->size; i++) {
        if(strcmp(dir_list->dirs[i], dir) == 0) {
            return i;
        }
    }
    return -1;
}

FileDirsList* init_list() {
    FileDirsList* dir_list = malloc(sizeof(FileDirsList));
    dir_list->list = (NameDirs**) malloc(INITIAL_LIST_SIZE * sizeof(NameDirs*));
    dir_list->size = 0;
    return dir_list;
}

