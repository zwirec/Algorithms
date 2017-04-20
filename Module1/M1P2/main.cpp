/*​Даны два массива целых чисел одинаковой длины A[0..n­1] и B[0..n­1]. Необходимо найти первую пару
индексов i0 и j0, i0 ≤ j0, такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
Время работы ­ O(n).
n ≤ 100000.*/

#include <iostream>

struct two_index {
    int i;
    int j;
};

struct two_index solveProblem2(const int *A, const int *B, int sz) {
    two_index result1 = {0, 0};
    two_index result2 = {0, 0};

    int maxB1 = B[sz - 1];
    result1.j = sz - 1;
    for (int j = sz - 2; j >= 0; --j) {
        if (maxB1 < B[j]) {
            maxB1 = B[j];
            result1.j = j;
        }
    }

    int maxA1 = A[0];
    result1.i = 0;
    for (int i = 1; i <= result1.j; ++i) {
        if (maxA1 < A[i]) {
            maxA1 = A[i];
            result1.i = i;
        }
    }

    for (int j = result1.j - 1; j >= result1.i; --j) {
        if (maxB1 == B[j]) {
            result1.j = j;
        }
    }

    int maxA2 = A[sz - 1];
    result2.i = sz - 1;
    for (int i = sz - 2; i >= 0; --i) {
        if (maxA2 <= A[i]) {
            maxA2 = A[i];
            result2.i = i;
        }
    }

    int maxB2 = B[sz - 1];
    result2.j = sz - 1;
    for (int j = sz - 2; j >= result2.i; --j) {
        if (maxB2 <= B[j]) {
            maxB2 = B[j];
            result2.j = j;
        }
    }

    if (maxA1 + maxB1 > maxA2 + maxB2) {
        return result1;
    } else if (maxA1 + maxB1 < maxA2 + maxB2) {
        return result2;
    } else {
        if (result1.i > result2.i)
            return result2;
        else if (result1.i < result2.i)
            return result1;
        else
            return result1.j < result2.j ? result1 : result2;
    }

}

struct two_index solve2(int *A, int *B, int sz) {
    two_index result = {0, 0};
    int a = A[0];
    int b = B[0];
    int sum = a + b;
    int aTemp = 0;
    int sumTemp = 0;
    bool key = true;
    for (int i = 1; i < sz; ++i) {
        if (A[i] > a) {
            aTemp = A[i];
            key = true;
        } else {
            aTemp = a;
            key = false;
        }
        sumTemp = aTemp + B[i];

        if (sumTemp > sum) {
            b = B[i];
            sum = sumTemp;
            result.j = i;
            if (key) {
                a = A[i];
                result.i = i;
            }
        }
    }
    return result;
}

int main() {
    int sz = 0;

    std::cin >> sz;
    int *A = new int[sz];
    int *B = new int[sz];

    for (int i = 0; i < sz; ++i) {
        std::cin >> A[i];
    }

    for (int i = 0; i < sz; ++i) {
        std::cin >> B[i];
    }

    two_index res = solve2(A, B, sz);
    std::cout << res.i << ' ' << res.j;
    delete[] A;
    delete[] B;
    return 0;
}