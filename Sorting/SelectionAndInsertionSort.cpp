#include<bits/stdc++.h>
using namespace std;

class sorter
{
    public:
        void selectionSort(vector<int>& arr, int size)
        {
            for(int i=0;i<size;i++)
            {
                int min=i;
                for(int j=i+1;j<size;j++)
                {
                   if(arr[j]<arr[min])
                     min=j;
                }
                swap(arr[i],arr[min]);
            }
        }
        void insertionSort(vector<int>& arr, int size)
        {
            for(int i=1;i<size;i++)
            {
                int key=arr[i];
                int j=i-1;
                while(j>=0 && key<arr[j])
                {
                    arr[j+1]=arr[j];
                    j--;
                }
                arr[j+1]=key;
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
    //s.selectionSort(arr,size);
    s.insertionSort(arr,size);
    cout<<"Elements after sorting\n";
    for(int i=0;i<size;i++)
      cout<<arr[i]<<" ";
    return 0;
}