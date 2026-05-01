#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include <atomic>

using namespace std;
using namespace chrono_literals;

class Philosopher {
private:
    int id;
    mutex& first_fork;   // Could be left or right depending on philosopher
    mutex& second_fork;
    mt19937 rng;
    atomic<bool>& running;

public:
    Philosopher(int id, mutex& first, mutex& second, atomic<bool>& run)
        : id(id), first_fork(first), second_fork(second), rng(random_device{}()), running(run) {}

    void dine() {
        while (running.load()) {
            think();
            eat();
        }
        cout << "Philosopher " << id << " is done dining.\n";
    }

private:
    void think() {
        cout << "Philosopher " << id << " is thinking.\n";
        uniform_int_distribution<> dist(100, 500);
        this_thread::sleep_for(chrono::milliseconds(dist(rng)));
    }

    void eat() {
        // Pick up forks in a fixed order (prevents circular wait)
        cout << "Philosopher " << id << " is hungry. Picking up first fork.\n";
        first_fork.lock();
        
        cout << "Philosopher " << id << " picked up first fork. Picking up second fork.\n";
        second_fork.lock();
        
        cout << "Philosopher " << id << " is EATING (with both forks).\n";
        uniform_int_distribution<> dist(200, 800);
        this_thread::sleep_for(chrono::milliseconds(dist(rng)));
        
        second_fork.unlock();
        first_fork.unlock();
        cout << "Philosopher " << id << " finished eating. Put down forks.\n";
    }
};

int main() {
    const int N = 5;
    vector<mutex> forks(N);
    vector<thread> philosophers;
    atomic<bool> running(true);
    
    cout << "=== CORRECT VERSION (No Deadlock) ===\n";
    cout << "Solution: Last philosopher picks up right fork first.\n";
    cout << "This breaks the circular wait condition.\n\n";
    cout << "Running for 10 seconds...\n\n";
    
    for (int i = 0; i < N; ++i) {
        // Asymmetric: Last philosopher reverses fork order
        if (i == N - 1) {
            // Last philosopher picks up right fork first, then left
            philosophers.emplace_back([i, &forks, &running]() {
                Philosopher p(i, forks[(i+1) % N], forks[i], running);
                p.dine();
            });
        } else {
            // Others pick up left fork first, then right
            philosophers.emplace_back([i, &forks, &running]() {
                Philosopher p(i, forks[i], forks[(i+1) % N], running);
                p.dine();
            });
        }
    }
    
    // Let it run for 10 seconds
    this_thread::sleep_for(10s);
    running.store(false);
    
    // Wait for all philosophers to finish
    for (auto& t : philosophers) {
        if (t.joinable()) t.join();
    }
    
    cout << "\n=== Program ended successfully! No deadlock occurred. ===\n";
    
    return 0;
}