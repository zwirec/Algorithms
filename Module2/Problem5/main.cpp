#include <iostream>
#include <vector>

#define MAXSTACK 4096

template<class T, class Compare=std::less <T>>
int med(T *arr, int a, int b, int c, Compare cmp = std::less<int>()) {
    if (!cmp(arr[a], arr[b])) {
        if (cmp(arr[a], arr[c]))
            return a;
        return (!cmp(arr[b], arr[c])) ? b : c;
    }
    if (!cmp(arr[c], arr[b]))
        return b;
    return (!cmp(arr[a], arr[c])) ? a : c;
}

struct Bounds {
    int low_b;
    int up_b;
};

template<class T>
void qSort(T *a, int size) {

    int i, j;
    int left, right;

//    int ubstack[MAXSTACK];
//    int lbstack[MAXSTACK];

    int stackpos = 1;
    int ppos;
    T pivot;
    T temp;


    Bounds stack[MAXSTACK];
    stack[1] = {0, size - 1};

    do {

        left = stack[stackpos].low_b;
        right = stack[stackpos--].up_b;
//        if( right - left < 100 ) {
//            InsertionSort(a[left], right - left +1);
//        }

        do {

            ppos = med(a, left, (right + left) / 2, right);

            i = left;
            j = right;
            pivot = a[ppos];

            do {
                while (a[i] < pivot) i++;
                while (pivot < a[j]) j--;
                if (i <= j) {
                    std::swap(a[i], a[j]);
                    i++;
                    j--;
                }
            } while (i <= j);

            if (i < ppos) {
                if (i < right) {
                    stack[++stackpos].low_b = i;
                    stack[stackpos].up_b = right;

                }
                right = j;

            } else {
                if (j > left) {
                    stack[++stackpos].low_b = left;
                    stack[stackpos].up_b = j;

                }
                left = i;
            }
        } while (left < right);

    } while (stackpos != 0);
}

template<class InputIt>
void Merge(InputIt leftArrayBegin, InputIt leftArrayEnd,
           InputIt rightArrayBegin, InputIt rightArrayEnd, InputIt result) {
    while (true) {
        if (leftArrayBegin == leftArrayEnd) {
            std::copy(rightArrayBegin, rightArrayEnd, result);
            return;
        }
        if (rightArrayBegin == rightArrayEnd) {
            std::copy(leftArrayBegin, leftArrayEnd, result);
            return;
        }
        *result++ = (*rightArrayBegin < *leftArrayBegin)
                    ? *rightArrayBegin++ : *leftArrayBegin++;
    }
}


int main() {
    size_t sz = 0, k = 0;
    std::cin >> sz >> k;
    int x = 0;
    int i = 0;
    std::vector<int> reserve;
    std::vector<int> buffer;
//    typedef std::chrono::high_resolution_clock Time;
//    typedef std::chrono::milliseconds ms;
    while ((buffer.size() != k) && i < sz) {
        std::cin >> x;
        buffer.push_back(x);
        i++;
    }
    qSort(buffer.data(), buffer.size());
//    std::sort(buffer.begin(), buffer.begin()+k);
    while (true) {
        while (buffer.size() != 2 * k && i < sz) {
            std::cin >> x;
            buffer.push_back(x);
            i++;
        }
        reserve.resize(buffer.size());
//        auto t0 = Time::now();
//        std::sort(buffer.begin()+k, buffer.end());
//        qSort(&buffer[0], k+1);
        qSort(&buffer[k], buffer.size() - k);
        Merge(buffer.begin(), buffer.begin() + k, buffer.begin() + k, buffer.end(), reserve.begin());

        if (i == sz) {
            for (auto x:reserve) {
                std::cout << x << " ";
            }
            break;
        } else {
            for (auto j = 0; j < k; j++) {
                std::cout << reserve[j] << " ";
            }
        }

        buffer.assign(reserve.begin() + k, reserve.end());
        reserve.clear();
    }

    std::cout << std::endl;
    return 0;
}