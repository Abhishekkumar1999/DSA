//1. std::try_lock() tries to lock all the lockable objects passed in it one by one in given order.
//2. Syntax: std::try_lock(m1,m2,m3,m4,m5)
//2. On success this function returns -1 otherwise it will return 0-based mutex index number which it could not lock.
//3. If it fails to lock any of the mutex then it will release all the mutex it locked before.
//4. If a call to try_lock results in an exception, unlock is called for any locked objects before rethrowing.
//Exmple
#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

int X=0,Y=0;
mutex m1,m2;

void incrementXorY(int &XorY, mutex& m, const string& str)
{
    for(int i=0;i<5;i++)
    {
        m.lock();
        ++XorY;
        cout<<XorY<<endl;
        m.unlock();
        this_thread::sleep_for(chrono::seconds(5));
    }
}

void consumeXorY(){
    int count=5;
    int sumXandY=0;
    int itr=0;
    while(1)
    {
        int status=try_lock(m1,m2);
        if(status==-1)//means lock mutexes got acquired
        {
            if(X>0 && Y>0)
            {
                --count;
                sumXandY+=X+Y;
                cout<<"sum: "<<sumXandY<<endl;
                X=0;Y=0;
            }
            m1.unlock();m2.unlock();
            if(count==0)
              break;
        }
        cout<<"Itr: "<<itr<<endl;
    }
}

int main()
{
    thread t1(incrementXorY,std::ref(X),std::ref(m1),"X");
    thread t2(incrementXorY,std::ref(Y),std::ref(m2),"Y");
    thread t3(consumeXorY);
    t1.join();t2.join();t3.join();
    cout<<"Programm successful"<<endl;
    return 0;
}