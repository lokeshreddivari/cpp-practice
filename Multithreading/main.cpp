#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// Shared variable
int counter = 0;

// Mutex to prevent race condition
std::mutex mtx;

// Condition variable to coordinate threads
std::condition_variable cv;

// Flag to alternate between threads
bool thread1_turn = true;

// How many times each thread increments
const int MAX_COUNT = 100;

void thread1_increment() {
    for (int i = 0; i < MAX_COUNT; i++) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until it's thread1's turn
        cv.wait(lock, [] { return thread1_turn; });

        // Increment shared variable
        counter++;
        std::cout << "Thread 1 incremented counter to: "
                  << counter << std::endl;

        // Give turn to thread 2
        thread1_turn = false;

        // Notify thread 2
        cv.notify_all();
    }
}

void thread2_increment() {
    for (int i = 0; i < MAX_COUNT; i++) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until it's thread2's turn
        cv.wait(lock, [] { return !thread1_turn; });

        // Increment shared variable
        counter++;
        std::cout << "Thread 2 incremented counter to: "
                  << counter << std::endl;

        // Give turn to thread 1
        thread1_turn = true;

        // Notify thread 1
        cv.notify_all();
    }
}

int main() {
    std::cout << "Starting two threads..." << std::endl;
    std::cout << "Initial counter: " << counter << std::endl;

    // Create two threads
    std::thread t1(thread1_increment);
    std::thread t2(thread2_increment);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    std::cout << "\nFinal counter value: " << counter << std::endl;
    std::cout << "Expected value: " << MAX_COUNT * 2 << std::endl;

    return 0;
}
