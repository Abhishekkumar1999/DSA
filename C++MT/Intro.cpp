#include<iostream>
#include<chrono>
#include<thread>

using namespace std;

typedef unsigned long long ull;
ull Odd=0,Even=0;

void sumOdd(ull start, ull end)
{
  for(ull i=start;i<=end;i++)
  {
    if(i&1)
      Odd+=i;
  }
}

void sumEven(ull start, ull end)
{
    for(ull i=start;i<=end;i++)
    {
      if((i&1) == 0)
        Even+=i;
    }
}

int main()
{
    ull start = 0, end = 190000000000;
    auto startTime = chrono::high_resolution_clock::now();
    /*1. Single threaded. version*/
    // sumEven(start,end);
    // sumOdd(start,end);

     /*MT version*/
     thread t1(sumEven,start,end);
     thread t2(sumOdd,start,end);

     t1.join();
     t2.join();

    cout<<"Even: "<<Even<<endl;
    cout<<"Odd: "<<Odd<<endl;
    auto endTime = chrono::high_resolution_clock::now();
    cout<<"Time taken: "<<(chrono::duration_cast<chrono::microseconds>(endTime-startTime).count()/1000000);
    return 0;
}