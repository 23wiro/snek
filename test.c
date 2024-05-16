#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int board[8][8];
int i;
int j;

struct Node {
    int snakeX;
    int snakeY;
    struct Node* next;
};

struct Node* addNode(int x, int y){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory not allocated");
        return 0;
    }
    newNode->snakeX = x;
    newNode->snakeY = y;
    newNode->next = NULL;
    return newNode;
}

int main()  {
    srand(time(NULL));
    int appleX = rand() %7;
    int appleY = rand() %7;
    board[appleX][appleY] = 1;


    for (i=0; i <= 7; i++) {
        for (j=0; j<=7; j++){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}