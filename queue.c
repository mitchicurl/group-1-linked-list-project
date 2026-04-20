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

void enqueue(struct Node** front, struct Node** rear, int data);

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
        enqueue(front, rear, data);
    }
    fclose(file);
}

// TECH LEAD TASKS: FILL IN THE FUNCTIONS BELOW

// 1. Create the initial Queue (using the Do-While loop)
void createQueue(struct Node** front, struct Node** rear) {
// Your code here...
}

// 2. Display all items in the queue (from front to rear)
void display(struct Node* front) {
// Your code here...
}

// 3. Add a new node to the REAR (back) of the queue
void enqueue(struct Node** front, struct Node** rear, int data) {
// Your code here...
}

// 4. Remove and delete the node at the FRONT of the queue
void dequeue(struct Node** front, struct Node** rear) {
// Your code here...
}

// 5. View the data at the FRONT of the queue without removing it
void peekFront(struct Node* front) {
// Your code here...
}

// MAIN FUNCTION (Menu System)
int main() {
    struct Node* front = NULL; 
    struct Node* rear = NULL;  
    int choice, data;

    // Load saved data automatically
    loadFromFile(&front, &rear);

    while (1) {
        system("cls"); 
        
        printf("===== Queue Implementation by Group 1 =====\n");
        printf("1. Create node/s\n");
        printf("2. Display queue\n");
        printf("3. Enqueue node\n");
        printf("4. Dequeue node\n");
        printf("5. Peek Front\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createQueue(&front, &rear);
                waitForEnter();
                break;
            case 2:
                display(front);
                waitForEnter();
                break;
            case 3:
                printf("Enter data to enqueue: ");
                scanf("%d", &data);
                enqueue(&front, &rear, data);
                // Note: Make sure your success printf is inside your enqueue function!
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
