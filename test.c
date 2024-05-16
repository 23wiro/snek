#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int board[8][8];
int i, j, k;


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

int getDataOfIndex(struct Node* head,int index, int* x, int* y) {
    if (head == NULL) {
        printf("List is empty\n");
        exit(1);
    }

    struct Node* current = head;
    int currentIndex = 0;
    while (current!= NULL && currentIndex < index) {
    {
        current = current->next;
        currentIndex++;
    }

    if (current!= NULL) {
        printf("Index out of bounds\n");
        exit(1);
    }

    *x = current->snakeX;
    *y = current->snakeY;
    return 1;
}

int main()  {
    struct Node* head = NULL;
    addNode(0, 0);
    addNode(0, 1);
    addNode(0, 2);

    srand(time(NULL));
    int appleX = rand() %8;
    int appleY = rand() %8;
    board[appleX][appleY] = 1;

    int snakeX, snakeY;

    for (i=0; i <= 7; i++) {
        for (j=0; j<=7; j++){
            for (k=0; getDataOfIndex(head, k, &snakeX, &snakeY) != NULL; k++){
                board[snakeX][snakeY] = 2;
            }
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}