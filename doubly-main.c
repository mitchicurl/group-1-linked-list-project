#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// For help functions lang
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

// For file retrieving
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

// PERSON 2: Creation and Traversal
void createList(struct Node** head) {
    // Code dito...
}

void traverse(struct Node* head) {
    // Code dito...
}

// PERSON 3: Adding of New Node at Start and End
void insertAtStart(struct Node** head, int data) {
    // Code dito...
}

void insertAtEnd(struct Node** head, int data) {
    // Code dito...
}

// PERSON 4: Adding New Node Before and After a Node
void insertBefore(struct Node** head, int target, int data) {
    if (*head == NULL) {
        printf("\nError: The list is empty. Target %d not found.\n", target);
        return;
    }

    if ((*head)->data == target) {
        insertAtStart(head, data);
        return;
    }

    struct Node* TravNode = *head;

    while (TravNode != NULL) {
        TravNode = TravNode->next;
        if (TravNode->data == target) break;
    }

    if (TravNode == NULL) {
        printf("\nError: Target value %d not found in the list.\n", target);
        return;
    }
    
    struct Node* NewNode = createNode(data);
    NewNode->prev = TravNode->prev;
    NewNode->next = TravNode;
    TravNode->prev->next = NewNode;
    TravNode->prev = NewNode;
}

void insertAfter(struct Node* head, int target, int data) {
    if (head == NULL) {
        printf("\nError: The list is empty. Target %d not found.\n", target);
        return;
    }

    struct Node* TravNode = head;

    while (TravNode != NULL && TravNode->data != target) {
        TravNode = TravNode->next;
    }

    if (TravNode == NULL) {
        printf("\nError: Target value %d not found in the list.\n", target);
        return;
    }
    
    struct Node* NewNode = createNode(data);
    NewNode->next = TravNode->next;
    NewNode->prev = TravNode;
    if (TravNode->next != NULL) TravNode->next->prev = NewNode;
    TravNode->next = NewNode;
}

// PERSON 5: Deletion of Node at Start and by Value
void deleteAtStart(struct Node** head) {
    // Code dito...
}

void deleteByValue(struct Node** head, int target) {
    // Code dito...
}

// PERSON 6: Deletion Before and After a Node
void deleteBefore(struct Node** head, int target) {
    // Code dito...
}

void deleteAfter(struct Node* head, int target) {
    // Code dito...
}

// List / Choices
int main() {
    struct Node* head = NULL;
    int choice, data, target;

    loadFromFile(&head);

    while (1) {
        system("cls"); 
        
        printf("===== Doubly Linked List =====\n");
        printf("1. Create node(s)\n");
        printf("2. Display all nodes\n");
        printf("3. Adding of new node at the start\n");
        printf("4. Adding of new node at the end\n");
        printf("5. Adding new node before a node\n");
        printf("6. Adding new node after a node\n");
        printf("7. Deletion of node at the start\n");
        printf("8. Deletion of node by value\n");
        printf("9. Deletion of node before a node\n");
        printf("10. Deletion of node after a node\n");
        printf("11. Exit\n");
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
                printf("\n[Success] Start node deleted (if it existed)!\n");
                waitForEnter();
                break;
            case 8:
                printf("Enter the value of the node to delete: ");
                scanf("%d", &target);
                deleteByValue(&head, target);
                waitForEnter();
                break;
            case 9:
                printf("Enter the target node value to delete BEFORE it: ");
                scanf("%d", &target);
                deleteBefore(&head, target);
                waitForEnter();
                break;
            case 10:
                printf("Enter the target node value to delete AFTER it: ");
                scanf("%d", &target);
                deleteAfter(head, target);
                waitForEnter();
                break;
            case 11:
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
