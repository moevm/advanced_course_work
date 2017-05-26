#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void genNumber();

int main(int argc, char** argv){
    srand(time(NULL));  
    int numberOfNumbers = atoi(argv[1]);
    int numberOfCommands = atoi(argv[2]);
    for (int j = 0; j < numberOfCommands; j++){
        for (int  i = 0; i < numberOfNumbers; i++)
            printf("%d", 1 + (rand() % 10) * (rand() % 10) % 4);
    printf("\n");
    }
    return 0;
}