#include <iostream>
#include <vector>

template<class T, class Compare>
int med(T *arr, int a, int b, int c, Compare cmp) {
    if (!cmp(arr[a], arr[b])) {
        if (cmp(arr[a], arr[c]))
            return a;
        return (!cmp(arr[b], arr[c])) ? b : c;
    }
    if (!cmp(arr[c], arr[b]))
        return b;
    return (!cmp(arr[a], arr[c])) ? a : c;
}

template<class T, class Compare>
int Partition(T *arr, int left, int right, Compare cmp) {
    int pivot_ind = med(arr, left, (right + left) / 2, right, cmp);
    std::swap(arr[pivot_ind], arr[right]);
    T pivot = arr[right];
    int i = left - 1;
    for (auto j = left; j < right; j++) {
        if (cmp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[right]);
    return i + 1;
}

template<class T, class Compare>
T KStat(T *arr, int size, int k, Compare cmp) {
    int left = 0;
    while (true) {
        int q = Partition(arr, left, size, cmp);
        if (q - left == k) {
            return arr[q];
        } else if (q - left + 1 > k) {
            size = q - 1;
        } else {
            k = k - (q - left + 1);
            left = q + 1;
        }
    }
};


int main() {
    size_t sz = 0;
    size_t k = 0;
    std::cin >> sz;
    std::cin >> k;
    std::vector<int> vector;
    for (int i = 0; i < sz; i++) {
        int tmp = 0;
        std::cin >> tmp;
        vector.push_back(tmp);
    }
    std::cout << KStat(&vector[0], vector.size() - 1, k, std::less<int>());

    return 0;
}