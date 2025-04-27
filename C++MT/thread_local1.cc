#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

// Thread-local storage
thread_local int local_value = 0;

// To collect results
std::vector<int> collection_points;

void thread_function(size_t thread_idx) {
    // Each thread modifies its own thread-local value
    local_value = thread_idx * 10;  // Some example computation
    
    // Store result in pre-allocated slot
    collection_points[thread_idx] = local_value;
}

int main() {
    const int num_threads = 10;
    std::vector<std::thread> threads;
    
    // Pre-allocate slots to store each thread's local value
    collection_points.resize(num_threads);
    
    // Create threads
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(thread_function, i));
    }
    
    // Join all threads
    for (auto& t : threads) {
        t.join();
    }
    
    // Combine thread-local values (after all threads complete)
    int combined_value = 0;
    for (int value : collection_points) {
        combined_value += value;
    }
    
    std::cout << "Combined value: " << combined_value << std::endl;
    
    return 0;
}