#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <algorithm>

class Sum {
private:
    int threadId;
    int total = 0;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    Sum(int threadId)
        : threadId(threadId), gen(std::random_device{}()), dist(1, 1000) {}


    void computeSum() {
        for (int i = 0; i < 100; i++) {
            total += dist(gen);
        }
    }

    int getThreadId() const { return threadId; }
    int getTotal() const { return total; }
};

int main() {
    std::vector<Sum> sums;
    for (int i = 0; i < 10; i++) {
        sums.emplace_back(i);
    }

    std::vector<std::thread> threads;
    threads.reserve(sums.size());
    for (int i = 0; i < 10; i++) {
        threads.emplace_back(&Sum::computeSum, &sums[i]);
    }

    for (auto& t : threads) t.join();

    for (const auto& s : sums)
        std::cout << "Thread " << s.getThreadId() << ": " << s.getTotal() << std::endl;


    std::sort(sums.begin(), sums.end(),
        [](const Sum& a, const Sum& b) { return a.getTotal() > b.getTotal(); });

    std::cout << "Max value is " << sums[0].getTotal()
              << " Thread " << sums[0].getThreadId() << std::endl;

    return 0;
}
