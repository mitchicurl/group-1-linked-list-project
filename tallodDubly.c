struct Node *START = NULL;

void insertAtStart (int value) {
    struct Node* Newnode = (struct Node*) malloc(sizeof (struct Node));

    Newnode -> data = value;

    Newnode -> prev = NULL;
    Newnode -> next = NULL;

    if (HEAD == NULL) {
        HEAD == TAIL = Newnode;
    }else {
        Newnode -> next = HEAD;
        HEAD -> prev = Newnode;
        HEAD = Newnode;
    }
    Newnode = NULL;

    return 1;
}

void insertAtEnd (int value) {
    struct Node* Newnode = (struct Node*) malloc(sizeof (struct Node));

    Newnode -> data = value;

    Newnode -> prev = NULL;
    Newnode -> next = NULL;

    if (TAIL == NULL) {
        HEAD == TAIL = Newnode;
    }else {
        Newnode -> prev = TAIL;
        TAIL -> next = Newnode;
        TAIL = Newnode;
    }
    Newnode = NULL;

    return 1;
}