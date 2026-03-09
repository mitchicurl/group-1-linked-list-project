#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// For help function lang
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void waitForEnter() {
    printf("\nPress Enter to continue...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    getchar(); 
}

// For file input/output function
void insertAtEnd(struct Node** head, int data);
void saveToFile(struct Node* head) {
    FILE *file = fopen("doubly_list_data.txt", "w");
    if (file == NULL) return;
    struct Node* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d\n", temp->data);
        temp = temp->next;
    }
    fclose(file);
}

void loadFromFile(struct Node** head) {
    FILE *file = fopen("doubly_list_data.txt", "r");
    if (file == NULL) return; 
    int data;
    while (fscanf(file, "%d", &data) == 1) {
        insertAtEnd(head, data);
    }
    fclose(file);
}

// FILL IN YOUR ASSIGNED FUNCTIONS BELOW!
// Do not change the function names or parameters.
// Remember to link BOTH the 'next' and 'prev' pointers!

// --- PERSON 2: Creation and Traversal ---
void createList(struct Node** head) {
// Code dito
}

void traverse(struct Node* head) {
// Code dito
}

// --- PERSON 3: Adding of New Node at Start and End ---
void insertAtStart(struct Node** head, int data) {
// Code dito
}

void insertAtEnd(struct Node** head, int data) {
// Code dito
}

// --- PERSON 4: Adding New Node Before and After a Node ---
void insertBefore(struct Node** head, int target, int data) {
// Code dito
}

void insertAfter(struct Node* head, int target, int data) {
// Code dito
}

// --- PERSON 5: Deletion of Node at Start and by Value ---
void deleteAtStart(struct Node **head) {
    struct Node *temp;

    if (*head == NULL) {
        printf("\nError: List is already empty.\n");
        return;
    }

    temp = *head;
    *head = temp->next;

    if (*head != NULL) {
        (*head)->prev = NULL;
    }

    free(temp);
    printf("\n[Success] Start node deleted!\n");
}

void deleteAtEnd(struct Node** head) {
    if (*head == NULL) {
        printf("\nError: List is already empty.\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->prev->next = NULL; 

    free(temp);
}

void deleteByValue(struct Node **head, int target) {
    struct Node *current;

    if (*head == NULL) {
        printf("\nError: List is empty.\n");
        return;
    }

    current = *head;

    while (current != NULL && current->data != target) {
        current = current->next;
    }

    if (current == NULL) {
        printf("\nError: Value %d not found.\n", target);
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
    printf("\n[Success] Node with value %d deleted!\n", target);
}

// --- PERSON 6: Deletion Before and After a Node ---
void deleteBefore(struct Node** head, int target) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("\nError: List too short to delete 'before'.\n");
        return;
    }

    if ((*head)->data == target) {
        printf("\nError: No node exists before the head (%d).\n", target);
        return;
    }

    struct Node* Current = *head;

    while (Current != NULL && Current->data != target) {
        Current = Current->next;
    }

    if (Current != NULL) {
        struct Node* DelNode = Current->prev;

        if (DelNode == *head) {
            *head = Current;
            Current->prev = NULL;
        } 
        else {
            DelNode->prev->next = Current;
            Current->prev = DelNode->prev;
        }
        
        free(DelNode);
        printf("\n[Success] Node before %d deleted!\n", target);
    } else {
        printf("\nError: Value %d not found.\n", target);
    }
}

void deleteAfter(struct Node* head, int target) {
    if (head == NULL) {
        printf("\nError: List is empty.\n");
        return;
    }

    struct Node* Current = head;
    
    while (Current != NULL && Current->data != target) {
        Current = Current->next;
    }

    if (Current != NULL) {
        if (Current->next == NULL) {
            printf("\nError: No node exists after %d.\n", target);
        } else {
            struct Node* DelNode = Current->next;
          
            Current->next = DelNode->next;

            if (DelNode->next != NULL) {
                DelNode->next->prev = Current;
            }
            
            free(DelNode);
            printf("\n[Success] Node after %d deleted!\n", target);
        }
    } else {
        printf("\nError: Value %d not found.\n", target);
    }
}

// List / Choices
int main() {
    struct Node* head = NULL;
    int choice, data, target;

    loadFromFile(&head);

    while (1) {
        system("cls"); 
        
        printf("===== Doubly Linked List by Group 1 =====\n");
        printf("1. Create node(s)\n");
        printf("2. Display all nodes\n");
        printf("3. Adding of new node at the start\n");
        printf("4. Adding of new node at the end\n");
        printf("5. Adding new node before a node\n");
        printf("6. Adding new node after a node\n");
        printf("7. Deletion of node at the start\n");
        printf("8. Deletion of node at the end\n");
        printf("9. Deletion of node by value\n");
        printf("10. Deletion of node before a node\n");
        printf("11. Deletion of node after a node\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createList(&head);
                printf("\n[Success] Nodes created!\n");
                waitForEnter();
                break;
            case 2:
                traverse(head);
                waitForEnter();
                break;
            case 3:
                printf("Enter data to insert at start: ");
                scanf("%d", &data);
                insertAtStart(&head, data);
                printf("\n[Success] Node inserted at start!\n");
                waitForEnter();
                break;
            case 4:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                printf("\n[Success] Node inserted at end!\n");
                waitForEnter();
                break;
            case 5:
                printf("Enter target node value: ");
                scanf("%d", &target);
                printf("Enter data to insert before %d: ", target);
                scanf("%d", &data);
                insertBefore(&head, target, data);
                waitForEnter();
                break;
            case 6:
                printf("Enter target node value: ");
                scanf("%d", &target);
                printf("Enter data to insert after %d: ", target);
                scanf("%d", &data);
                insertAfter(head, target, data);
                waitForEnter();
                break;
            case 7:
                deleteAtStart(&head);
                printf("\n[Success] Start node deleted!\n");
                waitForEnter();
                break;
            case 8:
                deleteAtEnd(&head);
                printf("\n[Success] End node deleted!\n");
                waitForEnter();
                break;
            case 9:
                printf("Enter the value of the node to delete: ");
                scanf("%d", &target);
                deleteByValue(&head, target);
                waitForEnter();
                break;
            case 10:
                printf("Enter the target node value to delete BEFORE it: ");
                scanf("%d", &target);
                deleteBefore(&head, target);
                waitForEnter();
                break;
            case 11:
                printf("Enter the target node value to delete AFTER it: ");
                scanf("%d", &target);
                deleteAfter(head, target);
                waitForEnter();
                break;
            case 12:
                printf("\nSaving data and exiting program...\n");
                saveToFile(head);

                while (head != NULL) {
                    struct Node* temp = head;
                    head = head->next;
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
