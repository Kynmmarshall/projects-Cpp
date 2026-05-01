#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono_literals;

class Philosopher {
private:
    int id;
    mutex& left_fork;
    mutex& right_fork;
    mt19937 rng;

public:
    Philosopher(int id, mutex& left, mutex& right) 
        : id(id), left_fork(left), right_fork(right), rng(random_device{}()) {}

    void dine() {
        while (true) {
            think();
            eat();
        }
    }

private:
    void think() {
        cout << "Philosopher " << id << " is thinking.\n";
        uniform_int_distribution<> dist(100, 500);
        this_thread::sleep_for(chrono::milliseconds(dist(rng)));
    }

    void eat() {
        // DEADLOCK PRONE: Both pick up left fork first
        cout << "Philosopher " << id << " is hungry. Picking up left fork.\n";
        left_fork.lock();
        
        cout << "Philosopher " << id << " picked up left fork. Picking up right fork.\n";
        right_fork.lock();
        
        cout << "Philosopher " << id << " is EATING (with both forks).\n";
        uniform_int_distribution<> dist(200, 800);
        this_thread::sleep_for(chrono::milliseconds(dist(rng)));
        
        right_fork.unlock();
        left_fork.unlock();
        cout << "Philosopher " << id << " finished eating. Put down forks.\n";
    }
};

int main() {
    const int N = 5;
    vector<mutex> forks(N);
    vector<thread> philosophers;
    
    cout << "=== BROKEN VERSION (Will Deadlock) ===\n";
    cout << "Each philosopher picks up left fork first.\n";
    cout << "This will likely deadlock within seconds.\n\n";
    
    for (int i = 0; i < N; ++i) {
        // Each philosopher gets left fork = i, right fork = (i+1)%N
        philosophers.emplace_back([i, &forks]() {
            Philosopher p(i, forks[i], forks[(i+1) % N]);
            p.dine();
        });
    }
    
    // Let it run for a few seconds to see the deadlock
    this_thread::sleep_for(5s);
    cout << "\n*** The program is likely deadlocked now. ***\n";
    cout << "*** All philosophers hold one fork and wait forever. ***\n";
    cout << "*** Press Ctrl+C to exit. ***\n";
    
    for (auto& t : philosophers) {
        if (t.joinable()) t.join(); // Will never complete due to deadlock
    }
    
    return 0;
}