#include <iostream>

struct Rectangle {
    int width;
    int height;

    int get_area();

    Rectangle() : width(0), height(0) {};

    Rectangle(int w, int h);
};

int Rectangle::get_area() {
    return width * height;
}

Rectangle::Rectangle(int w, int h) : width(w), height(h) {

}

struct Node {
    Node *next;
    Rectangle rectangle;
};

class Stack {
private:
    Node *top;
public:
    Stack();

    ~Stack();

    void push(Rectangle data);

    Rectangle pop();


    bool isEmpty();

    int topHeight();

    void increaseWidth(int i);
};

Stack::Stack() {
    top = nullptr;
}

void Stack::push(Rectangle r) {
    Node *q = new Node;
    q->rectangle = r;
    if (isEmpty()) {
        q->next = nullptr;
    } else {
        q->next = top;
    }
    top = q;
}

Rectangle Stack::pop() {
    if (!isEmpty()) {
        Rectangle result = top->rectangle;
        Node *temp = top->next;
        delete top;
        top = temp;
        return result;
    }
    return Rectangle(0, 0);
}

bool Stack::isEmpty() {
    return top == nullptr;
}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

int Stack::topHeight() {
    return top->rectangle.height;
}


void Stack::increaseWidth(int i) {
    top->rectangle.width += i;
}

int maxSquare(Rectangle *arr, size_t size) {
    int max = arr[0].get_area();
    Stack stack;
    stack.push(arr[0]);

    for (int i = 1; i < size; i++) {
        if (arr[i].height >= stack.topHeight())
            stack.push(arr[i]);
        else {
            //идем по высоте
            int currentHeight = stack.topHeight();
            while (currentHeight > arr[i].height) {
                Rectangle last = stack.pop();
                int area = last.get_area();
                if (area > max)
                    max = area;

                // Пустой стек?
                if (stack.isEmpty()) {
                    currentHeight = arr[i].height;
                    stack.push(Rectangle(last.width + arr[i].width, currentHeight));
                } else {
                    stack.increaseWidth(last.width);
                    if (stack.topHeight() > arr[i].height)
                        currentHeight = stack.topHeight();
                    else if (stack.topHeight() == arr[i].height) {
                        stack.increaseWidth(arr[i].width);
                        currentHeight = arr[i].height;
                    } else {
                        currentHeight = arr[i].height;
                        stack.push(Rectangle(last.width + arr[i].width, currentHeight));
                    }
                }
            }
        }
    }
    int top_area = stack.pop().get_area();
    return max > top_area ? max : top_area;
}

int main() {
    size_t sz = 0;
    std::cin >> sz;
    Rectangle *arr_rect = new Rectangle[sz];
    for (size_t i = 0; i < sz; i++) {
        int width = 0;
        int height = 0;
        std::cin >> width;
        std::cin >> height;
        arr_rect[i] = Rectangle(width, height);
    }
    std::cout << maxSquare(arr_rect, sz);
    delete[] arr_rect;
    return 0;
}