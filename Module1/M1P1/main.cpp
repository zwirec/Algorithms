/*​Вывести разложение натурального числа n на простые множители. Простые множители должны быть
упорядочены по возрастанию и разделены пробелами. 2 ≤ n ≤ 10^6*/

#include <iostream>
#include <cmath>


int *get_prime_divider(int n) {
    int *result = new int[int(sqrt(n))];
    int d = 2;
    size_t count = 0;
    while (d * d <= n) {
        if (n % d == 0) {
            result[count++] = d;
            n /= d;
        } else
            ++d;
    };
    if (n > 1) {
        result[count] = n;
    }
    return result;
}

int main() {
    size_t i = 0;
    int n = 0;
    std::cin >> n;
    int *res = get_prime_divider(n);
    while (res[i]) {
        std::cout << res[i++] << ' ';
    }
    delete[] res;
    return 0;
}