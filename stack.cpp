#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void push(Node*& top, int data, bool showMessage);

void saveToFile(Node* top) {
    ofstream file("stack_data.txt");
    if (!file) return;

    Node* temp = top;
    while (temp != NULL) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

void loadFromFile(Node*& top) {
    ifstream file("stack_data.txt");
    if (!file) return;

    int data;
    int tempArr[1000];
    int count = 0;

    while (file >> data) {
        tempArr[count++] = data;
    }

    for (int i = count - 1; i >= 0; i--) {
        push(top, tempArr[i], false);
    }
    file.close();
}

void createStack(Node*& top) {
    if (top != NULL) {
        cout << "\n[Notice] Stack already exists!\n";
        return;
    }

    char resp;
    int data;

    do {
        cout << "Enter data: ";
        if (!(cin >> data)) {
            cout << "[Error] Invalid input!\n";
            return;
        }

        push(top, data, false);

        do {
            cout << "Add another node [Y/N]? ";
            cin >> resp;
        } while (!(resp == 'Y' || resp == 'y' || resp == 'N' || resp == 'n'));

    } while (resp == 'Y' || resp == 'y');

    cout << "\n[Success] Stack created!\n";
}

void display(Node* top) {
    if (!top) {
        cout << "\nStack is empty!\n";
        return;
    }

    cout << "\n--- Stack ---\n";
    while (top) {
        cout << "[" << top->data << "]\n";
        top = top->next;
    }
}

void push(Node*& top, int data, bool showMessage) {
    Node* newNode = new Node();

    newNode->data = data;
    newNode->next = top;
    top = newNode;

    if (showMessage)
        cout << "[Success] " << data << " pushed!\n";
}

void pop(Node*& top) {
    if (!top) {
        cout << "\nStack Underflow!\n";
        return;
    }

    Node* temp = top;
    int val = temp->data;

    top = top->next;
    delete temp;

    cout << "[Success] " << val << " popped!\n";
}

void peek(Node* top) {
    if (!top)
        cout << "Stack empty!\n";
    else
        cout << "Top: " << top->data << endl;
}

int main() {
    Node* top = NULL;
    int choice, data;

    loadFromFile(top);

    while (true) {
        system("cls");

        cout << "===== STACK MENU =====\n";
        cout << "1. Create\n2. Display\n3. Push\n4. Pop\n5. Peek\n6. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createStack(top); break;
            case 2: display(top); break;
            case 3:
                cout << "Enter data: ";
                cin >> data;
                push(top, data, true);
                break;
            case 4: pop(top); break;
            case 5: peek(top); break;
            case 6:
                saveToFile(top);
                while (top) {
                    Node* temp = top;
                    top = top->next;
                    delete temp;
                }
                exit(0);
        }
        waitForEnter();
    }
}
