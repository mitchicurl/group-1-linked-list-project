import os


class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    # For file retrieving
    def save_to_file(self):
        try:
            with open("list_data.txt", "w") as file:
                temp = self.head
                while temp is not None:
                    file.write(f"{temp.data}\n")
                    temp = temp.next
        except IOError:
            pass

    def load_from_file(self):
        if not os.path.exists("list_data.txt"):
            return
        try:
            with open("list_data.txt", "r") as file:
                for line in file:
                    data = int(line.strip())
                    self.insert_at_end(data)
        except (IOError, ValueError):
            pass

    # PERSON 2: Creation and Traversal
    def create_list(self):
        n = int(input("How many nodes do you want to create? "))

        if n <= 0:
            print("List is empty.")
            return

        for i in range(1, n + 1):
            data = int(input(f"Enter data for node {i}: "))
            self.insert_at_end(data)

    def traverse(self):
        print("\n--- Current List ---")
        if self.head is None:
            print("The list is currently empty.")
        else:
            temp = self.head
            # Python equivalent of printing on the same line with spacing
            while temp is not None:
                print(f"{temp.data}      ", end="")
                temp = temp.next
            print()  # Move to the next line
        print("--------------------")

    # PERSON 3: Adding of New Node at Start and End
    def insert_at_start(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node

    def insert_at_end(self, data):
        new_node = Node(data)

        if self.head is None:
            self.head = new_node
            return

        temp = self.head
        while temp.next is not None:
            temp = temp.next

        temp.next = new_node

    # PERSON 4: Adding New Node Before and After a Node (Target by VALUE)
    def insert_before(self, target, data):
        if self.head is None:
            print(f"\nError: The list is empty. Target {target} not found.")
            return

        if self.head.data == target:
            self.insert_at_start(data)
            return

        trav_node = self.head

        while trav_node.next is not None and trav_node.next.data != target:
            trav_node = trav_node.next

        if trav_node.next is None:
            print(f"\nError: Target value {target} not found in the list.")
        else:
            new_node = Node(data)
            new_node.next = trav_node.next
            trav_node.next = new_node

    def insert_after(self, target, data):
        if self.head is None:
            print(f"\nError: The list is empty. Target {target} not found.")
            return

        trav_node = self.head

        while trav_node is not None and trav_node.data != target:
            trav_node = trav_node.next

        if trav_node is None:
            print(f"\nError: Target value {target} not found in the list.")
        else:
            new_node = Node(data)
            new_node.next = trav_node.next
            trav_node.next = new_node

    # PERSON 5: Deletion of Node at Start and by Value
    def delete_at_start(self):
        if self.head is None:
            print("\nError: The list is currently empty. Cannot delete.")
            return

        # Python automatically frees memory when there are no references left
        self.head = self.head.next

    def delete_by_value(self, target):
        if self.head is None:
            print("\nError: The list is currently empty.")
            return

        current = self.head
        previous = None

        if current.data == target:
            self.head = current.next
            return

        while current is not None and current.data != target:
            previous = current
            current = current.next

        if current is None:
            print(f"\nError: Value {target} not found in the list.")
            return

        previous.next = current.next

    # PERSON 6: Deletion Before and After a Node (Target by VALUE)
    def delete_before(self, target):
        if self.head is None or self.head.next is None:
            print("\nError: List too short to delete 'before'.")
            return

        if self.head.data == target:
            print(f"\nError: No node exists before the head ({target}).")
            return

        if self.head.next.data == target:
            self.head = self.head.next
            return

        temp = self.head
        while temp.next.next is not None and temp.next.next.data != target:
            temp = temp.next

        if temp.next.next is None:
            print(f"\nError: Value {target} not found.")
        else:
            to_delete = temp.next
            temp.next = to_delete.next

    def delete_after(self, target):
        if self.head is None:
            print("\nError: List is empty.")
            return

        temp = self.head

        while temp is not None and temp.data != target:
            temp = temp.next

        if temp is None:
            print(f"\nError: Value {target} not found.")
        elif temp.next is None:
            print(f"\nError: No node exists after {target} (it is the last node).")
        else:
            to_delete = temp.next
            temp.next = to_delete.next


# For pausing
def wait_for_enter():
    input("\nPress Enter to continue...")


# List / Choices
def main():
    linked_list = LinkedList()
    linked_list.load_from_file()

    while True:
        # Cross-platform way to clear console (works for Windows & Unix/Mac)
        os.system('cls' if os.name == 'nt' else 'clear')

        print("\n===== Singly Linked List by Group 1 =====")
        print("1. Create a node")
        print("2. Display all nodes")
        print("3. Adding of new node at the start")
        print("4. Adding of new node at the end")
        print("5. Adding new node before a node")
        print("6. Adding new node after a node")
        print("7. Deletion of node at the start")
        print("8. Deletion of node by value")
        print("9. Deletion of node before a node")
        print("10. Deletion of node after a node")
        print("11. Exit")

        try:
            choice = int(input("Enter your choice: "))
        except ValueError:
            print("\n[Error] Invalid input. Please enter a number.")
            wait_for_enter()
            continue

        if choice == 1:
            linked_list.create_list()
            print("\n[Success] Node/s created!")
            wait_for_enter()
        elif choice == 2:
            linked_list.traverse()
            wait_for_enter()
        elif choice == 3:
            data = int(input("Enter data to insert at start: "))
            linked_list.insert_at_start(data)
            print("\n[Success] Node inserted at start!")
            wait_for_enter()
        elif choice == 4:
            data = int(input("Enter data to insert at end: "))
            linked_list.insert_at_end(data)
            print("\n[Success] Node inserted at end!")
            wait_for_enter()
        elif choice == 5:
            target = int(input("Enter target node value: "))
            data = int(input(f"Enter data to insert before {target}: "))
            linked_list.insert_before(target, data)
            wait_for_enter()
        elif choice == 6:
            target = int(input("Enter target node value: "))
            data = int(input(f"Enter data to insert after {target}: "))
            linked_list.insert_after(target, data)
            wait_for_enter()
        elif choice == 7:
            linked_list.delete_at_start()
            print("\n[Success] Start node deleted! (if any existed)")
            wait_for_enter()
        elif choice == 8:
            target = int(input("Enter the value of the node to delete: "))
            linked_list.delete_by_value(target)
            wait_for_enter()
        elif choice == 9:
            target = int(input("Enter the target node value to delete BEFORE it: "))
            linked_list.delete_before(target)
            wait_for_enter()
        elif choice == 10:
            target = int(input("Enter the target node value to delete AFTER it: "))
            linked_list.delete_after(target)
            wait_for_enter()
        elif choice == 11:
            print("\nExiting program...")
            linked_list.save_to_file()
            break
        else:
            print("\n[Error] Invalid selection.")
            wait_for_enter()


if __name__ == "__main__":
    main()