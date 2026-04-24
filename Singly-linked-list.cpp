#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

// For help functions 
Node* createNode(int value) {
    Node* newNode = new Node;
    if (newNode == NULL) {
        cout << "Memory allocation failed!" << endl;
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// For pausing
void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n'); 
    cin.get(); 
}

// For file retrieving
void insertAtEnd(Node** head, int data);
void saveToFile(Node* head) {
    ofstream file("list_data.txt");
    if (!file.is_open()) return;
    Node* temp = head;
    while (temp != NULL) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

void loadFromFile(Node** head) {
    ifstream file("list_data.txt");
    if (!file.is_open()) return; 
    int data;
    while (file >> data) {
        insertAtEnd(head, data);
    }
    file.close();
}


// PERSON 2: Creation and Traversal
void createList(Node** head) {
    int n, data, i;
    
    cout << "How many nodes do you want to create? ";
    cin >> n;

    if (n <= 0) {
        cout << "List is empty." << endl;
        return;
    }

    for (i = 1; i <= n; i++) {
        cout << "Enter data for node " << i << ": ";
        cin >> data;
        insertAtEnd(head, data);
    }
}

void traverse(Node* head) {
    cout << "\n--- Current List ---" << endl;
    if (head == NULL) {
        cout << "The list is currently empty." << endl;
    } else {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << "      ";
            temp = temp->next;
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
}

// PERSON 3: Adding of New Node at Start and End
void insertAtStart(Node** head, int data) {
    Node* newNode = createNode(data);

    newNode->next = *head;
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
}

// PERSON 4: Adding New Node Before and After a Node (Target by VALUE)
void insertBefore(Node** head, int target, int data) {
    if (*head == NULL) {
        cout << "\nError: The list is empty. Target " << target << " not found." << endl;
        return;
    }

    if ((*head)->data == target) {
        insertAtStart(head, data);
        return;
    }

    Node* TravNode = *head;

    while (TravNode->next != NULL && TravNode->next->data != target) {
        TravNode = TravNode->next;
    }

    if (TravNode->next == NULL) {
        cout << "\nError: Target value " << target << " not found in the list." << endl;
    } else {
        Node* NewNode = createNode(data);
        NewNode->next = TravNode->next;
        TravNode->next = NewNode;
    }
}

void insertAfter(Node* head, int target, int data) {
    if (head == NULL) {
        cout << "\nError: The list is empty. Target " << target << " not found." << endl;
        return;
    }

    Node* TravNode = head;

    while (TravNode != NULL && TravNode->data != target) {
        TravNode = TravNode->next;
    }

    if (TravNode == NULL) {
        cout << "\nError: Target value " << target << " not found in the list." << endl;
    } else {
        Node* NewNode = createNode(data);
        NewNode->next = TravNode->next;
        TravNode->next = NewNode;
    }
}

// PERSON 5: Deletion of Node at Start and by Value
void deleteAtStart(Node** head) {
    if (*head == NULL) {
        cout << "\nError: The list is currently empty. Cannot delete." << endl;
        return;
    }

    Node* temp = *head;
    *head = temp->next;
    delete temp;
}

void deleteByValue(Node** head, int target) {
    if (*head == NULL) {
        cout << "\nError: The list is currently empty." << endl;
        return;
    }

    Node* current = *head;
    Node* previous = NULL;

    if (current->data == target) {
        *head = current->next;
        delete current;
        return;
    }

    while (current != NULL && current->data != target) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "\nError: Value " << target << " not found in the list." << endl;
        return;
    }

    previous->next = current->next;
    delete current;
}

// PERSON 6: Deletion Before and After a Node (Target by VALUE)
void deleteBefore(Node** head, int target) {
    if (*head == NULL || (*head)->next == NULL) {
        cout << "\nError: List too short to delete 'before'." << endl;
        return;
    }

    if ((*head)->data == target) {
        cout << "\nError: No node exists before the head (" << target << ")." << endl;
        return;
    }

    if ((*head)->next->data == target) {
        Node* temp = *head;
        *head = (*head)->next;
        delete temp;
        return;
    }
    
    Node* temp = *head;
    while (temp->next->next != NULL && temp->next->next->data != target) {
        temp = temp->next;
    }

    if (temp->next->next == NULL) {
        cout << "\nError: Value " << target << " not found." << endl;
    } else {
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }
}

void deleteAfter(Node* head, int target) {
    if (head == NULL) {
        cout << "\nError: List is empty." << endl;
        return;
    }
    
    Node* temp = head;
    
    while (temp != NULL && temp->data != target) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        cout << "\nError: Value " << target << " not found." << endl;
    } else if (temp->next == NULL) {
        cout << "\nError: No node exists after " << target << " (it is the last node)." << endl;
    } else {
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }
}

// List / Choices
int main() {
    Node* head = NULL;
    int choice, data, target;
    loadFromFile(&head);

    while (true) {
        system("cls");
        cout << "\n===== Singly Linked List by Group 1 =====" << endl;
        cout << "1. Create a node" << endl;
        cout << "2. Display all nodes" << endl;
        cout << "3. Adding of new node at the start" << endl;
        cout << "4. Adding of new node at the end" << endl;
        cout << "5. Adding new node before a node" << endl;
        cout << "6. Adding new node after a node" << endl;
        cout << "7. Deletion of node at the start" << endl;
        cout << "8. Deletion of node by value" << endl;
        cout << "9. Deletion of node before a node" << endl;
        cout << "10. Deletion of node after a node" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createList(&head);
                cout << "\n[Success] Node/s created!" << endl;
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
                cout << "\n[Success] Node inserted at start!" << endl;
                waitForEnter();
                break;
            case 4:
                cout << "Enter data to insert at end: ";
                cin >> data;
                insertAtEnd(&head, data);
                cout << "\n[Success] Node inserted at end!" << endl;
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
                cout << "\n[Success] Start node deleted!" << endl;
                waitForEnter();
                break;
            case 8:
                cout << "Enter the value of the node to delete: ";
                cin >> target;
                deleteByValue(&head, target);
                waitForEnter();
                break;
            case 9:
                cout << "Enter the target node value to delete BEFORE it: ";
                cin >> target;
                deleteBefore(&head, target);
                waitForEnter();
                break;
            case 10:
                cout << "Enter the target node value to delete AFTER it: ";
                cin >> target;
                deleteAfter(head, target);
                waitForEnter();
                break;
            case 11:
                cout << "\nExiting program..." << endl;
                saveToFile(head);
                exit(0);
            default:
                cout << "\n[Error] Invalid selection." << endl;
                waitForEnter();
        }
    }
    return 0;
}