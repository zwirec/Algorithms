
#include <iostream>
#include <cassert>

struct arr_with_sz {
    size_t *arr;
    size_t sz;

    arr_with_sz(size_t n);
    ~arr_with_sz();
};

arr_with_sz::arr_with_sz(size_t n):sz(0) {
    arr = new size_t[n+1];
}

arr_with_sz::~arr_with_sz() {
    delete[] arr;
}

arr_with_sz prime_dividers(size_t N) {
    assert(N > 0);
    arr_with_sz pr(N);                             //массив простых чисел
    size_t count = 0;

    size_t *lp = new size_t[N + 1];             //показатель простоты числа
    for (size_t i = 2; i <= N; ++i) {
        if (lp[i] == 0) {                       //если 0 значит простое
            lp[i] = i;
            pr.arr[pr.sz++] = i;
        }
        size_t k = 0;
        while (k < pr.sz && pr.arr[k] <= lp[i] && lp[i] != 0 && pr.arr[k] * i <= N) {
            lp[pr.arr[k] * i] = pr.arr[k];
            k++;
        }
    }
    return pr;
}


int main() {
    size_t N = 0;
    std::cin >> N;
    arr_with_sz res = prime_dividers(N);
    for (size_t i = 0; i < res.sz; i++) {
        std::cout << res.arr[i] << std::endl;
    }
    std::cout << std::endl;
    return 0;
}