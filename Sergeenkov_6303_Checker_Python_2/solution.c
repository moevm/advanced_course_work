#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define ROOT_PATH "./Cases/"
#define FILE_EXTENSION ".txt"

#define MAX_PATH_LEN 3000
#define ARRAY_LEN 1000
#define MAX_TEXT_LENGTH 100
#define MAX_DIR_NAME 255

typedef struct FileContent
{
  int number;
  char text[MAX_TEXT_LENGTH];
} FileContent;

FileContent content[ARRAY_LEN];
int arr_index = 0;

//Рекурсивная функция для обхода поддиректорий
void dirTraveler(char *dirname, int deep);
//функция для сортировки массива структур
void sort();
//функция для печати массива структур
void print();

int main(int argc, char const *argv[])
{

  char path[MAX_PATH_LEN];
  strcat(path, ROOT_PATH);
  dirTraveler(path, 100);
  sort();
  print();
  return 0;
}

void dirTraveler(char *dirname, int deep)
{
  if (deep==0)
      return;
  DIR *dir;
  struct dirent *entry;
  if ((dir = opendir(dirname)) == NULL)
  {
      exit(1);
  }
  while ((entry = readdir(dir)) != NULL)
  {
      if (strcmp(entry->d_name,".")&&strcmp(entry->d_name,".."))
      {
          char s[MAX_DIR_NAME];
          s[0]='\0';
          strcat(s,dirname);
          strcat(s,entry->d_name);
          if (opendir(s)==NULL)
          {
              FILE * file = fopen(s, "r");
              int number;
              fscanf(file, "%d %s", &content[arr_index].number, content[arr_index].text);
              ++arr_index;
              fclose(file);
          }
          else
          {
              strcat(s,"/");
              dirTraveler(s,deep-1);
          }
      }
  }
  if (closedir(dir) != 0)
  {
      exit(1);
  }
  return;
}

void sort()
{
  for (int i = 0; i < arr_index - 1; i++)
  {
    for (int j = 0; j < (arr_index - i - 1); j++)
    {
      if (content[j].number > content[j+1].number)
      {
        FileContent buf = content[j];
        content[j] = content[j+1];
        content[j+1] = buf;
      }
    }
  }
}

void print()
{
  for (int i = 0; i < arr_index; i++)
  {
    printf("%d %s\n", content[i].number, content[i].text);
  }
}
