// TOPIC: std: :mutex::try_lock() On Mutex In C++11 Threading
// 0. try_lock() Tries to lock the mutex. Returns immediately. On successful lock acquisition returns true otherwise returns false.
// 1. If try_lock() is not able to lock mutex, then it doesn't get blocked that's why it is called non-blocking, where as if a thread uses lock and it didn't get the lock then it will get blocked
//If try_lock is called again by the same thread which owns the mutex, the behavior is undefined.
//It is a dead lock situation with undefined behaviour. (if you want to be able to lock the same mutex by same thread
//more than one time the go for recursive_mutex)

// There are so many try_lock function
// 1. std:: try_lock &
// 2. std::mutex:: try lock
// 3. std::shared lock: :try_lock
// 4. std: :timed mutex::try_lock
// 5. std: :unique_lock:: try_lock
// 6. std:: shared mutex:: try lock
// 7. std:: recursive mutex::try lock
// 8. std: :shared_timed mutex::try_lock
// 9. std:: recursive_timed mutex:: try_lock

//When to use lock() and when to use try_lock()
// Example 1: ATM Banking System
// Using lock()
//Customer withdrawal - must complete transaction
// void withdrawMoney(Account& account, int amount) {
//     account_mutex.lock();  // Wait for account access
//     // Critical transaction that can't be skipped
//     std::cout << "Customer " << std::this_thread::get_id() << " withdrawing $" << amount << std::endl;
//     account.balance -= amount;
//     dispenseCase(amount);
//     account_mutex.unlock();
// }
// Using try_lock()
// Balance inquiry - can retry later if system busy
// bool checkBalance(Account& account) {
//     if (account_mutex.try_lock()) {
//         // Display balance
//         std::cout << "Balance for customer " << std::this_thread::get_id() 
//                   << ": $" << account.balance << std::endl;
//         account_mutex.unlock();
//         return true;
//     } else {
//         std::cout << "System busy, please try again shortly" << std::endl;
//         return false;
//     }
// }
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

int main()
{
    mutex m;
    int var=0;
    auto fun=[&]()
    {
        for(int i=0;i<100000;i++){
         if( m.try_lock()){
          var++;
          m.unlock();
         }
        }
    };
    thread t1(fun);
    //cout<<"Hello"<<endl;
    thread t2(fun);
    t1.join();
    t2.join();
    cout<<var<<endl;
    return 0;
}

//Explanation: As we know if a thread uses try_lock to acquire the thread and if it doesn't get the mutex and it will not get suspended instead it return false
//so, what can happen is if T1 and T2 simultaneously trying to acquire the mutex then Let say T1 acquire first then T2 will not get suspended 
// and keep on waiting istead it will run the next iteration and try acquiring the mutex and hence it might skip some operations.