/*----------------------------------------------
MMP MANAWADU
CO2206 Opearating Systems
Assignment 3
17/ENG/072
-----------------------------------------------*/

#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

//structure type to store the details of processes
struct process_info {
    int processID;
    int burstTime;
    int period;
    int timeRemaining;
    bool ready; //to check the status of the process
    int count = 0; //to calculate how many times the process has been executed
};

int gcd(int a, int b) //greatest common denominator used in calculating the lcm
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Returns LCM of array elements 
int findlcm(vector<int> arr, int n)
{
    // Initialize result 
    int ans = arr[0];

    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) / (gcd(arr[i], ans)));

    return ans;
}

bool cmp(process_info a, process_info b) { //compares the period of the processes (of type struct)
    return(a.period < b.period);
}


int main()
{
    vector<process_info> processes; //vector of processes
    int n; //stores the number of processes

    cout << "Enter the number of processes : " ;
    cin >> n;
    cout << endl << endl;
    vector<int> periodArray; //vector to store the periods in order to find the lcm 

    for (int i = 0; i < n; i++) //storing detailsof processes in to a vector array of type struct
    {
        process_info tmp;
        tmp.processID = i + 1; //stores the process ID

        cout << "Enter the burst time of the process " << i + 1 << "\t : ";
        cin >> tmp.burstTime;

        tmp.timeRemaining = tmp.burstTime; //initially equating the remaining time with the value of the burst time

        cout << "Enter period of the process "  << i + 1 << "\t\t :";
        cin >> tmp.period;

        tmp.ready = 1; //initially making the status of all the processes as ready

        processes.push_back(tmp); //including the stored detais of a particular process in to a vector

        periodArray.push_back(tmp.period); //adding the periods in to the period array to calculate the LCM

        cout << endl;

    }



    sort(processes.begin(), processes.end(), cmp); //sorting the processes based on the period (for priority)



    int lcm = findlcm(periodArray, n); 

    cout << "LCM : " << lcm << endl;

    for (int i = 0; i < lcm; i++) //the timeline is looped for the calculated value of LCM
    {
        if (i >= processes[0].period) //if the value of i is higher than the first period, then the details for other periods are uploaded
        {
            for (int j = 0; j < n; j++)
            {
                int tmp;
                tmp = i % processes[j].period; //checking whether the value of "i" is a multiple of a given period
                if (!tmp) //if the value of "i" is corresponding to a period then the process is renewed for the next period
                    processes[j].ready = 1;
            }
        }
        
        //considering a particular period
        for (int j = 0; j < n; j++) //iterating through the sorted processes 
        {
            if (processes[j].ready) //if the status of the process is 1, that is if its ready for execution
            {
                if (processes[j].timeRemaining) //if there is time remaining
                {
                    processes[j].timeRemaining--; //decrementing time of each corresponding process
                    if (!processes[j].timeRemaining) //if the time remianing is zoro
                    {
                        processes[j].ready = 0; //making the status of the processes in to the waiting stage
                        processes[j].timeRemaining = processes[j].burstTime;  //initializing the burst time again
                    }
                }
                cout << " " << i << "\t\tP" << processes[j].processID << endl; 
                processes[j].count++; //taking a count of process being executed
                break; //breaking for the next time segment of the timeline
            }
        }


    }

    bool sheduleChecker = 1; //to check whether the proces can be scheduled 

    for (int i = 0; i < n; i++) 
    {
        //checking whether the number of segments processes executed equal to the required amount needed to schedule the processes within the given deadline
        if (!(processes[i].count == (lcm * processes[i].burstTime / processes[i].period)))
        {
            sheduleChecker = 0; //if the above equation is not satisfied it depicts that the algorithm cannot be scheduled
        }
    }

    if (sheduleChecker)
    {
        cout << "\nGiven set of processes can be completed within the deadline";
    }
    else
    {
        cout << "\nGiven set of processes cannot be completed within the deadline";
    }

   
    system("PAUSE");
    return 0;
}

