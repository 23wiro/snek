#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int boardSizeX = 8;
const int boardSizeY = 8;

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

int movement(struct Node **head,char* direction) {
    int x, y;
    int newHeadX = 0;
    int newHeadY = 0;
    int currentIndex = 0;
    struct Node* current = *head;

    getDataOfIndex(*head, 0, &x, &y);
    if (strcmp(direction, "up") == 0) {
        newHeadX = x-1;
        newHeadY = y;
    } else if (strcmp(direction, "down") == 0) {
        newHeadX = x+1;
        newHeadY = y;
    } else if (strcmp(direction, "left") == 0) {
        newHeadX = x;
        newHeadY = y-1;
    } else if (strcmp(direction, "right") == 0) {
        newHeadX = x;
        newHeadY = y+1;
    } else {
        printf("Invalid direction\n");
    }
    while (current != NULL && currentIndex < snakeLength) {
        getDataOfIndex(*head, currentIndex, &x, &y);
        if (newHeadX == x && newHeadY == y) {
            printf("Game over\n");
            return 0;
        }
        currentIndex++;
    }
    if (newHeadX < 0 || newHeadX >= boardSizeX || newHeadY < 0 || newHeadY >= boardSizeY) {
        printf("Game over\n");
        return 0;
    }

    *head = addNode(*head, newHeadX, newHeadY);
    return 1;
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
    *appleX = rand() % boardSizeX;
    *appleY = rand() % boardSizeY;
    while (current != NULL && currentIndex < snakeLength) {
        getDataOfIndex(head, currentIndex, &x, &y);
        while (*appleX == x && *appleY == y) {
            *appleX = rand() % boardSizeX;
            *appleY = rand() % boardSizeY;
        }
        currentIndex++;
    }
}

int main() {
    char board[boardSizeX][boardSizeY];
    int maxSnakeLength = boardSizeX * boardSizeY;
    struct Node* head = NULL;
    int snakeX, snakeY;
    int appleX, appleY;
    char direction[10];

    head = addNode(head, 0, 2);
    head = addNode(head, 0, 1);
    head = addNode(head, 0, 0);

    appleMaker(head, &appleX, &appleY);

    while (snakeLength < maxSnakeLength) {

        for (i = 0; i < boardSizeY; i++) {
            for (j = 0; j < boardSizeX; j++) {
                board[i][j] = 0; 
            }
        }

        board[appleX][appleY] = 1;

        struct Node* current = head;
        for (k = 0; k < snakeLength; k++){
            snakeX = current->snakeX;
            snakeY = current->snakeY;
            board[snakeX][snakeY] = 2; 
            current = current->next;
        }

        for (i = 0; i < boardSizeX; i++) {
            for (j = 0; j < boardSizeY; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }

        printf("Enter the direction: ");
        scanf("%s", direction);
        if (movement(&head, direction) == 0) {
            break;
        }

        if (appleEaten(head, appleX, appleY)) {
            snakeLength++;
            appleMaker(head, &appleX, &appleY);
            board[appleX][appleY] = 1;
        }
    }

    if (snakeLength == maxSnakeLength){
        printf("congratulations you won\n");
    }
    return 0;
}