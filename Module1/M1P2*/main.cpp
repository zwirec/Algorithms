#include <iostream>
#include <assert.h>

size_t solve(const size_t *A, size_t sz) {
    size_t i = sz - 1;
    size_t j = sz - 1;
    i = A[i];
    j = A[A[j]];
    while (i != j) {
        i = A[i];
        j = A[A[j]];
    }
    i = A[i];
    j = A[sz - 1];
    while (i != j) {
        i = A[i];
        j = A[j];
    }
    return i;
}

int main() {
    size_t sz = 0;
    std::cin >> sz;
    assert(sz > 0);
    size_t *A = nullptr;

    try {
        A = new size_t[sz];
    }
    catch (std::bad_alloc &e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    for (size_t i = 0; i < sz; ++i) {
        std::cin >> A[i];
    }
    size_t i = solve(A, sz);
    std::cout << i << std::endl;
    delete[] A;
    return 0;
}