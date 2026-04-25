#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.clear();
    cin.ignore(1000, '\n'); 
    cin.get(); 
}

void enqueue(Node** front, Node** rear, int data, int showMessage);

void saveToFile(Node* front) {
    ofstream file("queue_data.txt");
    if (!file.is_open()) return;
    
    Node* temp = front;
    while (temp != NULL) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

void loadFromFile(Node** front, Node** rear) {
    ifstream file("queue_data.txt");
    if (!file.is_open()) return; 
    
    int data;
    while (file >> data) {
        enqueue(front, rear, data, 0); 
    }
    file.close();
}

void createQueue(Node** front, Node** rear) {
    if (*front != NULL) {
        cout << "\n[Notice] A queue already exists! Please use Option 3 to Enqueue." << endl;
        return;
    }

    char resp;
    int data;

    do {
        cout << "Enter data to enqueue: ";
        
        if (!(cin >> data)) {
            cout << "  -> [Error] Invalid input! Letters/characters are not allowed." << endl;
            cout << "\nReturning to main menu..." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            return; 
        }
        
        enqueue(front, rear, data, 0); 

        while (true) {
            cout << "Add another node [Y/N]? ";
            cin >> resp; 
            
            if (resp == 'Y' || resp == 'y' || resp == 'N' || resp == 'n') {
                break; 
            } else {
                cout << "  -> [Error] Invalid input. Please enter 'Y' for Yes or 'N' for No." << endl;
            }
        }
        
    } while (resp == 'Y' || resp == 'y');
    
    cout << "\n[Success] Initial Queue created!" << endl;
}

void display(Node** front, Node** rear) {
    Node* TravNode = *front;

    if (TravNode == NULL) {
        cout << "\nError: The Queue is Empty!" << endl;
    } else {
        Node* tempFront = NULL;
        Node* tempRear = NULL;

        cout << "\n--- Current Queue Line ---" << endl;
        cout << "FRONT -> ";

        do {
            cout << "[" << TravNode->data << "] -> ";

            *front = TravNode->next;

            if (*front == NULL) {
                *rear = NULL;
            }

            TravNode->next = NULL;

            if (tempFront == NULL) {
                tempFront = tempRear = TravNode;
            } else {
                tempRear->next = TravNode;
                tempRear = TravNode;
            }

            TravNode = *front;

        } while (*front != NULL);

        cout << "REAR" << endl;
        cout << "--------------------------" << endl;

        *front = tempFront;
        *rear = tempRear;
    }
}

void enqueue(Node** front, Node** rear, int data, int showMessage) {
    Node* NewNode = new Node(); 
    if (NewNode == NULL) {
        cout << "\nError: Memory allocation failed!" << endl;
        return;
    }
    
    NewNode->data = data;
    NewNode->next = NULL;

    if (*rear == NULL) {
        *front = *rear = NewNode;
    } else {
        (*rear)->next = NewNode;
        *rear = NewNode;
    }
    
    if (showMessage) {
        cout << "\n[Success] " << data << " fell in line at the rear!" << endl;
    }
}

void dequeue(Node** front, Node** rear) {
    Node* DelNode = *front;

    if (DelNode == NULL) {
        cout << "\nError: The Queue is Empty!" << endl;
        return;
    } 
    
    int servedData = DelNode->data; 
    
    *front = (*front)->next;
    DelNode->next = NULL;
    delete DelNode; 
    
    if (*front == NULL) {
        *rear = NULL;
    }

    cout << "\n[Success] " << servedData << " was served and left the queue!" << endl;
}

void peekFront(Node* front) {
    if (front == NULL) {
        cout << "\nError: The Queue is Empty!" << endl;
    } else {
        cout << "\n[Peek] The next in line at the front is: " << front->data << endl;
    }
}

int main() {
    Node* front = NULL; 
    Node* rear = NULL;  
    int choice, data;

    loadFromFile(&front, &rear);

    while (true) {
        system("cls"); 
        
        cout << "===== Queue Implementation by Group 1 =====" << endl;
        cout << "1. Create queue" << endl;
        cout << "2. Display queue" << endl;
        cout << "3. Enqueue (insert item)" << endl;
        cout << "4. Dequeue (remove item)" << endl;
        cout << "5. Peek (view front item)" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cout << "\n[Error] Invalid input! Letters/symbols are not allowed." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            waitForEnter(); 
            continue; 
        }

        switch (choice) {
            case 1:
                createQueue(&front, &rear);
                waitForEnter();
                break;
            case 2:
                display(&front, &rear);
                waitForEnter();
                break;
            case 3:
                cout << "Enter data to enqueue: ";
                if (!(cin >> data)) {
                    cout << "\n[Error] Invalid input! Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else {
                    enqueue(&front, &rear, data, 1); 
                }
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
                cout << "\nSaving data and exiting program..." << endl;
                saveToFile(front);
                
                while (front != NULL) {
                    Node* temp = front;
                    front = front->next;
                    delete temp;
                }
                exit(0);
            default:
                cout << "\n[Error] Invalid selection." << endl;
                waitForEnter();
        }
    }
    return 0;
}
