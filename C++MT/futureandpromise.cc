/*
1. Future and promise concept is part of c++ async programming
2. We use future and promise concept where we need the local value used/set/generated inside a thread at global level.
3. To achive this we first create a promise object of a that particular data type.
4. Then we will create the future object which will get data from the promise object after running the thread(means in future)
5. To use this concept we need to include the "future.h" headerfile
*/

//Example
//Let say we have to create sum of 90000 numbers and we want the local sum of by that thread for a range
#include<iostream>
#include<thread>
#include<future>
#include<vector>
void getSum(std::promise<size_t>&& p, int start, int end)
{
    size_t sum=0;
    for(int i=start;i<=end;i++)
    {
        sum+=i;
    }
    p.set_value(sum);//here we set the local value by this thread to the promise object so that in future the future object can get the value by promise
}

int main()
{
    std::vector<std::promise<size_t>> p(3);
    std::vector<std::future<size_t>> f(3);
    for(int i=0;i<3;i++)
      f[i]=p[i].get_future();//making promise for future

    std::thread t1(getSum,std::move(p[0]),1,30000);
    std::thread t2(getSum,std::move(p[1]),30001,60000);
    std::thread t3(getSum,std::move(p[2]),60001,90000);

    std::cout<<"First: "<<f[0].get()<<"\n";//If we call .get(), then future object will wait until it doesn't get the value.
    std::cout<<"Sec: "<<f[1].get()<<"\n";
    std::cout<<"Third: "<<f[2].get()<<"\n";

    t1.join();
    t2.join();
    t3.join();
    return 0;
}