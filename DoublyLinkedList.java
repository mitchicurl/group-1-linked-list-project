import java.util.*;
import java.io.*;

class Node {
    int data;
    Node next;
    Node prev;

    Node(int value) {
        data = value;
        next = null;
        prev = null;
    }
}

public class DoublyLinkedList {

    static Scanner sc = new Scanner(System.in);

    // CREATE NODE
    static Node createNode(int value) {
        return new Node(value);
    }

    static void waitForEnter() {
        System.out.print("\nPress Enter to continue...");
        try {
            System.in.read();
        } catch (Exception e) {}
    }

    // FILE HANDLING
    static void insertAtEnd(Node[] headRef, int data) {
        Node newNode = createNode(data);

        if (headRef[0] == null) {
            headRef[0] = newNode;
            return;
        }

        Node temp = headRef[0];
        while (temp.next != null) {
            temp = temp.next;
        }

        temp.next = newNode;
        newNode.prev = temp;
    }

    static void saveToFile(Node head) {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter("doubly_list_data.txt"));
            Node temp = head;

            while (temp != null) {
                writer.write(temp.data + "\n");
                temp = temp.next;
            }

            writer.close();
        } catch (Exception e) {}
    }

    static void loadFromFile(Node[] headRef) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader("doubly_list_data.txt"));
            String line;

            while ((line = reader.readLine()) != null) {
                int data = Integer.parseInt(line);
                insertAtEnd(headRef, data);
            }

            reader.close();
        } catch (Exception e) {}
    }

    static void createList(Node[] headRef) {
        if (headRef[0] != null) {
            System.out.println("\n[Notice] A list already exists! Please use options 3-6 to add more nodes.");
            return;
        }

        System.out.print("Enter number of nodes to create: ");
        int n = sc.nextInt();

        if (n <= 0) {
            System.out.println("Invalid number of nodes.");
            return;
        }

        for (int i = 1; i <= n; i++) {
            System.out.print("Enter data for node " + i + ": ");
            int data = sc.nextInt();
            insertAtEnd(headRef, data);
        }

        System.out.println("\n[Success] Nodes created!");
    }

    static void traverse(Node head) {
        System.out.println("\n--- Current Doubly Linked List ---");

        if (head == null) {
            System.out.println("The list is currently empty.");
        } else {
            Node temp = head;

            while (temp != null) {
                System.out.print("[" + temp.data + "]");
                if (temp.next != null) System.out.print(" <-> ");
                temp = temp.next;
            }
            System.out.println();
        }

        System.out.println("----------------------------------");
    }

    static void insertAtStart(Node[] headRef, int data) {
        Node newNode = createNode(data);

        if (headRef[0] == null) {
            headRef[0] = newNode;
            return;
        }

        newNode.next = headRef[0];
        headRef[0].prev = newNode;
        headRef[0] = newNode;
    }

    static void insertBefore(Node[] headRef, int target, int data) {
        if (headRef[0] == null) {
            System.out.println("\nError: The list is empty. Target " + target + " not found.");
            return;
        }

        if (headRef[0].data == target) {
            insertAtStart(headRef, data);
            System.out.println("\n[Success] Node inserted before " + target + "!");
            return;
        }

        Node temp = headRef[0];

        while (temp != null && temp.data != target) {
            temp = temp.next;
        }

        if (temp == null) {
            System.out.println("\nError: Target value " + target + " not found in the list.");
            return;
        }

        Node newNode = createNode(data);
        newNode.prev = temp.prev;
        newNode.next = temp;
        temp.prev.next = newNode;
        temp.prev = newNode;

        System.out.println("\n[Success] Node inserted before " + target + "!");
    }

    static void insertAfter(Node head, int target, int data) {
        if (head == null) {
            System.out.println("\nError: The list is empty. Target " + target + " not found.");
            return;
        }

        Node temp = head;

        while (temp != null && temp.data != target) {
            temp = temp.next;
        }

        if (temp == null) {
            System.out.println("\nError: Target value " + target + " not found in the list.");
            return;
        }

        Node newNode = createNode(data);
        newNode.next = temp.next;
        newNode.prev = temp;

        if (temp.next != null) {
            temp.next.prev = newNode;
        }
        temp.next = newNode;

        System.out.println("\n[Success] Node inserted after " + target + "!");
    }

    static void deleteAtStart(Node[] headRef) {
        if (headRef[0] == null) {
            System.out.println("\nError: List is already empty.");
            return;
        }

        headRef[0] = headRef[0].next;

        if (headRef[0] != null) {
            headRef[0].prev = null;
        }
    }

    static void deleteAtEnd(Node[] headRef) {
        if (headRef[0] == null) {
            System.out.println("\nError: List is already empty.");
            return;
        }

        if (headRef[0].next == null) {
            headRef[0] = null;
            return;
        }

        Node temp = headRef[0];
        while (temp.next != null) {
            temp = temp.next;
        }

        temp.prev.next = null;
    }

    static void deleteByValue(Node[] headRef, int target) {
        if (headRef[0] == null) {
            System.out.println("\nError: List is empty.");
            return;
        }

        Node current = headRef[0];

        while (current != null && current.data != target) {
            current = current.next;
        }

        if (current == null) {
            System.out.println("\nError: Value " + target + " not found.");
            return;
        }

        if (current.prev != null) {
            current.prev.next = current.next;
        } else {
            headRef[0] = current.next;
        }

        if (current.next != null) {
            current.next.prev = current.prev;
        }

        System.out.println("\n[Success] Node with value " + target + " deleted!");
    }

    static void deleteBefore(Node[] headRef, int target) {
        if (headRef[0] == null || headRef[0].next == null) {
            System.out.println("\nError: List too short to delete 'before'.");
            return;
        }

        if (headRef[0].data == target) {
            System.out.println("\nError: No node exists before the head (" + target + ").");
            return;
        }

        Node current = headRef[0];

        while (current != null && current.data != target) {
            current = current.next;
        }

        if (current != null) {
            Node delNode = current.prev;

            if (delNode == headRef[0]) {
                headRef[0] = current;
                current.prev = null;
            } else {
                delNode.prev.next = current;
                current.prev = delNode.prev;
            }

            System.out.println("\n[Success] Node before " + target + " deleted!");
        } else {
            System.out.println("\nError: Value " + target + " not found.");
        }
    }

    static void deleteAfter(Node head, int target) {
        if (head == null) {
            System.out.println("\nError: List is empty.");
            return;
        }

        Node current = head;

        while (current != null && current.data != target) {
            current = current.next;
        }

        if (current != null) {
            if (current.next == null) {
                System.out.println("\nError: No node exists after " + target + ".");
            } else {
                Node delNode = current.next;
                current.next = delNode.next;

                if (delNode.next != null) {
                    delNode.next.prev = current;
                }

                System.out.println("\n[Success] Node after " + target + " deleted!");
            }
        } else {
            System.out.println("\nError: Value " + target + " not found.");
        }
    }

    // MAIN PROGRAM
    public static void main(String[] args) {
        Node[] headRef = new Node[1];
        int choice, data, target;

        loadFromFile(headRef);

        while (true) {
            System.out.println("===== Doubly Linked List by Group 1 =====");
            System.out.println("1. Create node(s)");
            System.out.println("2. Display all nodes");
            System.out.println("3. Adding of new node at the start");
            System.out.println("4. Adding of new node at the end");
            System.out.println("5. Adding new node before a node");
            System.out.println("6. Adding new node after a node");
            System.out.println("7. Deletion of node at the start");
            System.out.println("8. Deletion of node at the end");
            System.out.println("9. Deletion of node by value");
            System.out.println("10. Deletion of node before a node");
            System.out.println("11. Deletion of node after a node");
            System.out.println("12. Exit");
            System.out.print("Enter your choice: ");

            choice = sc.nextInt();

            switch (choice) {
                case 1:
                    createList(headRef);
                    waitForEnter();
                    break;
                case 2:
                    traverse(headRef[0]);
                    waitForEnter();
                    break;
                case 3:
                    System.out.print("Enter data to insert at start: ");
                    data = sc.nextInt();
                    insertAtStart(headRef, data);
                    System.out.println("\n[Success] Node inserted at start!");
                    waitForEnter();
                    break;
                case 4:
                    System.out.print("Enter data to insert at end: ");
                    data = sc.nextInt();
                    insertAtEnd(headRef, data);
                    System.out.println("\n[Success] Node inserted at end!");
                    waitForEnter();
                    break;
                case 5:
                    System.out.print("Enter target node value: ");
                    target = sc.nextInt();
                    System.out.print("Enter data to insert before " + target + ": ");
                    data = sc.nextInt();
                    insertBefore(headRef, target, data);
                    waitForEnter();
                    break;
                case 6:
                    System.out.print("Enter target node value: ");
                    target = sc.nextInt();
                    System.out.print("Enter data to insert after " + target + ": ");
                    data = sc.nextInt();
                    insertAfter(headRef[0], target, data);
                    waitForEnter();
                    break;
                case 7:
                    deleteAtStart(headRef);
                    System.out.println("\n[Success] Start node deleted!");
                    waitForEnter();
                    break;
                case 8:
                    deleteAtEnd(headRef);
                    System.out.println("\n[Success] End node deleted!");
                    waitForEnter();
                    break;
                case 9:
                    System.out.print("Enter the value of the node to delete: ");
                    target = sc.nextInt();
                    deleteByValue(headRef, target);
                    waitForEnter();
                    break;
                case 10:
                    System.out.print("Enter the target node value to delete BEFORE it: ");
                    target = sc.nextInt();
                    deleteBefore(headRef, target);
                    waitForEnter();
                    break;
                case 11:
                    System.out.print("Enter the target node value to delete AFTER it: ");
                    target = sc.nextInt();
                    deleteAfter(headRef[0], target);
                    waitForEnter();
                    break;
                case 12:
                    System.out.println("\nSaving data and exiting program...");
                    saveToFile(headRef[0]);
                    return;
                default:
                    System.out.println("\n[Error] Invalid selection.");
                    waitForEnter();
            }
        }
    }
}
