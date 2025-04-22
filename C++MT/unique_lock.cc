// TOPIC: unique lock In C++ (std :: unique_lock<mutex> lock(m)

// NOTES:
// 1. The class unique lock is a mutex ownership wrapper.
// 2. It Allows:
        // a. Can Have Different Locking Strategies
        // b. time-constrained attempts at locking (try_lock_for, try_lock_until)
        // c. recursive locking
        // d. transfer of lock ownership (move not copy)
        // e. condition variables. (See this in coming videos)

// Locking Strategies
        // TYPE                EFFECTS(S)
        // 1. defer_lock       do not acquire ownership of the mutex.
        // 2. try_to_lock      try to acquire ownership of the mutex without blocking.
        // 3. adopt_lock       assume the calling thread already has ownership of the mutex.

#include<iostream>
#include<thread>
#include<mutex>

int main()
{
    std::mutex m;
    int var=0;
    //this is not thread safe, because of race condition
    // auto fun=[&](){
    //     for(int i=0;i<1000000;i++){
    //         var++;
    //       //std::cout<<std::this_thread::get_id()<<" "<<var<<"\n";
    //     }
    // };

    //to make thread safe, either we can create a mutex and ask thread to who will acquire the thread will do the operation 
    // auto fun=[&](){
    //        m.lock();
    //         for(int i=0;i<1000000;i++){
    //             var++;
    //           //std::cout<<std::this_thread::get_id()<<" "<<var<<"\n";
    //         }
    //         m.unlock();
    // };
    //we have seen, the use of lock_guard as well
    // auto fun=[&](){
    //     std::lock_guard<mutex> lock(m);//it will immideately acquire the lock
    //      for(int i=0;i<1000000;i++){
    //          var++;
    //        //std::cout<<std::this_thread::get_id()<<" "<<var<<"\n";
    //      }
         
    // };
    //now when we want to acuqire the lock and want to try different strategy based upon situation then we can use try lock
    auto fun=[&](){
        //std::unique_lock<std::mutex> lock(m);//immediately acquire the lock
        std::unique_lock<std::mutex> lock(m,std::defer_lock);
        //it will not acquire the lock immediately, but it will lock manualy but the best part is unlocking will happen automatically through destructor
        lock.lock();
         for(int i=0;i<1000000;i++){
             var++;
           //std::cout<<std::this_thread::get_id()<<" "<<var<<"\n";
         }
         
    };
    std::thread t1(fun);
    std::thread t2(fun);

    t1.join();
    t2.join();
    std::cout<<var<<"\n";
    return 0;

}
