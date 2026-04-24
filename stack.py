from os import system
from pathlib import Path

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

def waitForEnter():
    print("\nPress Enter to continue...")
    input()

def saveToFile(top):
    with open("stack_data.txt", "w") as file:
        temp = top
        while temp is not None:
            file.write(f"{temp.data}\n")
            temp = temp.next

def loadFromFile(top):
    if not Path("stack_data.txt").exists():
        return

    tempArr = []
    count = 0

    with open("stack_data.txt", "r") as file:
        for line in file:
            data = int(line.strip())
            tempArr.append(data)
            count += 1

    i = count - 1
    while i >= 0:
        push(top, tempArr[i], 0)
        i -= 1

def createStack(top):
    if top[0] is not None:
        print("\n[Notice] A stack already exists! Please use Option 3 to Push more items.")
        return

    while True:
        data = input("Enter data to push: ")

        if not data.lstrip("-").isdigit():
            print("  -> [Error] Invalid input! Letters/characters are not allowed.")
            print("\nReturning to main menu...\n")
            return

        push(top, int(data), 0)

        while True:
            resp = input("Add another node [Y/N]? ")

            if resp in ["Y", "y", "N", "n"]:
                break
            else:
                print("  -> [Error] Invalid input. Please enter 'Y' for Yes or 'N' for No.")

        if resp in ["N", "n"]:
            break

    print("\n[Success] Initial Stack created!")

def display(top):
    if top is None:
        print("\nError: The stack is empty!")
        return

    temp = top

    print("\n--- Current Stack ---")
    while temp is not None:
        print(f"[{temp.data}]")
        temp = temp.next
    print("-------------------")

def push(top, data, showMessage):
    newNode = Node(data)
    newNode.next = top[0]
    top[0] = newNode

    if showMessage:
        print(f"\n[Success] {data} was pushed to the top of the stack!")

def pop(top):
    if top[0] is None:
        print("\nError: Stack Underflow! The stack is already empty.")
        return

    temp = top[0]
    poppedData = temp.data

    top[0] = top[0].next

    print(f"\n[Success] {poppedData} was popped from the stack!")

def peek(top):
    if top[0] is None:
        print("\nError: The stack is empty!")
    else:
        print(f"\n[Peek] The item at the TOP of the stack is: {top[0].data}")

def main():
    top = [None]
    loadFromFile(top)

    while True:
        system("cls")

        print("===== Stack Implementation by Group 1 =====")
        print("1. Create stack")
        print("2. Display stack")
        print("3. Push (insert item)")
        print("4. Pop (remove item)")
        print("5. Peek (view top item)")
        print("6. Exit")
        choice = input("Enter your choice: ")

        if not choice.isdigit():
            print("\n[Error] Invalid input! Letters/symbols are not allowed.")
            waitForEnter()
            continue

        choice = int(choice)

        if choice == 1:
            createStack(top)
            waitForEnter()

        elif choice == 2:
            display(top[0])
            waitForEnter()

        elif choice == 3:
            data = input("Enter data to push onto the stack: ")
            if not data.lstrip("-").isdigit():
                print("\n[Error] Invalid input! Please enter a number.")
            else:
                push(top, int(data), 1)
            waitForEnter()

        elif choice == 4:
            pop(top)
            waitForEnter()

        elif choice == 5:
            peek(top)
            waitForEnter()

        elif choice == 6:
            print("\nSaving data and exiting program...")

            saveToFile(top[0])

            while top[0] is not None:
                temp = top[0]
                top[0] = top[0].next
                del temp

            exit()

        else:
            print("\n[Error] Invalid selection.")
            waitForEnter()

main()
