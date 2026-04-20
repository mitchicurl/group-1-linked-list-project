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

void push(struct Node** top, int data); 

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
        push(top, tempArr[i]);
    }
    fclose(file);
}

// TECH LEAD TASKS: FILL IN THE FUNCTIONS BELOW

// 1. Add a new node to the TOP of the stack
void push(struct Node** top, int data) {
    // Your code here...
}

// 2. Remove and delete the node at the TOP of the stack
void pop(struct Node** top) {
    // Your code here...
}

// 3. View the data at the TOP of the stack without removing it
void peek(struct Node* top) {
    // Your code here...
}

// 4. Display all items in the stack (from top to bottom)
void display(struct Node* top) {
    // Your code here...
}

// MAIN FUNCTION (Menu System)
int main() {
    struct Node* top = NULL; // In a stack, 'head' is traditionally called 'top'
    int choice, data;

    loadFromFile(&top);

    while (1) {
        system("cls"); 
        
        printf("===== Stack Implementation =====\n");
        printf("1. Push (Insert Item)\n");
        printf("2. Pop (Remove Top Item)\n");
        printf("3. Peek (View Top Item)\n");
        printf("4. Display Stack\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push onto the stack: ");
                scanf("%d", &data);
                push(&top, data);
                // Note: Add your printf("\n[Success]...") inside your push function!
                waitForEnter();
                break;
            case 2:
                pop(&top);
                waitForEnter();
                break;
            case 3:
                peek(top);
                waitForEnter();
                break;
            case 4:
                display(top);
                waitForEnter();
                break;
            case 5:
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
