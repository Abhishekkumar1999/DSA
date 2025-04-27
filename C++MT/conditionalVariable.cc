// TOPIC: Condition Variable In C++ Threading
// IMPORTANT POINT: CV are used for two purpose
//
//A. Notify other threads
//B. Waiting for some conditions
// 1. Condition Variable allows running threads to wait on some conditions and once those condition are met then waiting thread is notified using
    // a. notify_one();
    // b. notify_all();
// 2. You need mutex to use condition variable.
// 3. If some thread want to wait on some condition then it has to do these things:
    //a. Acquire the mutex lock using std: :unique_lock<std::mutex> lock(m) ; •
    //b. Execute wait, wait_for and wait_until. The wait operation will automatically release the mutex and suspend the execution of the thread.
    //c. When the condition variable is notified, the thread is awakened, and the mutex is atomically reacquired. The thread should then check the condition and resume waiting if the wake
    //up was spurious
// NOTE:
// 1. Condition variables are used to synchronize two or more threads.
// 2. Best use case of condition variable is Producer/Consumer problem.
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>


int main()
{
    std::mutex m;
    std::condition_variable cv;
    int balance=0;
    auto addMoney=[&](int amt){
        std::lock_guard<std::mutex> l(m);
        balance+=amt;
        std::cout<<amt<<" rupees credited successfully...\n";
        cv.notify_one();
    };

    auto withdrawMoney=[&](int amt){
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul,[&]{return balance>0?true:false;});
        if(balance >= amt){
            balance-=amt;
          std::cout<<amt<<" rupees debited successfully...\n";
        }
        else{
            std::cout<<"Insufficient balance!\n";
        }
    };

    
    
    std::thread t2(withdrawMoney,700);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::thread t1(addMoney,500);
    t1.join();
    t2.join();

    return 0;

}