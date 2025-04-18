//TOPIC: Mutex In C++ Threading | Why Use Mutex | What Is Race Condition And How To Solve It? | What Is Critical Section
// Mutex:Mutual Exclusion
// RACE CONDITION
// 0. Race condition is a situation where two or more threads/process happend to change a common data at the same time.
// 1. If there is a race condition then we have to protect it and the protected setion is called critical section/ region.
// MUTEX:
// 0. Mutex is used to avoid race condition.
// 1. We use lock() , unlock() on mutex to avoid race condition.

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
        for(int i=0;i<10;i++){
          m.lock();
          var++;
          cout<<std::this_thread::get_id()<<" "<<var<<endl;
          m.unlock();
          std::this_thread::sleep_for(chrono::seconds(2));
        }
    };
    thread t1(fun);
    cout<<"Hello"<<endl;
    thread t2(fun);
    t1.join();
    t2.join();
    cout<<var<<endl;
    return 0;
}