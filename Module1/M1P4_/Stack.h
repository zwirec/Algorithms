//
// Created by Даниил Котельников on 24.03.17.
//

#ifndef M1P4_STACK_H
#define M1P4_STACK_H


struct Node {
    Node *next;
    int data;
};

class Stack {
private:
    Node *top;
    size_t size;
public:
    Stack();

    Stack(const Stack &other);

    Stack &operator=(const Stack &rhs);

    ~Stack();

    void push(int data);

    int pop();

    size_t get_size();

    bool isEmpty();

};


#endif //M1P4_STACK_H
