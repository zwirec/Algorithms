#include <iostream>
#include <vector>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;

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

template<class T, class Compare>
void siftDown(T *v, size_t i, size_t size, Compare cmp) {
    while (2 * i + 1 < size) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t j = left;
        if (right < size && v[right] > v[left]) {
            j = right;
        }
        if (v[i] >= v[j]) {
            break;
        }
        std::swap(v[i], v[j]);
        i = j;
    }
}

template<typename T, typename Compare=std::less <T>>
void HeapSort(T *v, int size, Compare cmp = std::less<T>()) {
    for (int i = size / 2; i >= 0; i--) {
        siftDown(v, i, size, cmp);
    }
    for (int i = size - 1; i > 0; i--) {
        std::swap(v[0], v[i]);
        siftDown(v, 0, i, cmp);
    }
}

inline void writeInt(int n, FILE *f) {
    int N = n, rev, count = 0;
    rev = N;
    if (N == 0) {
        putc_unlocked('0', f);
        putc_unlocked('\n', f);
        return;
    }
    while ((rev % 10) == 0) {
        count++;
        rev /= 10;
    } //obtain the count of the number of 0s
    rev = 0;
    while (N != 0) {
        rev = (rev << 3) + (rev << 1) + N % 10;
        N /= 10;
    }  //store reverse of N in rev
    while (rev != 0) {
        putc_unlocked(rev % 10 + '0', f);
        rev /= 10;
    }
    while (count--) putc_unlocked('0', f);
    //putc_unlocked('\n', f);
}

void displayInt(int n, FILE *f) {
    if (n < 0) {
        putc_unlocked('-', f);
        n = -n;
    }
    writeInt(n, f);
    putc_unlocked('\n', f);
}
//int randint(int l, int u) {
//    srand(time(NULL));
//    return l + rand() % (u - l + 1);
//}

template<typename T>
void InsertionSort(T *arr, int size) {
    for (auto i = 0; i < size; i++) {
        T key = arr[i];
        auto j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//const int cutoff = 30;

template<class T>
void QSort4(T *x, int l, int u) {
    if (l >= u)
        return;

    if (u - l > 31) {
        std::swap(x[l], x[med(&x[0], l, (u + l) / 2, u)]);
        T t;
        int i, j;

        t = x[l];
        i = l;
        j = u + 1;

        while (1) {
            do
                i++;
            while (i <= u && x[i] < t);

            do
                j--;
            while (x[j] > t);

            if (i > j)
                break;
            std::swap(x[i], x[j]);
        }

        std::swap(x[l], x[j]);


        QSort4(x, l, j - 1);
        QSort4(x, j + 1, u);
    }

}


template<class T>
void QSort3(T *x, int l, int u) {
    if (l >= u)
        return;

    if (u - l > 25) {


        T t, tmp;
        int i, j;
        t = x[l];
        i = l;
        j = u + 1;

        while (1) {
            /* пропуск элементов справа и слева,
               чтобы не делать лишней работы */
            do i++; while (i <= u && x[i] < t);
            do j--; while (x[j] > t);

            if (i > j)
                break;
            // Делаем swap(i, j):
            std::swap(x[i], x[j]);
        }

        // swap(l, j)
        std::swap(x[i], x[j]);

        QSort3(x, l, j - 1);
        QSort3(x, j + 1, u);
    }
}


struct Bounds {
    int low_b;
    int up_b;
};

#define MAXSTACK 1024

template<class T>
inline void qSort(T a[], int size, int cutoff) {

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
        if (right - left > cutoff) {

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
        }


    } while (stackpos != 0);
    InsertionSort(&a[0], size);
}


bool read_int_unlocked(int &out) {
    int c = getchar_unlocked();
    int x = 0;
    int neg = 0;

    for (; !('0' <= c && c <= '9') && c != '-'; c = getchar_unlocked()) {
        if (c == EOF)
            return false;
    }
    if (c == '-') {
        neg = 1;
        c = getchar_unlocked();
    }
    if (c == EOF)
        return false;
    for (; '0' <= c && c <= '9'; c = getchar_unlocked()) {
        x = x * 10 + c - '0';
    }
    out = neg ? -x : x;
    return true;
}


void countSort(int *a, size_t size) {
    std::vector<int> vector(INT32_MAX);
    for (auto i = 0; i < size; i++) {
        vector[a[i]] += 1;
    }
    int k = 0;
    for (auto &x:vector) {
        for (auto i = 0; i < x; i++) {
            a[k++] = x;
        }
    }
}

int main(int argc, char **argv) {
    std::vector<int> vector1;
//    int *vector1 = (int*)malloc(25000000*4);
    int x1 = 0;
    int k = 0;
    while (read_int_unlocked(x1))
        vector1.push_back(x1);
    auto t0 = Time::now();
    qSort(vector1.data(), vector1.size(), 25);
//    QSort4(vector1.data(), 0, vector1.size());
//    InsertionSort(vector1.data(), vector1.size());
//    QSort3(vector1.data(), 0, vector1.size());
//    InsertionSort(vector1.data(), vector1.size());
    auto t1 = Time::now();
//    for (auto i = 9; i < k; i += 10) {
//        displayInt(vector1[i], stdout);
//    }

    std::cout << std::is_sorted(vector1.begin(), vector1.end()) << std::endl;

    ms d = std::chrono::duration_cast<ms>(t1 - t0);
    std::cout << d.count() << "ms\n";
//    fclose(stdin);
    return 0;
}