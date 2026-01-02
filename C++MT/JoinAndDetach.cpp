// / TOPIC: Use Of join(), detach() and joinable() In Threar

// / JOIN NOTES
// / 0. Once a thread is started we wait for this thread to finish by calling join() function on thread object.
// / 1. Double join will result into program termination.
// / 2. If needed we should check thread is joinable before joining. ( using joinable() function)

// / DETACH NOTES
// / 0. This is used to detach newly created thread from the parent thread.
// / 1. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and
// / double detach() will result into program termination.
// / 2. If we have detached thread and main function is returning then the detached thread execution is suspended

// / NOTES:
// / Either join() or detach() should be called on thread object, otherwise during thread object's destructor it will
// / terminate the program. Because inside destructor it checks if thread is still joinable? if yes then it terminates the program.

//We can get id information using this_thread::get_id():
//std::cout << "Number of threads = " <<  std::thread::hardware_concurrency() << std::endl;

//Examples
#include<iostream>
#include<thread>
#include<chrono>
using namespace std;

void displaySomething(int x)
{
    for(int i=0;i<x;i++)
    {
      cout<<"Abhi "<<i<<endl;
    }
    std::this_thread::sleep_for(chrono::seconds(5));
}
int main()
{
    thread t(displaySomething,10);
    //use of join
    //cout<<"Before join"<<endl;
    // t.join();//it waits untile thread doesn't return
    // cout<<"After join"<<endl;
    // if(t.joinable())
    //   t.join();//double join will cause program termination, so better check if thread is joinable before usin join

    //use of detach(we only use detach for background taks i.e. where no synchronisation required. use this with cuatio)
    cout<<"Before detach"<<endl;
    t.detach();
    cout<<"After detach"<<endl;
    std::this_thread::sleep_for(chrono::seconds(5));
    return 0;

}
