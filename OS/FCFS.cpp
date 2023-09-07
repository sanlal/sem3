#include<bits/stdc++.h>
#include<iostream>
using namespace std;


int main(){
	int n;
	cout<<"Enter n: ";
	cin>>n;
	
//	int P[n];
	int AT[n];
	int ET[n];
//	cout<<"Enter Arrival Time and Execution time: ";
	for(int i=1;i<=n;i++){
		cout<<"Enter Arrival Time and Execution time for P"<<i<<" : ";
		cin>>AT[i]>>ET[i];
	}
	
	
	
	int ST[n];
	ST[1]=AT[1];
	cout<<ST[0];
	for(int i=2;i<=n;i++){
		ST[i] =ET[i-1] + ST[i-1];
	}
	
	int FT[n];
	int sum=0;
	for(int i=1;i<=n;i++){
		sum += ET[i];
		FT[i] = sum;
	}
	
	int TAT[n];
	for(int i=1;i<=n;i++){
		TAT[i] = FT[i] - AT[i];
	}
	
	int WT[n];
	for(int i=1;i<=n;i++){
		WT[i] = TAT[i] - ET[i];
	}
	
	cout<<endl<<"P \t AT \t ET \t ST \t FT \t TAT \t WT \t"<<endl;
	for(int j=1;j<=n;j++){
		cout<<"P"<<j<<"\t"<<AT[j]<<"\t"<<ET[j]<<"\t"<<ST[j]<<"\t"<<FT[j]<<"\t"<<TAT[j]<<"\t"<<WT[j];
		cout<<endl;
	}
		
	
}