#include <iostream>
#include <thread>
#include <random>
#include <vector>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1, 1000);

class Sum {
private:
    int threadId;
    int total = 0;

public:
    Sum(int threadId) : threadId(threadId) {}

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

    int idx = 0;

    for (int i = 1; i < sums.size(); ++i) {
        if (sums[i].getTotal() > sums[idx].getTotal())
            idx = i;
    }

    std::cout << "Max value is " << sums[idx].getTotal()
              << " Thread " << sums[idx].getThreadId() << std::endl;

    return 0;
}
