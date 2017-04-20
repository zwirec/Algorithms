/*Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся незамкнутую

ломаную, проходящую через все эти точки.

Указание: стройте ломаную в порядке возрастания x-координаты. Если имеются две точки с

одинаковой x-координатой, то расположите раньше ту точку, у которой y-координата меньше.*/

#include <iostream>
#include <vector>

struct Point {
    int x;
    int y;

    friend std::istream &operator>>(std::istream &os, Point &p);

    friend std::ostream &operator<<(std::ostream &os, Point &p);

    bool operator>(const Point &rhs) const;

    bool operator<(const Point &rhs) const;
};

std::istream &operator>>(std::istream &os, Point &p) {
    os >> p.x >> p.y;
    return os;
}

bool Point::operator>(const Point &rhs) const {
    if (this->x > rhs.x) {
        return true;
    } else if (this->x < rhs.x) {
        return false;
    } else {
        return this->y > rhs.y;
    }
}

bool Point::operator<(const Point &rhs) const {
    return rhs > *this;
}

std::ostream &operator<<(std::ostream &os, Point &p) {
    os << p.x << " " << p.y;
    return os;
}


template<typename RandomIt>
void InsertionSort(RandomIt begin, RandomIt end) {
    for (RandomIt i = begin + 1; i != end; i++) {
        typename RandomIt::value_type key = *i;
        RandomIt j = i - 1;
        while (j >= begin && *j > key) {
            *(j + 1) = *j;
            j = j - 1;
        }
        *(j + 1) = key;
    }
}

template<typename RandomIt, typename Compare>
void InsertionSort(RandomIt begin, RandomIt end, Compare compare) {
    for (RandomIt i = begin + 1; i != end; i++) {
        typename RandomIt::value_type key = *i;
        RandomIt j = i - 1;
        while (j >= begin && compare(*j, key)) {
            *(j + 1) = *j;
            j = j - 1;
        }
        *(j + 1) = key;
    }
}

bool comparePoint(const Point &lhs, const Point &rhs) {
    if (lhs.x > rhs.x) {
        return true;
    } else if (lhs.x < rhs.x) {
        return false;
    } else {
        return lhs.y > rhs.y;
    }
}

int main() {
    std::vector <Point> vector;
    size_t sz = 0;
    std::cin >> sz;

    vector.reserve(sz);
    for (size_t i = 0; i < sz; i++) {
        Point tmp = {0, 0};
        std::cin >> tmp;
        vector.push_back(tmp);
    }
    InsertionSort(vector.begin(), vector.end(), comparePoint);

    for (auto &x:vector) {
        std::cout << x << std::endl;
    }
    return 0;
}

