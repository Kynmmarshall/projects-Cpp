#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;

class BoundedBufferCV {
private:
    queue<int> buffer;
    const size_t capacity;
    
    mutex mtx;
    condition_variable not_full;   // Signals that buffer is not full
    condition_variable not_empty;  // Signals that buffer is not empty
    
public:
    BoundedBufferCV(size_t cap) : capacity(cap) {}
    
    void produce(int item, int producer_id) {
        unique_lock<mutex> lock(mtx);
        
        // Wait if buffer is full
        not_full.wait(lock, [this]() { 
            return buffer.size() < capacity; 
        });
        
        // Critical section
        buffer.push(item);
        cout << "Producer " << producer_id << " produced item " << item 
             << ". Buffer size: " << buffer.size() << "/" << capacity << "\n";
        
        // Signal that buffer is not empty
        not_empty.notify_one();
    }
    
    int consume(int consumer_id) {
        unique_lock<mutex> lock(mtx);
        
        // Wait if buffer is empty
        not_empty.wait(lock, [this]() { 
            return !buffer.empty(); 
        });
        
        // Critical section
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << consumer_id << " consumed item " << item 
             << ". Buffer size: " << buffer.size() << "/" << capacity << "\n";
        
        // Signal that buffer is not full
        not_full.notify_one();
        
        return item;
    }
};

// Producer and consumer functions (similar to above)
void producer(BoundedBufferCV& buffer, int id, int num_items, atomic<bool>& running) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<> dist(1, 100);
    
    for (int i = 0; i < num_items && running; ++i) {
        int item = dist(rng);
        buffer.produce(item, id);
        this_thread::sleep_for(chrono::milliseconds(dist(rng) % 500 + 100));
    }
    cout << "Producer " << id << " finished.\n";
}

void consumer(BoundedBufferCV& buffer, int id, int num_items, atomic<bool>& running) {
    mt19937 rng(random_device{}());
    
    for (int i = 0; i < num_items && running; ++i) {
        int item = buffer.consume(id);
        this_thread::sleep_for(chrono::milliseconds(rng() % 300 + 200));
    }
    cout << "Consumer " << id << " finished.\n";
}

int main() {
    const int BUFFER_SIZE = 5;
    const int NUM_PRODUCERS = 2;
    const int NUM_CONSUMERS = 3;
    const int ITEMS_PER_PRODUCER = 10;
    
    BoundedBufferCV buffer(BUFFER_SIZE);
    vector<thread> producers, consumers;
    atomic<bool> running(true);
    
    cout << "=== BOUNDED BUFFER (Condition Variables) ===\n";
    cout << "Buffer capacity: " << BUFFER_SIZE << "\n\n";
    
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producers.emplace_back(producer, ref(buffer), i, ITEMS_PER_PRODUCER, ref(running));
    }
    
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumers.emplace_back(consumer, ref(buffer), i, ITEMS_PER_PRODUCER, ref(running));
    }
    
    for (auto& t : producers) t.join();
    cout << "\nAll producers finished. Waiting for consumers...\n";
    this_thread::sleep_for(3s);
    running = false;
    
    for (auto& t : consumers) t.join();
    
    cout << "\n=== Program completed ===\n";
    return 0;
}