
#include <algorithm>
#include <stack>
#include <iostream>

#include "Stack.h"

using namespace std;

class Queue {
private:
    Stack R;
    Stack L;
    Stack L_d;
    Stack R_copy;
    Stack R_d_copy;
    Stack S;
    int toCopy = 0;
    bool recopy = false;
    bool copied = false;

    bool checkRecopy();

    bool checkNormal();

    void additionalOperations();

public:
    int pop();

    void push(int data);

    bool isEmpty();

};

void Queue::push(int data) {
    if (!recopy) {
        L.push(data);
        if (R_d_copy.get_size() > 0) {
            R_d_copy.pop();
        }
        checkRecopy();
    } else {
        L_d.push(data);
        checkNormal();
    }
}

int Queue::pop() {
    if (!recopy) {
        int tmp = R.pop();
        R_copy.pop();
        if (R_d_copy.get_size() > 0) {
            R_d_copy.pop();
        }
        checkRecopy();
        return tmp;
    } else {
        int tmp = R_copy.pop();
        if (toCopy > 0) {
            toCopy--;
        } else {
            R.pop();
            R_d_copy.pop();
        }
        checkNormal();
        return tmp;
    }
}

bool Queue::checkRecopy() {
    recopy = (L.get_size() > R.get_size());
    if (recopy) {
        toCopy = (int) R.get_size();
        copied = false;
        checkNormal();
    }
    return true;
}

bool Queue::checkNormal() {
    additionalOperations();
    recopy = (S.get_size() != 0);
    return true;
}

void Queue::additionalOperations() {
    int toDo = 3;
    while ((!copied) && toDo > 0 && R.get_size() > 0) {
        S.push(R.pop());
        toDo--;
    }
    while (toDo > 0 && L.get_size() > 0) {
        copied = true;
        int tmp = L.pop();
        R.push(tmp);
        R_d_copy.push(tmp);
        toDo--;
    }
    while (toDo > 0 && S.get_size() > 0) {
        int tmp = S.pop();
        if (toCopy > 0) {
            R.push(tmp);
            R_d_copy.push(tmp);
            toCopy--;
        }
        toDo--;
    }
    if (S.get_size() == 0) {
        std::swap(L, L_d);
        std::swap(R_copy, R_d_copy);
    }
}

bool Queue::isEmpty() {
    return !recopy && R.get_size() == 0;
}

int main() {
    Queue queue;
    for (size_t i = 0; i < 10; i++) {
        queue.push(i);
    }
    while (!queue.isEmpty()) {
        std::cout << queue.pop() << std::endl;
    }

    return 0;
}