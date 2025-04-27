#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>

#define MAX 100
int buffer=0;
std::mutex m;
std::condition_variable cv;
void producer(int rep)
{
  while(rep){
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul,[&](){return buffer<MAX;});
    buffer++;
    rep--;
    std::cout<<"Produced, Current buffer val: "<<buffer<<"\n";
    ul.unlock();
    cv.notify_one();
  }
}
void consumer()
{
    while(1){
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul,[&](){return buffer>0;});
        buffer--;
        std::cout<<"Consumed, Current buffer val: "<<buffer<<"\n";
        ul.unlock();
        cv.notify_one();
    }
}

int main()
{
    std::thread t1(producer,50);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}