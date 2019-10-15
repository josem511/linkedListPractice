#include <iostream>
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

struct node {
    char data;
    node * next = nullptr;
};

void traverse(node * h);
void addDataAtStart(node * & h, node * & t, char d);
void addDataAtEnd(node * & h, node * & t, char d);
void addDataInOrder(node * & h, node * & t, char d);
void removeAtStart(node * & h, node * & t);
void removeAtEnd(node * & h, node * & t);
void removeData(node * & h, node * & t, char d);


int main() {
    //char letters[5];
    std::string word = "";
    node * h1 = nullptr; node * t1 = nullptr;
    node * h2 = nullptr; node * t2 = nullptr;
    node * h3 = nullptr; node * t3 = nullptr;

    std::cout << "Enter a word: ";
    std::cin >> word;
    while(word.length() < 3){
        std::cout << "Enter a word with at least 3 letters: ";
        std::cin >> word;
    }   

    for (char l: word){
        addDataAtStart(h1, t1, l);
    }

    for (char l: word){
        addDataAtEnd(h2, t2, l);
    }

        for (char l: word){
        addDataInOrder(h3, t3, l);
    }
    
    // printing the same word in different ways
    std::cout << "\nAdding each letter to the start of a linked list: \n";
    traverse(h1);
    std::this_thread::sleep_for (std::chrono::seconds(1));

    std::cout << "\nAdding each letter to the end of a linked list: \n";
    traverse(h2);
    std::this_thread::sleep_for (std::chrono::seconds(1));

    std::cout << "\nAdding each letter in alphabetical order to a linked list: \n";
    traverse(h3);
    std::this_thread::sleep_for (std::chrono::seconds(1));


    //notify user that we will remove the first letter from each linked list
    std::cout << "\nNow we'll remove the first element: \n";
    std::this_thread::sleep_for (std::chrono::seconds(1));

    //remove the first letter from each linked list
    removeAtStart(h1,t1);
    removeAtStart(h2,t2);
    removeAtStart(h3,t3);

    //printing new linked lists
    traverse(h1);
    std::this_thread::sleep_for (std::chrono::seconds(1));

    traverse(h2);
    std::this_thread::sleep_for (std::chrono::seconds(1));

    traverse(h3);
    std::this_thread::sleep_for (std::chrono::seconds(1));

    
    return 0;
}


void traverse(node * h) {
    while (h) {
        std::cout << h -> data << " ";
        h = h -> next;
    }
    std::cout << std::endl;
}

void addDataAtStart(node * & h, node * & t, char d) {
    node * newnode = new node;
    newnode -> data = d;
    newnode -> next = h;
    h = newnode;
    if (!t)
        t = newnode;
}

void addDataAtEnd(node * & h, node * & t, char d) {
    if (h == nullptr)
        addDataAtStart(h, t, d);
    else {
        node * newnode = new node;
        newnode -> data = d;
        t->next = newnode;
        t = newnode;
    }
}

void addDataInOrder(node * & h, node * & t, char d){
    //check if list is empty or d is smallest in list
    if (!h || d < h -> data)
        addDataAtStart(h, t, d);
    else if (d > t -> data)
        addDataAtEnd(h,t,d);
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


}

void removeAtStart(node * & h, node * & t) {
    if (!h)
        ;
    else if (h == t) {
        delete h;
        h = nullptr;
        t = nullptr;
    } else {
        node * temp = h;
        h = h -> next;
        delete temp;
    }
}

void removeAtEnd(node * & h, node * & t){
    if (!h)
        ;
    else if (h == t) {
        removeAtStart(h,t);
    } else {
        node * temp = h;
        while(temp -> next != t)
            temp = temp->next;
        t = temp;
        delete temp->next;
        temp->next = nullptr;
    }
}

void removeData(node * & h, node * & t, char d){
    if(h == nullptr)
        return;
    else if(h->data == d)
        removeAtStart(h,t);
    else if(t->data == d)
        removeAtEnd(h,t);
    else {
        node* before_d = h;
        node* after_d = nullptr;
        while(before_d->next != nullptr && before_d->next != t && before_d->next->data != d)
            before_d = before_d->next;
        if(before_d->next != nullptr && before_d->next->data == d){
            after_d = before_d->next->next;
            delete before_d->next;
            before_d->next = after_d;
        }
    }
}