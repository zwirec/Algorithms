/*Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 ­ push front
a = 2 ­ pop front
a = 3 ­ push back
a = 4 ­ pop back
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b ­ ожидаемое значение.Если команда pop вызвана для пустой структуры
данных, то ожидается “­1”.
 ​Реализовать дек с динамическим зацикленным буфером.*/

#include <iostream>

//struct Node {
//    int data;
//    Node *prev;
//    Node *next;
//};
//
//class Deque {
//public:
//    Deque(int data, Node *head, Node *tail);
//
//    Deque();
//
//    ~Deque();
//
//    bool isEmpty();
//
//    void push_front(int data);
//
//    void push_back(int data);
//
//    int pop_front();
//
//    int pop_back();
//
//private:
//    Node *head;
//    Node *tail;
//};
//
//Deque::Deque(int data, Node *head, Node *tail) {
//    this->head = head;
//    this->tail = tail;
//    this->head->data = this->tail->data = data;
//}
//
//Deque::Deque() {
//    this->head = nullptr;
//    this->head = nullptr;
//}
//
//void Deque::push_front(int data) {
//    Node *q = new Node;
//    q->data = data;
//    if (!this->head) {
//        this->head = q;
//        this->tail = q;
//        this->head->prev = this->tail;
//        this->tail->next = this->head;
//    } else {
//        this->head->prev = q;
//        q->next = this->head;
//        q->prev = this->tail;
//        this->head = q;
//    }
//}
//
//void Deque::push_back(int data) {
//    Node *q = new Node;
//    q->data = data;
//    if (!this->head) {
//        this->head = q;
//        this->tail = q;
//        this->head->prev = this->tail;
//        this->tail->next = this->head;
//    } else {
//        q->next = this->head;
//        q->prev = this->tail;
//        this->tail->next = q;
//        this->tail = q;
//    }
//}
//
//int Deque::pop_front() {
//    if (!isEmpty()) {
//        if (this->head == this->tail) {
//            int res = this->head->data;
//            delete this->head;
//            this->head = this->tail = nullptr;
//            return res;
//        }
//        int res = this->head->data;
//        Node *temp = this->head->next;
//        delete head;
//        this->head = temp;
//        this->head->prev = this->tail;
//        this->tail->next = this->head;
//        return res;
//    }
//    return -1;
//}
//
//int Deque::pop_back() {
//    if (!isEmpty()) {
//        if (this->head == this->tail) {
//            int res = this->tail->data;
//            delete this->tail;
//            this->head = this->tail = nullptr;
//            return res;
//        }
//        int res = this->tail->data;
//        Node *temp = this->tail->prev;
//        delete tail;
//        this->tail = temp;
//        this->tail->next = this->head;
//        this->head->prev = this->tail;
//        return res;
//    }
//    return -1;
//}
//
//bool Deque::isEmpty() {
//    return this->head == nullptr;
//}
//
//Deque::~Deque() {
//    while (!isEmpty()) {
//        pop_back();
//    }
//}

#include <deque>

class Deque {
private:
    size_t size;
    int *deque;
    size_t head;
    size_t tail;
public:
    Deque(size_t size);

    ~Deque();

    size_t get_size();

    void push_back(int data);

    void push_front(int data);

    int pop_back();

    int pop_front();

    bool isEmpty();

};

size_t Deque::get_size() {
    if (tail < head) {
        return size - head + tail;
    } else {
        return tail - head;
    }
}

Deque::Deque(size_t size) : size(size), head(0), tail(0) {
    deque = new int[size];
}

void Deque::push_back(int data) {
    if (head == (tail + 1) % size) {
        int *newDeque = new int[size * 2];
        for (size_t i = 0; i < size - 2; i++) {
            newDeque[i] = deque[head];
            head = (head + 1) % size;
        }
        deque = newDeque;
        head = 0;
        tail = size - 1;
        size *= 2;
    }
    deque[tail] = data;
    tail = (tail + 1) % size;
}

void Deque::push_front(int data) {
    if (head == (tail + 1) % size) {
        int *newDeque = new int[size * 2];
        for (size_t i = 0; i < size - 2; i++) {
            newDeque[i] = deque[head];
            head = (head + 1) % size;
        }
        deque = newDeque;
        head = 0;
        tail = size - 1;
        size *= 2;
    }
    head = (head - 1 + size) % size;
    deque[head] = data;
}

bool Deque::isEmpty() {
    return head == tail;
}

int Deque::pop_back() {
    if (isEmpty()) {
        return -1;
    }
    if (get_size() < size / 4) {
        int *newDeque = new int[size / 2];
        size_t dequeSize = get_size();
        for (size_t i = 0; i < dequeSize - 1; ++i) {
            newDeque[i] = deque[head];
            head = (head + 1) % size;
        }
        deque = newDeque;
        head = 0;
        tail = dequeSize;
        size /= 2;
    }
    tail = (tail - 1 + size) % size;
    return deque[tail];
}

int Deque::pop_front() {
    if (isEmpty()) {
        return -1;
    }
    if (get_size() < size / 4) {
        int *newDeque = new int[size / 2];
        size_t dequeSize = get_size();
        for (size_t i = 0; i < dequeSize - 1; ++i) {
            newDeque[i] = deque[head];
            head = (head + 1) % size;
        }
        deque = newDeque;
        head = 0;
        tail = dequeSize;
        size /= 2;
    }
    int result = deque[head];
    head = (head + 1) % size;
    return result;
}

Deque::~Deque() {
    delete [] deque;
}

bool solve(int *commands, int *nums, size_t sz) {
    Deque deque = Deque(sz);
    for (size_t i = 0; i < sz; ++i) {
        switch (commands[i]) {
            case 1: {
                deque.push_front(nums[i]);
                break;
            }
            case 2: {
                if (deque.pop_front() != nums[i])
                    return false;
                break;
            }
            case 3: {
                deque.push_back(nums[i]);
                break;
            }
            case 4: {
                if (deque.pop_back() != nums[i])
                    return false;
                break;
            }
            default:
                break;
        }
    }
    return true;
}

int main() {
    size_t sz = 0;
    std::deque<int> a;
    std::cin >> sz;
    int *commands = new int[sz];
    int *nums = new int[sz];
    for (size_t i = 0; i < sz; ++i) {
        std::cin >> commands[i];
        std::cin >> nums[i];
    }
    if (solve(commands, nums, sz)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    delete[] commands;
    delete[] nums;

    return 0;
}