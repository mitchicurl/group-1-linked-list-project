from os import system
from pathlib import Path

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

def waitForEnter():
    print("\nPress Enter to continue...")
    input()

def saveToFile(front):
    with open("queue_data.txt", "w") as file:
        temp = front
        while temp != None:
            file.write(f"{temp.data}")
            temp = temp.next

def enqueue(front, rear, data, showMessage):
    newNode = Node(data)

    if rear == None:
        front = rear = newNode
    else:
        rear.next = newNode
        rear = newNode

    if showMessage:
        print(f"\n[Success] {data} fell in line at the rear!")

    return front, rear

def loadFromFile(front, rear):
    if not Path("queue_data.txt").exists():
        return front, rear

    with open("queue_data.txt", "r") as file:
        for line in file:
            data = line.strip()
            if data:
                front, rear = enqueue(front, rear, int(data), 0)

    return front, rear

def createQueue(front, rear):
    if front != None:
        print("\n[Notice] A queue already exists! Please use Option 3 to Enqueue.")
        return front, rear

    resp = ""
    data = 0

    while True:
        print("Enter data to enqueue: ")

        try:
            data = int(input())
        except:
            print("  -> [Error] Invalid input! Letters/characters are not allowed.")
            print("\nReturning to main menu...\n")
            return front, rear

        front, rear = enqueue(front, rear, data, 0)

        while True:
            print("Add another node [Y/N]? ")
            resp = input().strip()

            if resp in ['Y', 'y', 'N', 'n']:
                break
            else:
                print("  -> [Error] Invalid input. Please enter 'Y' for Yes or 'N' for No.")

        if resp not in ['Y', 'y']:
            break

    print("\n[Success] Initial Queue created!")
    return front, rear

def display(front, rear):
    travNode = front

    if travNode == None:
        print("\nError: The Queue is Empty!")
        return front, rear

    tempFront = None
    tempRear = None

    print("\n--- Current Queue Line ---")
    print("FRONT -> ", end="")

    while True:
        print(f"[{travNode.data}] -> ", end="")

        front = travNode.next

        if front == None:
            rear = None

        travNode.next = None

        if tempFront == None:
            tempFront = tempRear = travNode
        else:
            tempRear.next = travNode
            tempRear = travNode

        travNode = front

        if front == None:
            break

    print("REAR")
    print("--------------------------")

    return tempFront, tempRear

def dequeue(front, rear):
    delNode = front

    if delNode == None:
        print("\nError: The Queue is Empty!")
        return front, rear

    servedData = delNode.data

    front = front.next
    delNode.next = None

    if front == None:
        rear = None

    print(f"\n[Success] {servedData} was served and left the queue!")

    return front, rear

def peekFront(front):
    if front == None:
        print("\nError: The Queue is Empty!")
    else:
        print(f"\n[Peek] The next in line at the front is: {front.data}")

def main():
    front = None
    rear = None

    front, rear = loadFromFile(front, rear)

    while True:
        system("cls")

        print("===== Queue Implementation by Group 1 =====")
        print("1. Create queue")
        print("2. Display queue")
        print("3. Enqueue (insert item)")
        print("4. Dequeue (remove item)")
        print("5. Peek (view front item)")
        print("6. Exit")
        print("Enter your choice: ")

        try:
            choice = int(input())
        except:
            print("\n[Error] Invalid input! Letters/symbols are not allowed.")
            waitForEnter()
            continue

        if choice == 1:
            front, rear = createQueue(front, rear)
            waitForEnter()
        elif choice == 2:
            front, rear = display(front, rear)
            waitForEnter()
        elif choice == 3:
            print("Enter data to enqueue: ")
            try:
                data = int(input())
                front, rear = enqueue(front, rear, data, 1)
            except:
                print("\n[Error] Invalid input! Please enter a number.")
            waitForEnter()
        elif choice == 4:
            front, rear = dequeue(front, rear)
            waitForEnter()
        elif choice == 5:
            peekFront(front)
            waitForEnter()
        elif choice == 6:
            print("\nSaving data and exiting program...")
            saveToFile(front)

            while front != None:
                temp = front
                front = front.next

            exit(0)
        else:
            print("\n[Error] Invalid selection.")
            waitForEnter()

main()
