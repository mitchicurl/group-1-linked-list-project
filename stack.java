import java.io.*;
import java.util.*;

class Node {
    int data;
    Node next;

    Node(int data) {
        this.data = data;
        this.next = null;
    }
}

public class StackApp {
    static Node top = null;
    static Scanner sc = new Scanner(System.in);

    static void waitForEnter() {
        System.out.println("\nPress Enter to continue...");
        sc.nextLine();
        sc.nextLine();
    }

    static void push(int data, boolean showMessage) {
        Node newNode = new Node(data);
        newNode.next = top;
        top = newNode;

        if (showMessage)
            System.out.println("[Success] " + data + " pushed!");
    }

    static void pop() {
        if (top == null) {
            System.out.println("Stack Underflow!");
            return;
        }

        int val = top.data;
        top = top.next;

        System.out.println("[Success] " + val + " popped!");
    }

    static void peek() {
        if (top == null)
            System.out.println("Stack empty!");
        else
            System.out.println("Top: " + top.data);
    }

    static void display() {
        if (top == null) {
            System.out.println("Stack empty!");
            return;
        }

        Node temp = top;
        while (temp != null) {
            System.out.println("[" + temp.data + "]");
            temp = temp.next;
        }
    }

    static void saveToFile() {
        try (PrintWriter pw = new PrintWriter("stack_data.txt")) {
            Node temp = top;
            while (temp != null) {
                pw.println(temp.data);
                temp = temp.next;
            }
        } catch (Exception e) {}
    }

    static void loadFromFile() {
        try (Scanner file = new Scanner(new File("stack_data.txt"))) {
            ArrayList<Integer> list = new ArrayList<>();

            while (file.hasNextInt()) {
                list.add(file.nextInt());
            }

            for (int i = list.size() - 1; i >= 0; i--) {
                push(list.get(i), false);
            }
        } catch (Exception e) {}
    }

    public static void main(String[] args) {
        loadFromFile();

        int choice;

        while (true) {
            System.out.println("\n===== STACK MENU =====");
            System.out.println("1. Create\n2. Display\n3. Push\n4. Pop\n5. Peek\n6. Exit");
            System.out.print("Choice: ");

            choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter data: ");
                    push(sc.nextInt(), false);
                    break;
                case 2: display(); break;
                case 3:
                    System.out.print("Enter data: ");
                    push(sc.nextInt(), true);
                    break;
                case 4: pop(); break;
                case 5: peek(); break;
                case 6:
                    saveToFile();
                    System.exit(0);
            }
            waitForEnter();
        }
    }
}
