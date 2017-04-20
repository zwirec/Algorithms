#include <iostream>
#include <vector>

struct Date {
    int day;
    int month;
    int year;
    int step;

    Date(int d, int m, int y, int s);

    Date operator-(const Date &rhs);

    bool operator<(const Date &rhs) const;

    bool operator>(const Date &rhs) const;

    bool operator==(const Date &rhs) const;

    bool operator<=(const Date &rhs) const;

    bool operator>=(const Date &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
};

Date Date::operator-(const Date &rhs) {
    Date date(day, month, year, step);
    date.year -= rhs.year;
    if (date.month < rhs.month) {
        date.year--;
        date.month = 12 + date.month - rhs.month;
    } else {
        date.month -= rhs.month;
    }
    if (date.day < rhs.day) {
        if (date.month == 0) {
            date.year--;
            date.month += 12;
        }
        date.month--;
        date.day = 31 + date.day - rhs.day;
    } else {
        date.day -= rhs.day;
    }
    return date;
}

Date::Date(int d, int m, int y, int s) : day(d), month(m), year(y), step(s) {

}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << date.day << ' ' << date.month << ' ' << date.year;
    return os;
}

bool Date::operator<(const Date &rhs) const {
    if (this->year < rhs.year) {
        return true;
    } else if (this->year > rhs.year) {
        return false;
    } else {
        if (this->month < rhs.month) {
            return true;
        } else if (this->month > rhs.month) {
            return false;
        } else {
            if (this->day < rhs.day) {
                return true;
            } else if (this->day > rhs.day) {
                return false;
            }
        }
    }
    return false;
}

bool Date::operator>(const Date &rhs) const {
    return rhs < *this;
}

bool Date::operator==(const Date &rhs) const {
    return (this->year == rhs.year && this->month == rhs.month && this->day == rhs.day);
}

bool Date::operator<=(const Date &rhs) const {
    return *this < rhs || *this == rhs;
}

bool Date::operator>=(const Date &rhs) const {
    return *this > rhs || *this == rhs;
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

int main() {
    size_t sz = 0;
    std::cin >> sz;
    std::vector <Date> humans_date;

    for (size_t i = 0; i < sz; i++) {
        Date born_date = {0, 0, 0, 0};
        Date death_date = {0, 0, 0, 0};
        std::cin >> born_date.day >> born_date.month >> born_date.year;
        std::cin >> death_date.day >> death_date.month >> death_date.year;
        if (born_date.year + 18 == death_date.year
            && death_date.day == born_date.day
            && death_date.month == born_date.month
            || (born_date.year + 18 > death_date.year)
            || (born_date.year + 18 == death_date.year
                && (born_date.month * 31 + born_date.day) < (death_date.month * 31 + death_date.month))) {
            continue;
        }
        if (born_date.year + 80 == death_date.year
            && (death_date.month * 31 + death_date.day > born_date.month * 31 + born_date.day)
            || (born_date.year + 80 < death_date.year)) {
            death_date = born_date;
            death_date.year = born_date.year + 80;
        }
        born_date.year += 18;
        born_date.step = 1;
        death_date.step = -1;
        humans_date.push_back(born_date);
        humans_date.push_back(death_date);
    }
    HeapSort(&humans_date[0], humans_date.size());
    size_t max = 0;
    size_t curr_max = 0;

    for (auto &x: humans_date) {
        curr_max += x.step;
        if (curr_max > max) {
            max = curr_max;
        }
    }
    std::cout << max << std::endl;
    return 0;
}
