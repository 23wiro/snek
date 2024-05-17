#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[8][8];
int i, j, k;

struct Node {
    int snakeX;
    int snakeY;
    struct Node* next;
};

struct Node* addNode(struct Node* head, int x, int y) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory not allocated\n");
        return head;
    }
    newNode->snakeX = x;
    newNode->snakeY = y;
    newNode->next = head;
    return newNode;
}

int getDataOfIndex(struct Node *head, int index, int* x, int* y) {
    if (head == NULL) {
        printf("List is empty\n");
        return 0;
    }

    struct Node* current = head;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (current == NULL) {
        printf("Index out of bounds\n");
        return 0;
    }

    *x = current->snakeX;
    *y = current->snakeY;
    return 1;
}

int setDataOfIndex(struct Node *head, int index, int x, int y) {
    struct Node* current = head;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }
    if (current == NULL) {
        printf("Index out of bounds\n");
        return 0;
    }
    current->snakeX = x;
    current->snakeY = y;
}

int chuckThatShitOutOfHere(int *getDataOfIndex,  int *setDataOfIndex, Node *head) {
    struct Node* current = head;
    int l = 0;
    while (current != NULL){
        current = current->next;
        l++;

    }
    getDataOfIndex(l, &snakeX, &snakeY);
    setDataOfIndex();
}

int main() {
    struct Node* head = NULL;
    head = addNode(head, 0, 2);
    head = addNode(head, 0, 1);
    head = addNode(head, 0, 0);

    srand(time(NULL));
    int appleX = rand() % 8;
    int appleY = rand() % 8;

    int snakeX, snakeY;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            board[i][j] = 0; 
        }
    }
    board[appleX][appleY] = 1;

    struct Node* current = head;
    while (current != NULL) {
        snakeX = current->snakeX;
        snakeY = current->snakeY;
        board[snakeX][snakeY] = 2;  // Place the snake on the board
        current = current->next;
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%d ", board[i][j]);  // Use %d instead of %s
        }
        printf("\n");
    }

    // Free the allocated memory
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}