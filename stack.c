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

void push(struct Node** top, int data, int showMessage); 

void saveToFile(struct Node* top) {
    FILE *file = fopen("stack_data.txt", "w");
    if (file == NULL) return;
    
    struct Node* temp = top;
    while (temp != NULL) {
        fprintf(file, "%d\n", temp->data);
        temp = temp->next;
    }
    fclose(file);
}

void loadFromFile(struct Node** top) {
    FILE *file = fopen("stack_data.txt", "r");
    if (file == NULL) return; 
    
    int data;
    int tempArr[1000]; 
    int count = 0;
    
    while (fscanf(file, "%d", &data) == 1) {
        tempArr[count] = data;
        count++;
    }
    
    for (int i = count - 1; i >= 0; i--) {
        push(top, tempArr[i], 0); 
    }
    fclose(file);
}

// TECH LEAD TASKS: FILL IN THE FUNCTIONS BELOW

// 1. Create the initial Stack (using a Do-While loop)
void createStack(struct Node** top) {
// Your code here...
}

// 2. Display all items in the stack (from top to bottom)
void display(struct Node* top) {
// Your code here...
}

// 3. Add a new node to the TOP of the stack
void push(struct Node** top, int data, int showMessage) {
// Your code here...
}

// 4. Remove and delete the node at the TOP of the stack
void pop(struct Node** top) {
// Your code here...
}

// 5. View the data at the TOP of the stack without removing it
void peek(struct Node* top) {
// Your code here...
}

// MAIN FUNCTION (Menu System)
int main() {
    struct Node* top = NULL; 
    int choice, data;

    loadFromFile(&top);

    while (1) {
        system("cls"); 
        
        printf("===== Stack Implementation by Group 1 =====\n");
        printf("1. Create stack\n");
        printf("2. Display stack\n");
        printf("3. Push (insert item)\n");
        printf("4. Pop (remove item)\n");
        printf("5. Peek (view top item)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createStack(&top);
                waitForEnter();
                break;
            case 2:
                display(top);
                waitForEnter();
                break;
            case 3:
                printf("Enter data to push onto the stack: ");
                scanf("%d", &data);
                push(&top, data, 1); 
                waitForEnter();
                break;
            case 4:
                pop(&top);
                waitForEnter();
                break;
            case 5:
                peek(top);
                waitForEnter();
                break;
            case 6:
                printf("\nSaving data and exiting program...\n");
                saveToFile(top);
                
                while (top != NULL) {
                    struct Node* temp = top;
                    top = top->next;
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
