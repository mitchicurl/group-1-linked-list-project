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
    int i; 
    
    while (fscanf(file, "%d", &data) == 1) {
        tempArr[count] = data;
        count++;
    }
    
    for (i = count - 1; i >= 0; i--) {
        push(top, tempArr[i], 0); 
    }
    fclose(file);
}

void createStack(struct Node** top) {
    if (*top != NULL) {
        printf("\n[Notice] A stack already exists! Please use Option 3 to Push more items.\n");
        return;
    }

    char resp;
    int data;

    do {
        printf("Enter data to push: ");
        
        if (scanf("%d", &data) != 1) {
            printf("  -> [Error] Invalid input! Letters/characters are not allowed.\n");
            printf("\nReturning to main menu...\n");
            return; 
        }
        
        push(top, data, 0); 

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
    
    printf("\n[Success] Initial Stack created!\n");
}

void display(struct Node* top) {
    if (top == NULL) {
        printf("\nError: The stack is empty!\n");
        return;
    }

    struct Node* temp = top;
    
    printf("\n--- Current Stack ---\n");
    
    while (temp != NULL) {
        printf("[%d]\n", temp->data);
        temp = temp->next;
    }
    printf("-------------------\n");
}

void push(struct Node** top, int data, int showMessage) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nError: Memory allocation failed!\n");
        return;
    }
    
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
    
    if (showMessage) {
        printf("\n[Success] %d was pushed to the top of the stack!\n", data);
    }
}

void pop(struct Node** top) {
    if (*top == NULL) {
        printf("\nError: Stack Underflow! The stack is already empty.\n");
        return;
    }
    
    struct Node* temp = *top;
    int poppedData = temp->data;
    
    *top = (*top)->next;
    free(temp);
    
    printf("\n[Success] %d was popped from the stack!\n", poppedData);
}

void peek(struct Node* top) {
    if (top == NULL) {
        printf("\nError: The stack is empty!\n");
    } else {
        printf("\n[Peek] The item at the TOP of the stack is: %d\n", top->data);
    }
}

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
        
        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input! Letters/symbols are not allowed.\n");
            waitForEnter(); 
            continue; 
        }

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
                if (scanf("%d", &data) != 1) {
                    printf("\n[Error] Invalid input! Please enter a number.\n");
                } else {
                    push(&top, data, 1); 
                }
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
