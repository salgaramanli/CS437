#include <iostream>
#define Max 50
using namespace std;

struct Node
    {
        char ch;  //Letter
        int arv;  //Arrival Time
        int run;  //Run Time
        int rem;  //Remaining Time
        int exe;  //Execution Time
        int fin;  //Finish Time
        int tat;  //Turnaround Time
        int wait; //Waiting Time
    };
int n ,Now = 0  ,index ,minimum;
string order;
Node SJF[Max];
bool RemainingTimeIsZero()
{
    for(int i=0 ;i<n; i++)
        if(SJF[i].rem != 0)
            return 1;
    return 0;
}
void sorting()
{
    Node temp;
    for(int i=0 ; i<n ; i++)
    {
        for(int j=i ; j<n ; j++)
        {
            if(SJF[i].arv > SJF[j].arv)
            {
                temp = SJF[j];
                SJF[j] = SJF[i];
                SJF[i] = temp;
            }
        }
    }
}
void SRTF()
{
    order="";
    Now = 0;
    sorting();
    while( RemainingTimeIsZero() )
    {
        index=-1;
        minimum = 0;
        for(int i=0; i<=n ;i++)
        {
            if(SJF[i].rem != 0  && SJF[i].arv <= Now)
            {
                if(minimum > SJF[i].rem || minimum == 0 )
                {
                    minimum = SJF[i].rem;
                    index = i;
                }
            }
        }
        if( index == -1)
        {
            cout<<"now"<<endl;
            Now++;
        }
        else
        {
            order += SJF[index].ch;
            SJF[index].rem --;
            Now ++;
            SJF[index].fin = Now;
        }
    }
    //for Turnaround Time
    for(int i=0;i<n;i++)
    {
        SJF[i].tat = SJF[i].fin - SJF[i].arv ;
    }
    //for waiting time
    float sum = 0;
    for(int i=0;i<n;i++)
    {
        SJF[i].wait = SJF[i].tat - SJF[i].run;
        cout<<"wait time for "<<SJF[i].ch<<" : "<<SJF[i].wait<<endl;
        sum += SJF[i].wait;
    }
    cout<<"Avrege time is : "<<sum <<" / "<<n<<" = "<<sum/n<<endl<<endl;
    //print
    cout<<"\tArv\tRun\tRem\tFin\tTAT\tWait "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<SJF[i].ch<<"\t"<<SJF[i].arv<<"\t"<<SJF[i].run<<"\t"<<SJF[i].rem<<"\t"<<SJF[i].fin<<"\t"<<SJF[i].tat<<"\t"<<SJF[i].wait<<endl;
    }
    cout<<"Time now : "<<Now<<endl<<endl;
    cout<<"order  is : "<<order<<endl;
    cout<<"-----------------------------"<<endl;
}
bool ExecutionNotEmpty()
{
    for(int i=0 ;i<n; i++)
        if(SJF[i].exe == -1)
            return 1;
    return 0;
}
void SJF_()
{
    order="";
    Now = 0;
    sorting();
    while( ExecutionNotEmpty() )
    {
        minimum = 0;
        index = 0;
        for(int i=0; i<=n ;i++)
        {
            if(SJF[i].exe == -1  && SJF[i].arv <= Now)
            {
                if(minimum > SJF[i].run || minimum == 0 )
                {
                    minimum = SJF[i].run;
                    index = i;
                }
            }
        }
        if(minimum == 0)
        {
            Now++;
        }
        else
        {
            order += SJF[index].ch;
            SJF[index].exe = Now;
            Now += SJF[index].run;
        }
    }
//for waiting time
    float sum = 0;
    for(int i=0;i<n;i++)
    {
        SJF[i].wait = SJF[i].exe - SJF[i].arv;
        cout<<"wait time for "<<SJF[i].ch<<" : "<<SJF[i].wait<<endl;
        sum += SJF[i].wait;
    }
    cout<<"Avrege time is : "<<sum <<" / "<<n<<" = "<<sum/n<<endl<<endl;
//print
    cout<<"\tArv\tRun\tExe\twait "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<SJF[i].ch<<"\t"<<SJF[i].arv<<"\t"<<SJF[i].run<<"\t"<<SJF[i].exe<<"\t"<<SJF[i].wait<<endl;
    }
    cout<<"Time now : "<<Now<<endl<<endl;
    cout<<"order  is : "<<order<<endl;
    cout<<"-----------------------------"<<endl;
}
int main()
{
    cout<<"Enter Number of operations : ";
    cin>>n;
    cout<<endl<<"-----------------------------"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter Letter of Job : ";
        cin>>SJF[i].ch;
        cout<<"Enter Arrival Time of Job : ";
        cin>>SJF[i].arv;
        cout<<"Enter Run Time of Job : ";
        cin>>SJF[i].run;
        SJF[i].rem = SJF[i].run ;
        SJF[i].exe = -1;
        SJF[i].fin = 0;
        SJF[i].wait = 0;
        SJF[i].tat = 0;
        cout<<"-----------------------------"<<endl;
    }
/*
    n=4;
    //--------------------
    SJF[0].ch = 'A';
    SJF[0].arv = 0;
    SJF[0].run = 9;
    SJF[0].rem = SJF[0].run;
    SJF[0].exe = -1;
    SJF[0].fin = 0;
    SJF[0].wait = 0;
    SJF[0].tat = 0;
    //--------------------
    SJF[1].ch = 'B';
    SJF[1].arv = 2;
    SJF[1].run = 3;
    SJF[1].rem = SJF[1].run;
    SJF[1].exe = -1;
    SJF[1].fin = 0;
    SJF[1].wait = 0;
    SJF[1].tat = 0;
    //--------------------
    SJF[2].ch = 'C';
    SJF[2].arv = 3;
    SJF[2].run = 1;
    SJF[2].rem = SJF[2].run;
    SJF[2].exe = -1;
    SJF[2].fin = 0;
    SJF[2].wait = 0;
    SJF[2].tat = 0;
    //--------------------
    SJF[3].ch = 'D';
    SJF[3].arv = 4;
    SJF[3].run = 3;
    SJF[3].rem = SJF[3].run;
    SJF[3].exe = -1;
    SJF[3].fin = 0;
    SJF[3].wait = 0;
    SJF[3].tat = 0;
*/
    //print
    cout<<"\tArv\tRun "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<SJF[i].ch<<"\t"<<SJF[i].arv<<"\t"<<SJF[i].run<<endl;
    }
    cout<<"Time now : "<<Now<<endl<<endl;
    int flag=0;
    while(flag !=3)
    {
        cout<<"if you want  SJF non_preemptive press 1   /   SJF preemptive press 2  : ";
        cin>>flag;
        cout<<endl;
        if (flag == 1)
            SJF_();
        else if(flag == 2)
            SRTF();
        for(int i=0;i<n;i++)
        {
            SJF[i].rem = SJF[i].run ;
            SJF[i].exe = -1;
            SJF[i].fin = 0;
            SJF[i].wait = 0;
            SJF[i].tat = 0;
        }
    }
    return 0;
}
