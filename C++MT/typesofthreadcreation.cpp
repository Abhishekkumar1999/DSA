#include<iostream>
#include<thread>

using namespace std;

//1. using function pointer
void fun(int x)
{
    while(x)
    {
        cout<<x<<" ";
        x--;
    }
}

//3. using functor or functional object
// class Base{
//     public:
//       void operator()(int x){
//        while(x)
//        {
//             cout<<x<<" ";
//             x--;
//        }
//       }
// };

//4 and 5. using member funtion and static funtion
class Base{
    public:
      void fun(int x){
       while(x)
       {
            cout<<x<<" ";
            x--;
       }
      }

      static void run(int x){
        while(x)
       {
            cout<<x<<" ";
            x--;
       }
      }
};

int main()
{
   //1. thread t(fun,10);//pas function pointer then pass all the paramenters for the functions like 10 is passed for x
   //   t.join();
   //2. lambda function
    //    auto fun1=[&](int x){
    //     while(x)
    //     {
    //         cout<<x<<" ";
    //         x--;
    //     }
    //    };
    //    thread t(fun1,11);//pass lamba then all the parameters for lambda like 11 is passed for x
    //    t.join();

    //3. using functor or functional object
    // thread t(Base(),12);//pass the funtor and then the parameters for that like 12 is passed for x
    // t.join();

    //4. using member funtion
    // Base b;
    // thread t(&Base::fun,&b,15);//pass the ref of member funtion and object and then parameters required by member funtion
    // t.join();

    //5. using class funtion or static member funtion
    Base b;
    thread t(&Base::run,20);//pass the ref of class funtion and then parameters required by funtion
    t.join();

   return 0;
}