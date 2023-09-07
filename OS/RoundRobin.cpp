// Program to implement Rounds Robin Scheduling Algorithm(C++)
 
#include<iostream>
using namespace std;
int main()
{

  int count,j,n,time,remain,flag=0,time_quantum;
  int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10];
  cout<<"Enter Total Process:\t ";
  cin>>n;
  remain=n;
  for(count=0;count<n;count++)
  {
    cout<<"Enter Arrival Time and Burst Time for Process Process Number"<<count+1<<":";
    cin>>at[count];
    cin>>bt[count];
    rt[count]=bt[count];
  }
  cout<<"Enter Time Quantum:\t";
  cin>>time_quantum;
  cout<<"\n\nProcess\t|Turnaround Time|Waiting Time\n\n";
  for(time=0,count=0;remain!=0;)
  {
    if(rt[count]<=time_quantum && rt[count]>0)
    {
      time+=rt[count];
      rt[count]=0;
      flag=1;
    }
    else if(rt[count]>0)
    {
      rt[count]-=time_quantum;
      time+=time_quantum;
    }
    if(rt[count]==0 && flag==1)
    {
      remain--;
 cout<<"P["<<count+1<<"]"<<"\t\t"<<time-at[count]<<"\t\t"<<time-at[count]- bt[count]<<"\n";
      wait_time+=time-at[count]-bt[count];
      turnaround_time+=time-at[count];
      flag=0;
    }
    if(count==n-1)
      count=0;
    else if(at[count+1]<=time)
      count++;
    else
      count=0;
  }
  cout<<"\nAverage Waiting Time="<<wait_time*1.0/n<<"\n";
  cout<<"Avg Turnaround Time = "<<turnaround_time*1.0/n<<"\n";
  
  return 0;
}

/*
Enter Total Process:     5
Enter Arrival Time and Burst Time for Process Process Number1:9 8
Enter Arrival Time and Burst Time for Process Process Number2:4 5
Enter Arrival Time and Burst Time for Process Process Number3:9 5
Enter Arrival Time and Burst Time for Process Process Number4:5 7
Enter Arrival Time and Burst Time for Process Process Number5:1 5
Enter Time Quantum:     3


Process |Turnaround Time|Waiting Time

P[1]            11              3
P[2]            18              13
P[3]            15              10
P[5]            28              23
P[4]            25              18

Average Waiting Time=13.4
Avg Turnaround Time = 19.4

*/