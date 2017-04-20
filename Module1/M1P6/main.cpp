/*Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков
пирамиду.Каждый вышележащий слой пирамиды должен быть строго меньше
нижележащего.*/

#include <iostream>

long long* stairs_6_1(long n, long long *stairs) {
    stairs[0] = 1;
    stairs[1] = 1;
    for (long i = 2; i <= n; ++i) {
        int k = 1;
        int pentagon_num_1 = ((3 * k * k - k) / 2);
        int pentagon_num_2 = ((3 * k * k + k) / 2);
        while (i >= pentagon_num_1) {
            if ((k + 1) % 2 == 0) {
                stairs[i] += (stairs[i - pentagon_num_1]);
                if (i >= pentagon_num_2) {
                    stairs[i] += stairs[i - pentagon_num_2];
                }
            } else {
                stairs[i] += -(stairs[i - pentagon_num_1]);
                if (i >= pentagon_num_2) {
                    stairs[i] += -stairs[i - pentagon_num_2];
                }
            }
            k++;
            pentagon_num_1 = ((3 * k * k - k) / 2);
            pentagon_num_2 = ((3 * k * k + k) / 2);
        }

    }
    return stairs;
}

long long stairs_6_2(long n, long long *stairs) {
    stairs_6_1(n, stairs);
    long long result = stairs[n];
    long long pentagon1 = 1 * (3 * 1 - 1) / 2;
    long long pentagon2 = -1 * (3 * (-1) - 1) / 2;
    long i = 1;
    while (n >= 2 * pentagon1) {
        if (i % 2 == 0) {
            result += stairs[n - 2 * pentagon1];
        } else {
            result -= stairs[n - 2 * pentagon1];
        }
        if (n >= 2 * pentagon2) {
            if (i % 2 == 0) {
                result += stairs[n - 2 * pentagon2];
            } else {
                result -= stairs[n - 2 * pentagon2];
            }
        }
        i++;
        pentagon1 = i * (3 * i - 1) / 2;
        pentagon2 = -i * (3 * (-i) - 1) / 2;
    }
    return result;
}

long long arr[300][300];

size_t pyramids(long n) {
    size_t res = 0;
    for (long i = 1; i < n; i++) {
        arr[n - i][i] = 1;
    }
    for (long i = n - 1; i >= 1; i--) {
        for (long j = 1; j <= n - i; j++) {
            for (long q = j + 1; q <= i; q++) {
                arr[i - q][q] += arr[i][j];
            };
        };
    }

    for (long i = 1; i <= n; i++) {
        res += arr[0][i];
    }
    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return res + 1;
}

int main() {
    long n = 0;
    std::cin >> n;
    long long *stairs = new long long[n+1];
    std::cout << pyramids(n);
    delete[] stairs;
    return 0;
}