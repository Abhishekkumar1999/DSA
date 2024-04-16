#include<bits/stdc++.h>
using namespace std;

class sorter
{
    public:
        void buuble_sort(vector<int>& arr, int size)
        {
            for(int i=0;i<size-1;i++)
            {
                bool alreadySorted=true;
                for(int j=0;j<size-i-1;j++)
                {
                    if(arr[j+1]<arr[j])
                    {
                       alreadySorted=false;
                       int temp=arr[j];
                       arr[j]=arr[j+1];
                       arr[j+13]=temp;
                    }
                }
                if(alreadySorted)
                 break;
            }
        }
};

int main()
{
    int size;
    vector<int> arr;
    cout<<"Enter the size of the array\n";
    cin>>size;
    arr.resize(size);
    cout<<"Enter the array elements\n";
    for(int i=0;i<size;i++)
      cin>>arr[i];
    cout<<"Elements before sorting\n";
    for(int i=0;i<size;i++)
      cout<<arr[i]<<" ";
    sorter s;
    s.buuble_sort(arr,size);
    cout<<"Elements after sorting\n";
    for(int i=0;i<size;i++)
      cout<<arr[i]<<" ";
    return 0;
}