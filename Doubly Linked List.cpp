#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

// CREATE NODE
Node* createNode(int value) {
    Node* newNode = new Node;
    if (newNode == NULL) {
        cout << "Memory allocation failed!\n";
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// FUNCTION DECLARATION
void insertAtEnd(Node** head, int data);

// FILE HANDLING
void saveToFile(Node* head) {
    ofstream file("doubly_list_data.txt");
    if (!file) return;

    Node* temp = head;
    while (temp != NULL) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

void loadFromFile(Node** head) {
    ifstream file("doubly_list_data.txt");
    if (!file) return;

    int data;
    while (file >> data) {
        insertAtEnd(head, data);
    }
    file.close();
}

void createList(Node** head) {
    if (*head != NULL) {
        cout << "\n[Notice] A list already exists! Please use options 3-6 to add more nodes.\n";
        return;
    }

    int n, data;

    cout << "Enter number of nodes to create: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of nodes.\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        cout << "Enter data for node " << i << ": ";
        cin >> data;
        insertAtEnd(head, data);
    }

    cout << "\n[Success] Nodes created!\n";
}

void traverse(Node* head) {
    cout << "\n--- Current Doubly Linked List ---\n";

    if (head == NULL) {
        cout << "The list is currently empty.\n";
    } else {
        Node* temp = head;

        while (temp != NULL) {
            cout << "[" << temp->data << "]";
            if (temp->next != NULL) cout << " <-> ";
            temp = temp->next;
        }
        cout << endl;
    }
    cout << "----------------------------------\n";
}

void insertAtStart(Node** head, int data) {
    Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}

void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void insertBefore(Node** head, int target, int data) {
    if (*head == NULL) {
        cout << "\nError: The list is empty. Target " << target << " not found.\n";
        return;
    }

    if ((*head)->data == target) {
        insertAtStart(head, data);
        cout << "\n[Success] Node inserted before " << target << "!\n";
        return;
    }

    Node* TravNode = *head;

    while (TravNode != NULL && TravNode->data != target) {
        TravNode = TravNode->next;
    }

    if (TravNode == NULL) {
        cout << "\nError: Target value " << target << " not found in the list.\n";
        return;
    }

    Node* NewNode = createNode(data);
    NewNode->prev = TravNode->prev;
    NewNode->next = TravNode;
    TravNode->prev->next = NewNode;
    TravNode->prev = NewNode;

    cout << "\n[Success] Node inserted before " << target << "!\n";
}

void insertAfter(Node* head, int target, int data) {
    if (head == NULL) {
        cout << "\nError: The list is empty. Target " << target << " not found.\n";
        return;
    }

    Node* TravNode = head;

    while (TravNode != NULL && TravNode->data != target) {
        TravNode = TravNode->next;
    }

    if (TravNode == NULL) {
        cout << "\nError: Target value " << target << " not found in the list.\n";
        return;
    }

    Node* NewNode = createNode(data);
    NewNode->next = TravNode->next;
    NewNode->prev = TravNode;

    if (TravNode->next != NULL) {
        TravNode->next->prev = NewNode;
    }
    TravNode->next = NewNode;

    cout << "\n[Success] Node inserted after " << target << "!\n";
}

void deleteAtStart(Node **head) {
    if (*head == NULL) {
        cout << "\nError: List is already empty.\n";
        return;
    }

    Node *temp = *head;
    *head = temp->next;

    if (*head != NULL) {
        (*head)->prev = NULL;
    }

    delete temp;
}

void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        cout << "\nError: List is already empty.\n";
        return;
    }

    if ((*head)->next == NULL) {
        delete *head;
        *head = NULL;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->prev->next = NULL;
    delete temp;
}

void deleteByValue(Node **head, int target) {
    if (*head == NULL) {
        cout << "\nError: List is empty.\n";
        return;
    }

    Node *current = *head;

    while (current != NULL && current->data != target) {
        current = current->next;
    }

    if (current == NULL) {
        cout << "\nError: Value " << target << " not found.\n";
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

    delete current;
    cout << "\n[Success] Node with value " << target << " deleted!\n";
}

void deleteBefore(Node** head, int target) {
    if (*head == NULL || (*head)->next == NULL) {
        cout << "\nError: List too short to delete 'before'.\n";
        return;
    }

    if ((*head)->data == target) {
        cout << "\nError: No node exists before the head (" << target << ").\n";
        return;
    }

    Node* Current = *head;

    while (Current != NULL && Current->data != target) {
        Current = Current->next;
    }

    if (Current != NULL) {
        Node* DelNode = Current->prev;

        if (DelNode == *head) {
            *head = Current;
            Current->prev = NULL;
        } else {
            DelNode->prev->next = Current;
            Current->prev = DelNode->prev;
        }

        delete DelNode;
        cout << "\n[Success] Node before " << target << " deleted!\n";
    } else {
        cout << "\nError: Value " << target << " not found.\n";
    }
}

void deleteAfter(Node* head, int target) {
    if (head == NULL) {
        cout << "\nError: List is empty.\n";
        return;
    }

    Node* Current = head;

    while (Current != NULL && Current->data != target) {
        Current = Current->next;
    }

    if (Current != NULL) {
        if (Current->next == NULL) {
            cout << "\nError: No node exists after " << target << ".\n";
        } else {
            Node* DelNode = Current->next;

            Current->next = DelNode->next;

            if (DelNode->next != NULL) {
                DelNode->next->prev = Current;
            }

            delete DelNode;
            cout << "\n[Success] Node after " << target << " deleted!\n";
        }
    } else {
        cout << "\nError: Value " << target << " not found.\n";
    }
}

// MAIN PROGRAAAAM
int main() {
    Node* head = NULL;
    int choice, data, target;

    loadFromFile(&head);

    while (1) {
        system("cls");

        cout << "===== Doubly Linked List by Group 1 =====\n";
        cout << "1. Create node(s)\n";
        cout << "2. Display all nodes\n";
        cout << "3. Adding of new node at the start\n";
        cout << "4. Adding of new node at the end\n";
        cout << "5. Adding new node before a node\n";
        cout << "6. Adding new node after a node\n";
        cout << "7. Deletion of node at the start\n";
        cout << "8. Deletion of node at the end\n";
        cout << "9. Deletion of node by value\n";
        cout << "10. Deletion of node before a node\n";
        cout << "11. Deletion of node after a node\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createList(&head);
                waitForEnter();
                break;
            case 2:
                traverse(head);
                waitForEnter();
                break;
            case 3:
                cout << "Enter data to insert at start: ";
                cin >> data;
                insertAtStart(&head, data);
                cout << "\n[Success] Node inserted at start!\n";
                waitForEnter();
                break;
            case 4:
                cout << "Enter data to insert at end: ";
                cin >> data;
                insertAtEnd(&head, data);
                cout << "\n[Success] Node inserted at end!\n";
                waitForEnter();
                break;
            case 5:
                cout << "Enter target node value: ";
                cin >> target;
                cout << "Enter data to insert before " << target << ": ";
                cin >> data;
                insertBefore(&head, target, data);
                waitForEnter();
                break;
            case 6:
                cout << "Enter target node value: ";
                cin >> target;
                cout << "Enter data to insert after " << target << ": ";
                cin >> data;
                insertAfter(head, target, data);
                waitForEnter();
                break;
            case 7:
                deleteAtStart(&head);
                cout << "\n[Success] Start node deleted!\n";
                waitForEnter();
                break;
            case 8:
                deleteAtEnd(&head);
                cout << "\n[Success] End node deleted!\n";
                waitForEnter();
                break;
            case 9:
                cout << "Enter the value of the node to delete: ";
                cin >> target;
                deleteByValue(&head, target);
                waitForEnter();
                break;
            case 10:
                cout << "Enter the target node value to delete BEFORE it: ";
                cin >> target;
                deleteBefore(&head, target);
                waitForEnter();
                break;
            case 11:
                cout << "Enter the target node value to delete AFTER it: ";
                cin >> target;
                deleteAfter(head, target);
                waitForEnter();
                break;
            case 12:
                cout << "\nSaving data and exiting program...\n";
                saveToFile(head);

                while (head != NULL) {
                    Node* temp = head;
                    head = head->next;
                    delete temp;
                }
                exit(0);
            default:
                cout << "\n[Error] Invalid selection.\n";
                waitForEnter();
        }
    }
    return 0;
}
