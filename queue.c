#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void waitForEnter() {
    printf("\nPress Enter to continue...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    getchar(); 
}

void enqueue(struct Node** front, struct Node** rear, int data, int showMessage);

void saveToFile(struct Node* front) {
    FILE *file = fopen("queue_data.txt", "w");
    if (file == NULL) return;
    
    struct Node* temp = front;
    while (temp != NULL) {
        fprintf(file, "%d\n", temp->data);
        temp = temp->next;
    }
    fclose(file);
}

void loadFromFile(struct Node** front, struct Node** rear) {
    FILE *file = fopen("queue_data.txt", "r");
    if (file == NULL) return; 
    
    int data;
    while (fscanf(file, "%d", &data) == 1) {
        enqueue(front, rear, data, 0); 
    }
    fclose(file);
}

void createQueue(struct Node** front, struct Node** rear) {
    if (*front != NULL) {
        printf("\n[Notice] A queue already exists! Please use Option 3 to Enqueue.\n");
        return;
    }

    char resp;
    int data;

    do {
        printf("Enter data to enqueue: ");
        
        if (scanf("%d", &data) != 1) {
            printf("  -> [Error] Invalid input! Letters/characters are not allowed.\n");
            printf("\nReturning to main menu...\n");
            return; 
        }
        
        enqueue(front, rear, data, 0); 

        while (1) {
            printf("Add another node [Y/N]? ");
            scanf(" %c", &resp); 
            
            if (resp == 'Y' || resp == 'y' || resp == 'N' || resp == 'n') {
                break; 
            } else {
                printf("  -> [Error] Invalid input. Please enter 'Y' for Yes or 'N' for No.\n");
            }
        }
        
    } while (resp == 'Y' || resp == 'y');
    
    printf("\n[Success] Initial Queue created!\n");
}

void display(struct Node** front, struct Node** rear) {
    struct Node* TravNode = *front;

    if (TravNode == NULL) {
        printf("\nError: The Queue is Empty!\n");
    } else {
        struct Node* tempFront = NULL;
        struct Node* tempRear = NULL;

        printf("\n--- Current Queue Line ---\n");
        printf("FRONT -> ");

        do {
            printf("[%d] -> ", TravNode->data);

            *front = TravNode->next;

            if (*front == NULL) {
                *rear = NULL;
            }

            TravNode->next = NULL;

            if (tempFront == NULL) {
                tempFront = tempRear = TravNode;
            } else {
                tempRear->next = TravNode;
                tempRear = TravNode;
            }

            TravNode = *front;

        } while (*front != NULL);

        printf("REAR\n");
        printf("--------------------------\n");

        *front = tempFront;
        *rear = tempRear;
    }
}

void enqueue(struct Node** front, struct Node** rear, int data, int showMessage) {
    struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
    if (NewNode == NULL) {
        printf("\nError: Memory allocation failed!\n");
        return;
    }
    
    NewNode->data = data;
    NewNode->next = NULL;

    if (*rear == NULL) {
        *front = *rear = NewNode;
    } else {
        (*rear)->next = NewNode;
        *rear = NewNode;
    }
    
    if (showMessage) {
        printf("\n[Success] %d fell in line at the rear!\n", data);
    }
}

void dequeue(struct Node** front, struct Node** rear) {
    struct Node* DelNode = *front;

    if (DelNode == NULL) {
        printf("\nError: The Queue is Empty!\n");
        return;
    } 
    
    int servedData = DelNode->data; 
    
    *front = (*front)->next;
    DelNode->next = NULL;
    free(DelNode);
    
    if (*front == NULL) {
        *rear = NULL;
    }

    printf("\n[Success] %d was served and left the queue!\n", servedData);
}

void peekFront(struct Node* front) {
    if (front == NULL) {
        printf("\nError: The Queue is Empty!\n");
    } else {
        printf("\n[Peek] The next in line at the front is: %d\n", front->data);
    }
}

int main() {
    struct Node* front = NULL; 
    struct Node* rear = NULL;  
    int choice, data;

    loadFromFile(&front, &rear);

    while (1) {
        system("cls"); 
        
        printf("===== Queue Implementation by Group 1 =====\n");
        printf("1. Create queue\n");
        printf("2. Display queue\n");
        printf("3. Enqueue (insert item)\n");
        printf("4. Dequeue (remove item)\n");
        printf("5. Peek (view front item)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input! Letters/symbols are not allowed.\n");
            waitForEnter(); 
            continue; 
        }

        switch (choice) {
            case 1:
                createQueue(&front, &rear);
                waitForEnter();
                break;
            case 2:
                display(&front, &rear);
                waitForEnter();
                break;
            case 3:
                printf("Enter data to enqueue: ");
                if (scanf("%d", &data) != 1) {
                    printf("\n[Error] Invalid input! Please enter a number.\n");
                } else {
                    enqueue(&front, &rear, data, 1); 
                }
                waitForEnter();
                break;
            case 4:
                dequeue(&front, &rear);
                waitForEnter();
                break;
            case 5:
                peekFront(front);
                waitForEnter();
                break;
            case 6:
                printf("\nSaving data and exiting program...\n");
                saveToFile(front);
                
                while (front != NULL) {
                    struct Node* temp = front;
                    front = front->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("\n[Error] Invalid selection.\n");
                waitForEnter();
        }
    }
    return 0;
}
