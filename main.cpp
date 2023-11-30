#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <unordered_set>

void shuffle(std::list<int>& list)
{
    for (int i = static_cast<int>(list.size()) - 1; i > 0; --i) {
        const int j = std::rand() % (i + 1); // NOLINT(*-msc50-cpp)
        std::iter_swap(std::next(list.begin(), i), std::next(list.begin(), j));
    }
}

bool check_distinct(const std::list<int>& list)
{
    std::unordered_set<int> set;
    bool distinct = true;
    for (int n : list) {
        if (distinct && set.contains(n)) {
            distinct = false;
        }
        set.insert(n);
    }
    return distinct;
}

int main()
{
    std::srand(69); // NOLINT(*-msc51-cpp)

    std::list<int> list;
    std::map<int, double> times;
    for (int i = 0; i < 10000; ++i) {
        std::cout << "n = " << i << "\n";
        list.push_back(i);
        shuffle(list);

        auto start = std::chrono::high_resolution_clock::now();
        check_distinct(list);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        times.insert({ i, duration.count() });
    }

    {
        std::fstream out_file("times.csv", std::ios::out);
        out_file << "n,time\n";
        for (auto [n, time] : times) {
            out_file << n << "," << time << "\n";
        }
    }
}
