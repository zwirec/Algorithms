#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using std::string;

void countSort(string *a, size_t size, std::vector<int> &count, size_t k) {


    for (int i = 0; i < 256; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        ++count[a[i][k]];
    }

    int sum = 0;

    for (int i = 0; i < 256; i++) {
        int tmp = count[i];
        count[i] = sum;
        sum += tmp;
    }

    std::vector <string> b(size);

    for (int i = 0; i < size; i++) {
        b[count[a[i][k]]] = a[i];
        ++count[a[i][k]];
    }

    std::move(b.begin(), b.end(), a);

}


void radixSort(string *b, int size, int d) {
    std::vector<int> count(257);
    count[256] = size;
    countSort(b, size, count, d);
    for (auto i = 0; i < 256; i++) {
        if ((count[i + 1] - count[i]) > 1) {
            radixSort(&b[count[i]], count[i + 1] - count[i], d + 1);
        }
    }
}

int main(void) {
    std::vector <std::string> data;
    std::string s;
    while (std::cin >> s) {
        data.push_back(s);
    };
//    auto t0 = Time::now();
    radixSort(&data[0], data.size(), 0);
//    auto t1 = Time::now();
    //std::cout << std::is_sorted(data.begin(), data.end()) << std::endl;
    for (auto &x:data) {
        std::cout << x << std::endl;
    }
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;
    return 0;
}