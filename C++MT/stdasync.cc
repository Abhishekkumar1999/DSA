// TOPIC: std: async
// NOTES:
// 1. It runs a function asynchronously (potentially in a new thread) and returns a std:: future that will hold the result.(here we don't need promise object specifically, the async will take care of that internally)
// 2. There are three launch policies for creating task:
    //a. std:: launch: : async (It creates a separate thread for the task if you use this policy)
    //b. std:: launch:: deffered (It will not create a separate thread for the task, it will only called when .get() will hit)
    //c. std:: launch: async | std: : launch: :async (We will give control to the os here to decide meaning if there is a thread in thread pool then use first one otherwise use deffered policy)
// HOW IT WORKS:
// 1. It automatically creates a thread (Or picks from internal thread pool) and a promise object for us.
// 2. Then passes the std: promise object to thread function and returns the associated std:: future object.
// 3. When our passed argument function exits then its value will be set in this promise object,set in this promise object,so eventually return value will be available in std:: future object.
// SIDE NOTES:
// 1. We can send functor and lambda function as callback to std::async, it will work the same.

#include<iostream>
#include<thread>
#include<future>

typedef unsigned long long ull;

ull findOddSum(ull start, ull end)
{
    ull sum=0;
    for(ull i=start;i<=end;i++)
    {
        if(i&1)
          sum+=i;
    }
    std::cout<<"In oddSum "<<std::this_thread::get_id()<<"\n";
    return sum;
}

int main()
{
    ull start =0, end=190000;
    std::cout<<"using deffered policy"<<"\n";

    std::future<ull> res = std::async(/*policy*/std::launch::deferred,findOddSum,start,end);
    std::cout<<"In main "<<std::this_thread::get_id()<<"\n";
    std::cout<<"waiting for the result \n";
    std::cout<<res.get()<<"\n";
    std::cout<<"Done!!";
    return 0;
}