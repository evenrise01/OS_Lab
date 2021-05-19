#include <bits/stdc++.h>
#include <vector>
using namespace std;

/* TAT = CT - AT
WT = TAT - BT
RT = ST - AT
*/

//Global Scope Variables
int n;
int i;
float avg_turnaround_time;
float avg_waiting_time;
float avg_response_time;
float cpu_utilisation = 0;
int total_turnaround_time = 0; 
int total_waiting_time = 0;
int total_response_time = 0;
int total_idle_time = 0;
float throughput = 0;


//Variable Structure
struct process {
    int pid; //process id
    int priority = 0; //priority
    int arrival_time; //arrival time
    int burst_time; //burst time
    int start_time; //start time
    int completion_time; //completion time
    int turnaround_time; // turn around time
    int waiting_time; // waiting time
    int response_time; // response time
};

//Compare Arrival Time of the Processes
bool compareArrival(process p1, process p2) 
{ 
    return p1.arrival_time < p2.arrival_time;
}

bool compareBurst(process p1, process p2)
{
    return p1.burst_time < p2.burst_time;
}
//Compare Process ID of the Processes
bool compareID(process p1, process p2) 
{  
    return p1.pid < p2.pid;
}

//Function to calculate average TAT, WT, RT and Cpu utilisation and throughput
void calculate_average(process p[], int n){
    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((p[n-1].completion_time - total_idle_time) / (float) p[n-1].completion_time)*100;
    throughput = float(n) / (p[n-1].completion_time - p[0].arrival_time);
}

//Function to print formatted table of the processes
void print_table(process p[], int n){

    cout << "\t\t\tPROCESS TABLE\n\n";
    cout<<endl;
    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].priority<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].response_time<<"\t"<<"\n"<<endl;
    }

  cout << "\n\n";
}

//Function to print the calculated average
void print_average(process p[], int n){

    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
    cout<<"Average Response Time = "<<avg_response_time<<endl;
    cout<<"CPU Utilization = "<<cpu_utilisation<<"%"<<endl;
    cout<<"Throughput = "<<throughput<<" process/unit time"<<endl;

total_turnaround_time = 0; 
total_waiting_time = 0;
total_response_time = 0;
total_idle_time = 0;
throughput = 0;
cpu_utilisation = 0;
    cout << "\n\n";
}


void printGantt(vector<int> &processName, vector<int> &processChangeTime)
{

   
    cout << " GANTT CHART \n\n" << endl;


  for(int i = 0; i < processName.size(); i++) //display box
  {
    cout << "+-------";
  }
  cout << "+" << endl;

  for(int i = 0; i < processName.size(); i++) //display process name
  {
    cout << "|   " << "P" << processName[i] << "  ";
  }
  cout << "| " << endl;

  for(int i = 0; i < processName.size(); i++) // display box again
  {
    cout << "+-------";
  }
  cout << "+" << endl;

  for(int i = 0; i < processChangeTime.size(); i++) //display time
  {
    cout << processChangeTime[i];
    
    if(processChangeTime[i] < 10)
      cout << "       ";
    else
      cout << "      ";
  }
  cout << endl << endl;
}


//First Come First Serve
void FCFS() {
    
    cout << "\n                                                    -  First Come First Serve Scheduling Algorithm -                              \n" << endl;
   

    struct process p[100];
    vector<int> processChangeTime; //for gantt chart output
    vector<int> processName; //for gantt chart output
    cout << setprecision(2) << fixed;

    
    cout<<"Enter the number of processes: \n";
    cin>>n;

     if(n == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 

    else if (n != 0){

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        cout<<endl;
        }
    }
    sort(p,p+n,compareArrival);
    processChangeTime.push_back(p[0].arrival_time);

    for(int i = 0; i < n; i++) {
        p[i].start_time = (i == 0)?p[i].arrival_time:max(p[i-1].completion_time,p[i].arrival_time);
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
        total_response_time += p[i].response_time;
        total_idle_time += (i == 0)?(p[i].arrival_time):(p[i].start_time - p[i-1].completion_time);
        
        processChangeTime.push_back(p[i].completion_time);
        processName.push_back(p[i].pid);
    }
    sort(p,p+n,compareID);

    calculate_average(p,n);
    sort(p,p+n,compareID);
    print_table(p, n);
    printGantt(processName, processChangeTime);
    print_average(p, n);
    system("pause");

}
//Shortest Job First 
void SJF() {

   
    cout << "                                                     - Shortest Job First Scheduling Algorithm -                                   \n" << endl;
     


    struct process p[100];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed)); //Mark all the elements 'False' in the array is_completed
    vector<int> processChangeTime; //for gantt chart output
    vector<int> processName; //for gantt chart output
    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: \n";
    cin>>n;

    if(n == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 

    else if (n != 0){
        
    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        cout<<endl;
        }
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    sort(p,p+n,compareArrival);
    processChangeTime.push_back(p[0].arrival_time);
//While all the processes are not completed 
//find process with minimum burst time among process that are in ready queue at current_time
    while(completed != n) {
        int idx = -1;
        int mn = 10000000;

        for(i = 0; i < n; i++) {
            //If the process is not completed and it's arrival time is less than the current time
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) { 
                if(p[i].burst_time < mn) {
                    mn = p[i].burst_time;
                    idx = i;

                }
                if(p[i].burst_time == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].burst_time;
                        idx = i;
                        
                    }
                }
            }
        }
        

        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
            processName.push_back(p[idx].pid); //For Gantt Chart
            processChangeTime.push_back(current_time);  //For gantt Chart
            
        }
        else {
            current_time++;
        }
    }
    
    calculate_average(p,n);
    sort(p,p+n,compareID);
    print_table(p, n);
    printGantt(processName,processChangeTime);
    print_average(p, n);
    system("pause");
}
//Shortest Remaining Time First
void SRTF() {

   
    cout << "\n                                                   - Shortest Remaining Time Scheduling Algorithm -                             \n" << endl;
       


    struct process p[100];
    vector<process> ready;
    vector<int> processChangeTime; //for gantt chart output
    vector<int> processName; //for gantt chart output
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: \n";
    cin>>n;

     if(n == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 

    else if (n != 0){

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        burst_remaining[i] = p[i].burst_time;
        cout<<endl;
    }
}  

    int current_time = 0;
    int completed = 0;
    int prev = 0;
    sort(p,p+n,compareArrival);
    processChangeTime.push_back(p[0].arrival_time);
    //find process with minimum burst time among process that are in ready queue at current_time
    while(completed != n) {
        int idx = -1;
        int mn = 10000000;

        //Criteria for scheduling SRTF is burst time
        for(int i = 0; i < n; i++) {
            
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(burst_remaining[i] < mn) {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if(burst_remaining[i] == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
              
            }
        }

        //if process is getting CPU for the first time; start_time = current_time
            
        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;
            processName.push_back(p[idx].pid); //For Gantt Chart
            processChangeTime.push_back(current_time);  //For gantt Chart
            
            //if burst_time = 0 then calcualate TAT, WT and RT for the process
            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1; //mark process as completed
                completed++;
                
            }
        }
        else {
             current_time++;
        }  
    }
    
    calculate_average(p,n);
    sort(p,p+n,compareID);
    print_table(p, n);
    printGantt(processName,processChangeTime);
    print_average(p, n);
    system("pause");

}
//Non-Preemptive Priority
void NP_Priority() {

    
    cout << "                                                 -  Priority (Non-Preemptive) Scheduling Algorithm  -                            " << endl;
     

    vector<int> processChangeTime; //for gantt chart output
    vector<int> processName; //for gantt chart output
    struct process p[100];
    int is_completed[100];
    
    memset(is_completed,0,sizeof(is_completed)); //Mark all the elements 'False' in the array is_completed

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: \n";
    cin>>n;

     if(n == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 

    else if (n != 0){

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        cout<<"Enter priority of the process "<<i+1<<": ";
        cin>>p[i].priority;
        p[i].pid = i+1;
        cout<<endl;
    }
}


    int current_time = 0;
    int completed = 0;
    int prev = 0;

    sort(p,p+n,compareArrival);
    processChangeTime.push_back(p[0].arrival_time);
    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }  
                }   
            }
           
        }
        
        //find process with maximum priority among process that are in ready queue at current_time
        // and calculate CT,TAT,WT and RT for the process
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
            processName.push_back(p[idx].pid); //For Gantt Chart
            processChangeTime.push_back(current_time);  //For gantt Chart 
        }
        else {
            current_time++;
        }
        
    }

    calculate_average(p,n); 
    sort(p,p+n,compareID);
    print_table(p, n);
    printGantt(processName, processChangeTime);
    print_average(p, n);
    system("pause");
}

//Preemptive Priority
void P_Priority() {

    
    cout << "                                                  - Priority (Preemptive) Scheduling Algorithm -                                  " << endl;
     
    
    vector<int> processChangeTime; //for gantt chart output
    vector<int> processName; //for gantt chart output
    struct process p[100];
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed)); //Mark all the elements 'False' in the array is_completed

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: \n";
    cin>>n;

     if(n == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 

    else if (n != 0){

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        cout<<"Enter priority of the process "<<i+1<<": ";
        cin>>p[i].priority;
        p[i].pid = i+1;
        burst_remaining[i] = p[i].burst_time;
        cout<<endl;
    }
}
    int current_time = 0;
    int completed = 0;
    int prev = 0;

     processChangeTime.push_back(p[0].arrival_time);
     while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;
            processName.push_back(p[idx].pid);
            processChangeTime.push_back(current_time);
            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }  
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }
    
    calculate_average(p,n);
    print_table(p, n);
    printGantt(processName, processChangeTime);
    print_average(p, n);
    system("pause");
    
}
//Round Robin Scheduling
void round_robin(){
    
    
    cout << "\n                                                  - Round Robin Scheduling Algorithm -                                            \n" << endl;
     

    int tq; //initialise the variable for quantum time
    struct process p[100];
    vector <int> processChangeTime; //for GanttChart output
    vector<int> processName; //for GanttChart output
    int time = 0;

    int burst_remaining[100]; //Initialise array for remaining burst time of the process
    int idx; //initialise index counter

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: \n";
    cin>>n;
    cout<<"Enter time quantum: ";
    cin>>tq;

     if(n == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 

    else if (n != 0){

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i+1;
        cout<<endl;
    }
    }
    //Sort the processes in order of their Arrival Time
    sort(p,p+n,compareArrival);


    queue <int> q; //Using a FIFO Queue
    int current_time = 0; //Variable to keep track of the time
    q.push(0);
    int completed = 0; //Keep track of the completion of the process
    int mark[100]; //Array to check if the process is in the queue or not
    memset(mark,0,sizeof(mark)); //Mark all the array 'False'
    mark[0] = 1; //Initialise first element of array Mark as 'True'

    processChangeTime.push_back(p[0].arrival_time);
    while(completed != n) {
        idx = q.front();
        q.pop();

        if(burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = max(current_time,p[idx].arrival_time);
            total_idle_time += p[idx].start_time - current_time;
            current_time = p[idx].start_time;
        }

        if(burst_remaining[idx]-tq > 0) {
            burst_remaining[idx] -= tq; //burst_remaining = burst_remanining - Quantum_time
            current_time += tq; //Current_time = Current_time + Quantum_time

            processName.push_back(p[idx].pid);
            processChangeTime.push_back(current_time);
        }
        
        // if burst_remaining[idx] <= 0 then calculate CT, TAT, WT, RT for the process
        else {
            current_time += burst_remaining[idx]; //current_time = current_time + burst_remaining[idx]
            burst_remaining[idx] = 0; //Mark the element 'False'
            completed++; //completed + 1

            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;

            processName.push_back(p[idx].pid);
            processChangeTime.push_back(current_time);
        }

        // If there are process with burst time remaining and arrival time <= current time 
        //and if the process is at a false index push the element into the running queue 
        for(int i = 1; i < n; i++) {
            if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1; //Mark the element 'True' 
            }
        }
        //if burst_remaining element at front of the queue is greater than 0 then push the element into the queue from the waiting queue
        if(burst_remaining[idx] > 0) {
            q.push(idx);
        }

        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    calculate_average(p,n);
    sort(p,p+n,compareID);
    print_table(p, n);
    printGantt(processName, processChangeTime);
    print_average(p, n);
    system("pause");
}

//Driver Program
int main(){

  int choice = 0;
  while(choice != 7) //exit
  {
    cout << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " | Main Menu                                                 |" << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " | Scheduling Algorithms:                                    |" << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " |   1. First Come First Serve                               |" << endl;
    cout << " |   2. Shortest Job First                                   |" << endl;
    cout << " |   3. Shortest Remaining Time First                        |" << endl;
    cout << " |   4. Priority Non Pre-emptive                             |" << endl;
    cout << " |   5. Priority Preemptive                                  |" << endl;
    cout << " |   6. Round Robin                                          |" << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " |   7. Exit                                                 |" << endl;
    cout << " +-----------------------------------------------------------+" << endl << endl;
  

    cout << " Your selection => ";
    cin >> choice;
    
    switch(choice)
    {
      case 1:
      FCFS();
      break;
      
      case 2:
      SJF();
      break;
      
      case 3:
      SRTF();
      break;
      
      case 4:
      NP_Priority();
      break;
      
      case 5:
      P_Priority();
      break;
      
      case 6:
      round_robin();
      break;
      
      case 7:
      cout << "Successfully exited the program. \n\n";
      cout << "Submitted by: Daksh Singh, Tushar Bafna, Arpan Shrivastava, Vatsal Aryan Bhatnagar, Prakash Aryan\n";
      cout << "B.Tech CS (AI) IV Sem, IInd Year\n";
      cout << "Department of Computer Science and Engineering\n";
      cout << "Poornima University, Jaipur\n\n\n";
      break;
    }
  }
}


