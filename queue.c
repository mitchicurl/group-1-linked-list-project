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

// 1. Add a new node to the REAR (back) of the queue
void enqueue(struct Node** front, struct Node** rear, int data) {
    // Your code here...
    // Hint: If the queue is empty, the new node becomes BOTH the front and the rear
}

// 2. Remove and delete the node at the FRONT of the queue
void dequeue(struct Node** front, struct Node** rear) {
    // Your code here...
    // Hint: Don't forget to check if the queue becomes empty after you delete the last node. 
    // If it does, you must set the 'rear' to NULL as well
}

// 3. View the data at the FRONT of the queue without removing it
void peekFront(struct Node* front) {
    // Your code here...
}

// 4. Display all items in the queue (from front to rear)
void display(struct Node* front) {
    // Your code here...
}

// MAIN FUNCTION (Menu System)
int main() {
    // A standard Queue tracks BOTH the front and the back of the line
    struct Node* front = NULL; 
    struct Node* rear = NULL;  
    int choice, data;

    loadFromFile(&front, &rear);

    while (1) {
        system("cls"); 
        
        printf("===== Queue Implementation =====\n");
        printf("1. Enqueue (Fall in line / Insert at Rear)\n");
        printf("2. Dequeue (Serve / Remove from Front)\n");
        printf("3. Peek Front (View next in line)\n");
        printf("4. Display Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to enqueue: ");
                scanf("%d", &data);
                enqueue(&front, &rear, data);
                // Note: Add your printf("\n[Success]...") inside your enqueue function!
                waitForEnter();
                break;
            case 2:
                dequeue(&front, &rear);
                waitForEnter();
                break;
            case 3:
                peekFront(front);
                waitForEnter();
                break;
            case 4:
                display(front);
                waitForEnter();
                break;
            case 5:
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
