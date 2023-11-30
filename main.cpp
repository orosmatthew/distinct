#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <unordered_set>

void shuffle(std::vector<int>& arr)
{
    for (int i = static_cast<int>(arr.size()) - 1; i > 0; --i) {
        const int j = std::rand() % (i + 1); // NOLINT(*-msc50-cpp)
        std::swap(arr[i], arr[j]);
    }
}

bool check_distinct(const std::vector<int>& list)
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

    std::vector<int> arr;
    std::map<int, double> times;
    for (int i = 0; i < 100000; ++i) {
        std::cout << "n = " << i << "\n";
        arr.push_back(i);
        shuffle(arr);

        auto start = std::chrono::high_resolution_clock::now();
        check_distinct(arr);
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
