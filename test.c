#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char board[8][8];
int i, j, k, m;
char direction;
int snakeLength = 3;

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

int movement(struct Node *head,char* direction) {
    if (strcmp(direction, "up") == 0) {
        int x, y;
        getDataOfIndex(head, 0, &x, &y);
        addNode(head, x, y + 1);
    } else if (strcmp(direction, "down") == 0) {
        int x, y;
        getDataOfIndex(head, 0, &x, &y);
        addNode(head, x, y - 1);
    } else if (strcmp(direction, "left") == 0) {
        int x, y;
        getDataOfIndex(head, 0, &x, &y);
        addNode(head, x - 1, y);
    } else if (strcmp(direction, "right") == 0) {
        int x, y;
        getDataOfIndex(head, 0, &x, &y);
        addNode(head, x + 1, y);
    }
}

int appleEaten(struct Node *head, int appleX, int appleY) {
    int x, y;
    getDataOfIndex(head, 0, &x, &y);
    if (x == appleX && y == appleY) {
        return 1;
    }
    return 0;
}

int appleMaker(struct Node *head, int* appleX, int* appleY) {
    int x, y;
    struct Node* current = head;
    int currentIndex = 0;
    srand(time(NULL));
    *appleX = rand() % 8;
    *appleY = rand() % 8;
    while (current != NULL && currentIndex < snakeLength) {
        while (appleX == x && appleY == y) {
            appleX = rand() % 8;
            appleY = rand() % 8;
        }
        currentIndex++;
    }
}

int main() {
    struct Node* head = NULL;
    head = addNode(head, 0, 2);
    head = addNode(head, 0, 1);
    head = addNode(head, 0, 0);

    int snakeX, snakeY;

    while (snakeLength < 64) {

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            board[i][j] = 0; 
        }
    }

int appleX, appleY;

applemaker(&appleX, &appleY);

    board[appleX][appleY] = 1;

    struct Node* current = head;
    for (k = 0; k < snakeLength; k++){
        snakeX = current->snakeX;
        snakeY = current->snakeY;
        board[snakeX][snakeY] = 2;  // Place the snake on the board
        current = current->next;
    }

    if (appleEaten(head, appleX, appleY)) {
        snakeLength++;
        applemaker(&appleX, &appleY);
        board[appleX][appleY] = 1;
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

    }

    return 0;
}