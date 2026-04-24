#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void waitForEnter() {
    cout << "\nPress Enter to continue...";
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