#Scheduling Program for FCFS


#include<iostream>
#define MAX_PROCESS 10
using namespace std;
class process
{
  public:
  int process_num;
  int burst_time;
  int arrival_time;
  int service_time;
  int completion_time;
  int waiting_time;
  int turnaround_time;
  void input_process(int);
  int get_at()
  {
    return arrival_time;
  }
};
 

//Inputs the arrival and burst time for process
void process::input_process(int count)
{
  process_num=count+1;
  cout<<"\nENTER ARRIVAL TIME FOR PROCESS "<<count+1<<" : ";
  cin >>arrival_time;
  cout<<"\ENTER BURST TIME FOR PROCESS "<<count+1<<" : ";
  cin>>burst_time;
  
}


void calc_wait_tat(process*,int);
void average(process*,int);
void display(process*,int);


int main(){
  process p[MAX_PROCESS],temp;
  int num,i,j;
  cout<<"ENTER NUMBER OF PROCESSES : ";
  cin>>num;
  for(i=0;i<num;++i)
    p[i].input_process(i);
  for(i=0;i<num;++i)
  {
    for(j=i+1;j<num;++j)
    {
      if(p[i].get_at()>p[j].get_at())
      {
        temp=p[i];
        p[i]=p[j];
        p[j]=temp;
      }
    }
  }
  calc_wait_tat(p,num);
  display(p,num);
  return 0;
}

//Waiting Time = Turn around time - burst time
//Turn around time  = burst time  + Waiting time
//Completion time = burst_time + 0 (for the first proccess)
void calc_wait_tat(process *p,int n)
{
  int i;
  p[0].service_time=0;
  for(i=1;i<n;++i)
  {
    p[i].service_time=p[i-1].burst_time+p[i-1].service_time;
    if(p[i].service_time<p[i].arrival_time)
      p[i].service_time=p[i].arrival_time;
  }
  
  p[0].waiting_time=0;
  for(i=1;i<n;++i)
    p[i].waiting_time=p[i].service_time-p[i].arrival_time;
  for(i=0;i<n;++i)
    p[i].turnaround_time=p[i].waiting_time+p[i].burst_time;

  p[0].completion_time = p[0].burst_time;
  for(i = 1; i<n;i++)
  {
    p[i].completion_time = p[i-1].completion_time + p[i].burst_time;
  }
}

//function for average of waiting time and turn around time 
void average(process *p,int n)
{
  float avg_wt=0,avg_tat=0,avg_st = 0, avg_ct=0;
  for(int i=0;i<n;++i)
  {
    avg_wt+=(float)p[i].waiting_time;
    avg_tat+=(float)p[i].turnaround_time;
    avg_ct+=(float)p[i].completion_time;
    avg_st+=(float)p[i].service_time;
  }
  avg_wt/=n;
  avg_tat/=n;
  avg_ct/=n;
  avg_st/=n;
  cout<<"\n\nAVERAGE WAITING TIME : "<<avg_wt;
  cout<<"\nAVERAGE TURN AROUND TIME : "<<avg_tat;
  cout<<"\nAVERAGE COMPLETION TIME : "<<avg_ct;
  cout<<"\nAVERAGE SERVICE TIME : "<<avg_st;
}


void display(process *p,int n)
{
        cout<<"Processes "<<"  Burst time  "<< "Service Time  " << "Completion Time " << " Waiting time  "<<" Turn around time\n";
        for (int i=0;i<n;i++)
        {
                cout<<"\n   "<<p[i].process_num<<"\t\t"<<p[i].burst_time<<"\t     " << p[i].service_time<<"\t\t   " << p[i].completion_time << "\t\t" <<p[i].waiting_time<<"\t\t      "<<p[i].turnaround_time;
        }
        average(p,n);
}
