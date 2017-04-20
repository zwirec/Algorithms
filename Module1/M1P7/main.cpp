/*В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N — выстроить из своих тел
башню максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на
плечах, третий стоит на плечах у второго и т.д.
Каждый атлет характеризуется силой s(kg) и массой m(kg).
Сила — это максимальная масса, которую атлет способен держать у себя на плечах.
К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической
подготовкой, и у них не было времени на изучение языков программирования. Помогите им, напишите
программу, которая определит максимальную высоту башни, которую они могут составить.
Известно, что если атлет тяжелее, то он и сильнее:
если mi>mj, то si>sj.Атлеты равной массы могут иметь различную силу.*/

#include <iostream>

struct athlet {
    unsigned int mass;
    unsigned int power;
};



athlet find_next_athlet(athlet *athletes, unsigned int current_weight, size_t sz) {
    athlet min_athlet = {2000000, 2000000};
    bool find = false;
    size_t i_next = 0;
    for (size_t i = 0; i < sz; ++i) {
        if (athletes[i].power >= current_weight &&
            athletes[i].mass < min_athlet.mass &&
            athletes[i].power < min_athlet.power) {
            min_athlet = athletes[i];
            i_next = i;
            find = true;
        }
    }
    if (find) {
        athletes[i_next] = {0, 0};
    }
    return find ? min_athlet : athlet{0, 0};
}

int solve(athlet *athletes, size_t sz) {
    unsigned int current_weight = 0;
    int res = 0;
    while (true) {
        athlet next = find_next_athlet(athletes, current_weight, sz);
        if (next.mass != 0 && next.power != 0) {
            current_weight += next.mass;
            ++res;
        } else {
            break;
        };
    }
    return res;
}

int main() {
    athlet *athletes = new athlet[100000];
    size_t sz = 0;
    while (std::cin >> athletes[sz].mass) {
        std::cin >> athletes[sz].power;
        sz++;
    }
    std::cout << solve(athletes, sz);
    delete [] athletes;
    return 0;
}