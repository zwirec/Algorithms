#include <iostream>
#include <vector>


struct Train {
    size_t arrival_time;
    size_t departure_time;

    bool operator<(const Train &rhs) const;

    bool operator==(const Train &rhs) const;

};

bool Train::operator==(const Train &rhs) const {
    return this->departure_time == rhs.departure_time;
}

bool Train::operator<(const Train &rhs) const {
    return this->departure_time < rhs.departure_time;
}


template<class T, class Compare = std::less <T>>
class Heap {
private:
    std::vector <T> heap_array;
    size_t size;
    Compare compare;

    void siftDown(size_t i);

    void siftUp(size_t i);

public:
    T extract();

    void insert(T val);

    T get_min();

    size_t get_size();

    Heap(Compare compare);

    Heap();
};

template<class T, class Compare>
void Heap<T, Compare>::siftDown(size_t i) {
    while (2 * i + 1 < size) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t j = left;
        if (right < size && compare(heap_array[right], heap_array[left])) {
            j = right;
        }
        std::swap(heap_array[i], heap_array[j]);
        i = j;
    }
}

template<class T, class Compare>
void Heap<T, Compare>::siftUp(size_t i) {
    if (size == 0) {
        return;
    } else {
        while (i > 0 && compare(heap_array[i], heap_array[(i - 1) / 2])) {
            std::swap(heap_array[i], heap_array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
}

template<class T, class Compare>
Heap<T, Compare>::Heap(Compare cmp) : size(1), heap_array(1), compare(cmp) {
    std::cout << "EX" << std::endl;
}

template<class T, class Compare>
T Heap<T, Compare>::extract() {
    T min = heap_array[0];
    heap_array[0] = heap_array[size - 1];
    --size;
    heap_array.resize(size);
    siftDown(0);
    return min;
}

template<class T, class Compare>
void Heap<T, Compare>::insert(T val) {
    ++size;
    heap_array.resize(size);
    heap_array[size - 1] = val;
    siftUp(size - 1);
}

template<class T, class Compare>
T Heap<T, Compare>::get_min() {
    return heap_array[0];
}

template<class T, class Compare>
size_t Heap<T, Compare>::get_size() {
    return size;
}

template<class T, class Compare>
Heap<T, Compare>::Heap():size(1), heap_array(1) {
    std::cout << &this->compare << std::endl;
}


bool compareTrain(const Train &lhs, const Train &rhs) {
    return lhs.departure_time < rhs.departure_time;
}

typedef bool(*cmpTrain)(const Train &, const Train &);

int main() {
    size_t sz = 0;
    std::cin >> sz;
    Heap<Train> heap_train;
    for (size_t j = 0; j < sz; ++j) {
        Train train;
        std::cin >> train.arrival_time >> train.departure_time;
        if (train.arrival_time > heap_train.get_min().departure_time) {
            heap_train.extract();
            heap_train.insert(train);
        } else {
            heap_train.insert(train);
        }
    }
    std::cout << heap_train.get_size() << std::endl;

    return 0;
}