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
    int n, data;

    printf("Enter number of nodes to create: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of nodes.\n");
        return;
    }

    struct Node* temp = NULL;
    struct Node* newNode = NULL;

    for (int i = 1; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        scanf("%d", &data);

        newNode = createNode(data);

        if (*head == NULL) {        // first node
            *head = newNode;
            temp = newNode;
        } 
        else {
            temp->next = newNode;   // forward link
            newNode->prev = temp;   // backward link
            temp = newNode;
        }
    }
}

void traverse(struct Node* head) {

    if (head == NULL) {
        printf("\nList is empty.\n");
        return;
    }

    struct Node* temp = head;

    printf("\nDoubly Linked List:\n");

    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
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
    // Code dito...
}

void insertAfter(struct Node* head, int target, int data) {
    // Code dito...
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
