#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){
    srand(time(NULL));  
    int isCorrect = rand() % 2;
    int numberOfNumbers = atoi(argv[1]);
    int numberOfCommands = atoi(argv[2]);
    for (int j = 0; j < numberOfCommands; j++){
        for (int  i = 0; i < numberOfNumbers; i++)
            printf("%d", 1 + (rand() % 10) * (rand() % 10) % 4);
    if (isCorrect != 0)
        printf("4\n");
    else
        printf("%d\n", 1 + rand() % 3);
    }
    return 0;
}