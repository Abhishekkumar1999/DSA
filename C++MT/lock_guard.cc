// NOTES:
//Syntac: std::lock_guard<mutex> lock(m);
// 0. It is very light weight wrapper for owning mutex on scoped basis.
// 1. It aquires mutex lock the moment you create the object of lock guard.
// 2. It automatically removes the lock while goes out of scope.
// 3. You can not explicitly unlock the lock_guard.
// 4. You can not copy lock_guard.
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

int main()
{
    mutex m;
    int var=0;
    //to make entire scope thread safe or for example here entire loop, we have to acquire the thread
    //and relase if just before ending the scope. Now here you have to manually take care of releasing of
    //mutex at the end of the scope
    // auto fun=[&]()
    // {
    //     m.lock();
    //     for(int i=0;i<100000;i++){
    //       var++;
    //     }
    //     m.unlock();
    // };

    //if we don't want to manually release the mutex at the end of the scope the try lock_guard
    auto fun=[&]()
    {
        std::lock_guard<mutex> lg(m);//lock will be aquire just after creation of the lock guard obj
        //and at the end of the scope it's destructor will be responsible to release the lock
        for(int i=0;i<100000;i++){
          var++;
        }
    };
    thread t1(fun);
    thread t2(fun);
    t1.join();
    t2.join();
    cout<<var<<endl;
    return 0;
}