#include<bits/stdc++.h>
using namespace std;

class sorter
{
    private:
       void merge(vector<int>& arr, int l, int mid, int r)
       {
          int size1= mid - l + 1;
          int size2 = r - mid;
          vector<int> arr1(size1),arr2(size2);
          for(int i=0;i<size1;i++)
           arr1[i]=arr[l+i];
          for(int i=0;i<size2;i++)
           arr2[i]=arr[mid+i+1];
          int i=0,j=0,x=l;
          while(i<size1 && j<size2)
          {
            if(arr1[i]<arr2[j])
              arr[x++]=arr1[i++];
            else
             arr[x++]=arr2[j++];
          }
          if(i>=size1)
          {
            while(j<size2)
            {
              arr[x++]=arr2[j++];
            }
          }
          if(j>=size2)
          {
            while(i<size1)
            {
              arr[x++]=arr1[i++];
            }
          }
       }
       void mergeSort(vector<int>& arr, int left, int right)
       {
          if(left>=right)
           return;
          int mid = left + (right-left)/2;
          mergeSort(arr,left,mid);
          mergeSort(arr,mid+1,right);
          merge(arr,left,mid,right);
       }
    public:
        void MergeSort(vector<int>& arr, int size)
        {
           mergeSort(arr,0,arr.size()-1);
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
    s.MergeSort(arr,size);
    cout<<"Elements after sorting\n";
    for(int i=0;i<size;i++)
      cout<<arr[i]<<" ";
    return 0;
}