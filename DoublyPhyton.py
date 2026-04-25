import os


class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None


class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.filename = "doubly_list_data.txt"

    # --- File I/O Functions ---
    def save_to_file(self):
        try:
            with open(self.filename, "w") as f:
                temp = self.head
                while temp:
                    f.write(f"{temp.data}\n")
                    temp = temp.next
        except IOError:
            print("Error saving to file.")

    def load_from_file(self):
        if not os.path.exists(self.filename):
            return
        try:
            with open(self.filename, "r") as f:
                for line in f:
                    if line.strip():
                        self.insert_at_end(int(line.strip()))
        except (IOError, ValueError):
            pass

    # --- PERSON 2: Creation and Traversal ---
    def create_list(self):
        if self.head:
            print("\n[Notice] A list already exists! Use other options to add nodes.")
            return

        try:
            n = int(input("Enter number of nodes to create: "))
            if n <= 0:
                print("Invalid number of nodes.")
                return

            for i in range(1, n + 1):
                data = int(input(f"Enter data for node {i}: "))
                self.insert_at_end(data)
            print("\n[Success] Nodes created!")
        except ValueError:
            print("[Error] Please enter valid integers.")

    def traverse(self):
        print("\n--- Current Doubly Linked List ---")
        if not self.head:
            print("The list is currently empty.")
        else:
            temp = self.head
            elements = []
            while temp:
                elements.append(f"[{temp.data}]")
                temp = temp.next
            print(" <-> ".join(elements))
        print("----------------------------------")

    # --- PERSON 3: Adding of New Node at Start and End ---
    def insert_at_start(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return

        new_node.next = self.head
        self.head.prev = new_node
        self.head = new_node

    def insert_at_end(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return

        temp = self.head
        while temp.next:
            temp = temp.next

        temp.next = new_node
        new_node.prev = temp

    # --- PERSON 4: Adding New Node Before and After a Node ---
    def insert_before(self, target, data):
        if not self.head:
            print(f"\nError: List empty. Target {target} not found.")
            return

        if self.head.data == target:
            self.insert_at_start(data)
            return

        curr = self.head
        while curr and curr.data != target:
            curr = curr.next

        if not curr:
            print(f"\nError: Target {target} not found.")
            return

        new_node = Node(data)
        new_node.prev = curr.prev
        new_node.next = curr
        curr.prev.next = new_node
        curr.prev = new_node

    def insert_after(self, target, data):
        if not self.head:
            print(f"\nError: List empty. Target {target} not found.")
            return

        curr = self.head
        while curr and curr.data != target:
            curr = curr.next

        if not curr:
            print(f"\nError: Target {target} not found.")
            return

        new_node = Node(data)
        new_node.next = curr.next
        new_node.prev = curr
        if curr.next:
            curr.next.prev = new_node
        curr.next = new_node

    # --- PERSON 5: Deletion of Node at Start and by Value ---
    def delete_at_start(self):
        if not self.head:
            print("\nError: List is already empty.")
            return

        self.head = self.head.next
        if self.head:
            self.head.prev = None

    def delete_at_end(self):
        if not self.head:
            print("\nError: List is already empty.")
            return

        if not self.head.next:
            self.head = None
            return

        temp = self.head
        while temp.next:
            temp = temp.next

        temp.prev.next = None

    def delete_by_value(self, target):
        if not self.head:
            print("\nError: List is empty.")
            return

        curr = self.head
        while curr and curr.data != target:
            curr = curr.next

        if not curr:
            print(f"\nError: Value {target} not found.")
            return

        if curr.prev:
            curr.prev.next = curr.next
        else:
            self.head = curr.next

        if curr.next:
            curr.next.prev = curr.prev

        print(f"\n[Success] Node with value {target} deleted!")

    # --- PERSON 6: Deletion Before and After a Node ---
    def delete_before(self, target):
        if not self.head or not self.head.next:
            print("\nError: List too short.")
            return

        if self.head.data == target:
            print(f"\nError: No node before head ({target}).")
            return

        curr = self.head
        while curr and curr.data != target:
            curr = curr.next

        if curr:
            del_node = curr.prev
            if del_node == self.head:
                self.head = curr
                curr.prev = None
            else:
                del_node.prev.next = curr
                curr.prev = del_node.prev
            print(f"\n[Success] Node before {target} deleted!")
        else:
            print(f"\nError: Value {target} not found.")

    def delete_after(self, target):
        if not self.head:
            print("\nError: List is empty.")
            return

        curr = self.head
        while curr and curr.data != target:
            curr = curr.next

        if curr:
            if not curr.next:
                print(f"\nError: No node after {target}.")
            else:
                del_node = curr.next
                curr.next = del_node.next
                if del_node.next:
                    del_node.next.prev = curr
                print(f"\n[Success] Node after {target} deleted!")
        else:
            print(f"\nError: Value {target} not found.")


def wait_for_enter():
    input("\nPress Enter to continue...")


def main():
    dll = DoublyLinkedList()
    dll.load_from_file()

    while True:
        # 'cls' for Windows, 'clear' for Mac/Linux
        os.system('cls' if os.name == 'nt' else 'clear')

        print("===== Doubly Linked List by Group 1 (Python) =====")
        print("1. Create node(s)")
        print("2. Display all nodes")
        print("3. Adding of new node at the start")
        print("4. Adding of new node at the end")
        print("5. Adding new node before a node")
        print("6. Adding new node after a node")
        print("7. Deletion of node at the start")
        print("8. Deletion of node at the end")
        print("9. Deletion of node by value")
        print("10. Deletion of node before a node")
        print("11. Deletion of node after a node")
        print("12. Exit")

        try:
            choice = int(input("Enter your choice: "))
        except ValueError:
            print("\n[Error] Please enter a number.")
            wait_for_enter()
            continue

        if choice == 1:
            dll.create_list()
        elif choice == 2:
            dll.traverse()
        elif choice == 3:
            data = int(input("Enter data to insert at start: "))
            dll.insert_at_start(data)
            print("\n[Success] Node inserted at start!")
        elif choice == 4:
            data = int(input("Enter data to insert at end: "))
            dll.insert_at_end(data)
            print("\n[Success] Node inserted at end!")
        elif choice == 5:
            target = int(input("Enter target node value: "))
            data = int(input(f"Enter data to insert before {target}: "))
            dll.insert_before(target, data)
        elif choice == 6:
            target = int(input("Enter target node value: "))
            data = int(input(f"Enter data to insert after {target}: "))
            dll.insert_after(target, data)
        elif choice == 7:
            dll.delete_at_start()
            print("\n[Success] Start node deleted!")
        elif choice == 8:
            dll.delete_at_end()
            print("\n[Success] End node deleted!")
        elif choice == 9:
            target = int(input("Enter value to delete: "))
            dll.delete_by_value(target)
        elif choice == 10:
            target = int(input("Enter target value to delete BEFORE: "))
            dll.delete_before(target)
        elif choice == 11:
            target = int(input("Enter target value to delete AFTER: "))
            dll.delete_after(target)
        elif choice == 12:
            print("\nSaving data and exiting...")
            dll.save_to_file()
            break
        else:
            print("\n[Error] Invalid selection.")

        wait_for_enter()


if __name__ == "__main__":
    main()