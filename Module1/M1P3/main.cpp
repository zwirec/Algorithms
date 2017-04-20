/*​Дан массив целых чисел А[0..n­1]. Известно, что на интервале [0, m] значения массива строго
возрастают, а на интервале [m, n­1] строго убывают. Найти m за O(log m).
2 ≤ n ≤ 10000.*/

#include <iostream>

size_t search(int *A, size_t l, size_t r) {
    if (r - l == 0) {
        return r;
    }
    if (A[(r + l) / 2] < A[(r + l) / 2 + 1]) {
        return search(A, (r + l) / 2 + 1, r);
    } else {
        return search(A, l, (r + l) / 2);
    }
}


size_t find_number(int *A, size_t sz) {
    if (A[0] > A[1]) {
        return 0;
    }
    size_t left = 1;
    size_t right = 2;
    while (left <= sz) {
        if (right > sz)
            right = sz;
        if (A[right] < A[right - 1] && A[right] > A[right+1]) {
            return search(A, left, right);
        } else {
            left <<= 1;
            right <<= 1;
        }
    }
    return sz;
}

int main() {
    size_t sz = 0;
    std::cin >> sz;
    int *A = new int[sz];
    for (size_t i = 0; i < sz; ++i) {
        std::cin >> A[i];
    }
    std::cout << find_number(A, sz - 1);
    delete[] A;
    return 0;
}