#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct process {
    int processID;
    int burstTime;
    int period;
    int timeRemaining;
    bool ready;
    int count=0;
};

int gcd(int a, int b)
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

    // ans contains LCM of arr[0], ..arr[i] 
    // after i'th iteration, 
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
        (gcd(arr[i], ans)));

    return ans;
}

bool cmp(process a, process b) {
    return(a.period < b.period);
}


int main()
{
    vector<process> processes;
    int n;
    cout << "Enter the number of processes"<<endl;
    cin >> n;
    
    vector<int> periodArray;

    for (int i = 0; i < n; i++) //storing details in to the vector array of process structure
    {
        process tmp;
        tmp.processID=i+1;
        cout << "Enter the burst time of the process    " << i+1 << ": ";
        cin >> tmp.burstTime;
        tmp.timeRemaining = tmp.burstTime;
        cout << "Enter period of the process            " << i+1 << ": ";
        cin >> tmp.period; 
        tmp.ready = 1;
        processes.push_back(tmp);
        periodArray.push_back(tmp.period);
        cout << endl;
        
    }

 

    sort(processes.begin(), processes.end(), cmp);



    int lcm= findlcm(periodArray,n);

    cout << "LCM : " <<lcm<<endl;

    for (int i = 0; i < lcm; i++)
    {
        if (i >= processes[0].period)
        {
            for (int j = 0; j < n; j++)
            {
                int tmp;
                tmp = i % processes[j].period;
                if (!tmp)
                    processes[j].ready = 1;
            }
        }

        for (int j = 0; j < n; j++)
        {
            if (processes[j].ready)
            {
                if (processes[j].timeRemaining)
                {
                    processes[j].timeRemaining--;
                    if (!processes[j].timeRemaining)   
                    {
                        processes[j].ready = 0;
                        processes[j].timeRemaining = processes[j].burstTime;
                    }
                }
                cout << " " << i << "\t\tP" << processes[j].processID << endl;
                processes[j].count++;
                break;
            }
        }


    }

    bool sheduleChecker=1;
    for (int i = 0; i < n; i++)
    {
        //cout << "Count of Process " << i << "\t\t" << processes[i].count << endl;
        if (!(processes[i].count == (lcm*processes[i].burstTime / processes[i].period)))
        {
            sheduleChecker = 0;
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

}

