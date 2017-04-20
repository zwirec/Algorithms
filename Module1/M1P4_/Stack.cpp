//
// Created by Даниил Котельников on 24.03.17.
//

#include <exception>
#include "Stack.h"


Stack::Stack() {
    top = nullptr;
    size = 0;
}

void Stack::push(int r) {
    Node *q = new Node;
    q->data = r;
    if (isEmpty()) {
        q->next = nullptr;
    } else {
        q->next = top;
    }
    top = q;
    size++;
}

int Stack::pop() {
    if (!isEmpty()) {
        int result = top->data;
        Node *temp = top->next;
        delete top;
        top = temp;
        size--;
        return result;
    }
    throw (new std::exception );
}

bool Stack::isEmpty() {
    return size==0;
}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

size_t Stack::get_size() {
    return size;
}

Stack::Stack(const Stack &other) {
    Node* tmp = other.top;
    this->top = tmp;
    this->size = other.size;
}

Stack &Stack::operator=(const Stack &rhs) {
    top = rhs.top;
    size = rhs.size;
    return *this;
}
