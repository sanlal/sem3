#include<iostream>
using namespace std;

void swap(int *x,int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void InsertionSort(int a[],int n){
    for(int i=1;i<n;i++){
        int j=i-1;
        int min =a[i];
        
        while(j>-1 && a[j]>min){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=min;
    }
}

int main(){
    int a[]={3,7,9,10,6,5,12,4,11,2};
    int n=10;
    InsertionSort(a,n);

    cout<<"Insertion Sort::  ";
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;

    return 0;
}