#include <iostream>

struct node {
    char data;
    node * next = nullptr;
};

void traverse(node * h);
void addDataAtStart(node * & h, char d);
void addDataAtEnd(node * & h, char d);
void addDataInOrder(node * & h, char d);


int main() {
    char letters[5];
    node * h1 = nullptr;
    node * h2 = nullptr;

    for (int i = 0; i < 5; i++) {
        std::cout << "Enter a character: ";
        std::cin >> letters[i];
    }

    for (int i = 0; i < 5; i++) {
        addDataAtEnd(h1, letters[i]);
        addDataInOrder(h2, letters[i]);
    }

    traverse(h1);
    // std::cout << h2 -> data << " ";
    traverse(h2);

    return 0;
}


void traverse(node * h) {
    while (h) {
        std::cout << h -> data << " ";
        h = h -> next;
    }
    std::cout << std::endl;
}

void addDataAtStart(node * & h, char d) {
    node * newnode = new node;
    newnode -> data = d;
    newnode -> next = h;
    h = newnode;
}

void addDataAtEnd(node * & h, char d) {
    if (h == nullptr) {
        addDataAtStart(h, d);
        return;
    }

    node * newnode = new node;
    newnode -> data = d;

    node * temp = h;
    while (temp -> next) {
        temp = temp -> next;
    }
    temp -> next = newnode;
}

void addDataInOrder(node * & h, char d) {
    //check if list is empty or d is smallest in list
    if (!h || d < h -> data) {
        addDataAtStart(h, d);
    }
    else {
    //two temp pointers
    node * ptr1 = h;
    node * ptr2 = h -> next;

    //traverse until 2nd ptr gets to NULL or if its value is bigger than d
    while (ptr2 && ptr2 -> data < d) {
        ptr1 = ptr2;
        ptr2 = ptr2 -> next;
    }
    
    //allocate mem for new node
    node * newnode = new node;
    newnode -> data = d;

    //update ptrs
    ptr1 -> next = newnode;
    newnode -> next = ptr2;
    }

    //traverse(h);
}