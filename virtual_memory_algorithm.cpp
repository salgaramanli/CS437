#include <iostream>
#include <queue>
#include <string>


using namespace std;
struct Node
{
    char ch;
    int counter =0;
};

void printOrder(char o[],int m)
{

    for(int i=0; i<m;i++)
    {

        cout<<o[i]<<"";
    }
    cout<<endl;
}


int WhatIndexInRAM(int k ,Node x [],char c)//if return -1 is not in RAM  - if return i is in RAM and his index in RAM is i
{
    for(int i=0;i<k;i++)
    {
        if(x[i].ch == c)
        {
            return i;
        }
    }
    return -1;
}
int SearchInOrder(char order[] ,int p ,Node ram[] ,int n ,int min_index)
{
    int swiched_item = 0;
    for(int i=p-1;i>=0;i--)
    {
        int index = WhatIndexInRAM(n,ram,order[i]);
        if(index == -1)
        {

            swiched_item = i+1;
            break;
        }
    }
    for(int i=swiched_item ;i<p; i++)
    {
        int index = WhatIndexInRAM(n,ram,order[i]);
        if( ram[index].counter == ram[min_index].counter )
        {
            return index;
        }
    }
    return 0;
}
int GetIndexOfMinCount( Node x[] , int k)//it is return low counter in your RAM
{
    int minum , index=0;
    minum = x[0].counter;
    for(int i=1;i<k;i++)
    {

        if(minum > x[i].counter)
        {
            minum = x[i].counter;
            index = i;
        }
    }
    return index;
}
int GetIndexOfMaxCount( Node x[] , int k)//it is return most counter in your RAM
{
    int maxum , index=0;
    maxum = x[0].counter;
    for(int i=1;i<k;i++)
    {
        if(maxum < x[i].counter)
        {
            maxum = x[i].counter;
            index = i;
        }
    }
    return index;
}
bool EqualCounterInRAM(int minv  ,Node x[] ,int k,int p, char order[])
{
    int minn;
    for(int i=0;i<k;i++)
    {
        if(minv == x[i].counter)
        {
            return 1;
        }
    }
    return 0;
}


int ReturnFirstProcess(char order[] ,Node ram[] ,int p ,int n ,int k)
{
    int z=0;
    for(int i=0;i<n;i++)
    {
        ram[i].counter = 0;
    }
    for(int i=p-1;i>=0;i--)
    {
      int index ;
      index = WhatIndexInRAM(k,ram,order[i]);
      //cout<<endl<<"z :"<<z<<endl<<"index :"<<index<<endl<<endl;
      if(ram[index].counter != 1)
      {
          z++;
          ram[index].counter = 1;
      }
      if(z == n)
      {
          //cout<<endl<<endl<<"********************** index :"<<index<<endl<<endl;
          return index;
      }
    }
    return -1;
}

int ReturnLastProcess(char order[] ,Node ram[] ,int p ,int n ,int k)
{
    for(int i=p-1;i>=0;i--)
    {
      int index ;
      index = WhatIndexInRAM(k,ram,order[i]);
      return index;
    }
    return -1;
}


int SearchItem(char order[] ,Node ram[] ,int p ,int n ,int k ,int m) //Search for the items in the ram, are you in the order?
{


    for(int index=0;index<n;index++)
    {
        int flag =0 ;
        for(int i=p+1;i<m;i++)
        {
            if(ram[index].ch == order [i])
            {
                flag=1;
                ram[index].counter = i;
                break;
            }
        }
        if(flag == 0)
        {
            for(int i=p-1;i>0;i--)
            {
                if(ram[index].ch == order [i])
                {
                    ram[index].counter = i;
                    break;
                }
            }
        }
    }

        int tmin ,tmax;
        tmin=tmax= ram[0].counter;
        for(int i=1;i<n;i++)
        {
            if( tmin > ram[i].counter)
            {
                tmin = ram[i].counter;
            }
            if( tmax < ram[i].counter)
            {
                tmax = ram[i].counter;
            }
        }
        if(tmin<p)
        {
            return WhatIndexInRAM(n,ram,order[tmin]);
        }
        else
        {
            return WhatIndexInRAM(n,ram,order[tmax]);
        }

}


int main()
{
    int n=3 ,m= 12 ;   //13 ;                     //m=18;                      //m=13;                     //m=17;                             //m=15 ;
    char order[m]="ABACDBRADABR";  //"7012030423032";      //"ABABTRMARTFBAFRMRA" ;     //"FMSTFTMSFFTHX";          //"01120403401245450";              //"701203042303212";
    Node ram[n];


/*
    cout<<"Enter number of partitions for RAM : ";
    cin>>n;

    cout<<"Enter number of characters : ";
    cin>>m;

    for(int i=0;i<m;i++)
    {
        cout<<"letter "<<i+1<<" : ";
        cin>>order[i];
    }
*/


    int algorithm;
    do                                                          //**********************************

    {
        for(int i=0;i<n;i++)
        {
            ram[i].ch = ' ';
            ram[i].counter = 0;
        }
        int hit=0 ,fault=0,k=0 ,index ,min_index ,max_index , flag=0;

        cout<<"Enter Number for algorithm :  ";
        cout<<"1 for  LFU   \t";
        //cout<<"2 for  MFU   \t";
        cout<<"3 for  LRU   \t";
        cout<<"4 for  MRU   \t";
        cout<<"5 for  OPT   "<<endl;
        cout<<"Enter 0 for  Exit "<<endl;
        cout<<"your algorithm is : ";cin>>algorithm;cout<<endl;
        if(algorithm == 1)
        {
            cout<<endl<<" *** LFU *** "<<endl<<endl;
            for(int i=0;i<m;i++)
            {
                if(k<n)
                {
                    index =WhatIndexInRAM ( k, ram, order[i] );//The index that we replace is returned
                    if( index == -1 )
                    {
                        ram[k].ch = order[i];
                        ram[k].counter ++;
                        fault ++;
                        k ++;
                        cout<<"fault "<<endl;
                    }
                    else
                    {
                        ram[index].counter++;
                        hit++;
                        cout<<"hit"<<endl;
                    }
                }
                else
                {
                    index =WhatIndexInRAM ( k, ram, order[i] );
                    if(index == -1)
                    {
                        min_index = GetIndexOfMinCount(ram , k);

                        flag = EqualCounterInRAM(ram[min_index].counter ,ram ,k,i,order);
                        if(flag ==1)
                        {
                            min_index = SearchInOrder(order,i,ram,n,min_index);
                        }
                        ram[min_index].ch = order[i];
                        ram[min_index].counter=1 ;
                        fault++ ;
                        cout<<"fault"<<endl;

                    }
                    else
                    {
                        ram[index].counter++;
                        hit++;
                        cout<<"hit "<<endl;
                    }
                }
                cout<<"I : "<<i+1<<"\t\t"<<order[i]<<" --> in RAM "<<endl;
                for(int j=0;j<n;j++)
                {
                    cout<<"RAM : "<<ram[j].ch<<" -->"<<ram[j].counter<<endl;
                }
                cout<<"***************"<<endl<<endl;
            }
            cout<<endl<<"-----------------------------------------"<<endl;
            cout<<"fault : "<<fault<<"\t";
            cout<<"hit : "<<hit<<endl;
            cout<<"-----------------------------------------"<<endl;
            //LFU();
        }
        else if(algorithm == 2)
        {
            cout<<"* MFU *"<<endl;
            for(int i=0;i<m;i++)
            {
                if(k<n)
                {
                    index =WhatIndexInRAM ( k, ram, order[i] );//The index that we replace is returned
                    if( index == -1 )
                    {
                        ram[k].ch = order[i];
                        ram[k].counter ++;
                        fault ++;
                        k ++;
                        cout<<"fault "<<endl;
                    }
                    else
                    {
                        ram[index].counter++;
                        hit++;
                        cout<<"hit"<<endl;
                    }
                }
                else
                {
                    index =WhatIndexInRAM ( k, ram, order[i] );
                    if(index == -1)
                    {
                        max_index = GetIndexOfMaxCount(ram , k);

                        flag = EqualCounterInRAM(ram[max_index].counter ,ram ,k,i,order);
                        if(flag ==1)
                        {
                            max_index = SearchInOrder(order,i,ram,n,max_index);
                        }
                        ram[max_index].ch = order[i];
                        ram[max_index].counter=1 ;
                        fault++ ;
                        cout<<"fault"<<endl;

                    }
                    else
                    {
                        ram[index].counter++;
                        hit++;
                        cout<<"hit "<<endl;
                    }
                }
                cout<<"I : "<<i+1<<"\t\t"<<order[i]<<" --> in RAM "<<endl;
                for(int j=0;j<n;j++)
                {
                    cout<<"RAM : "<<ram[j].ch<<" -->"<<ram[j].counter<<endl;
                }
                cout<<"***************"<<endl<<endl;
            }
            cout<<endl<<"-----------------------------------------"<<endl;
            cout<<"fault : "<<fault<<"\t";
            cout<<"hit : "<<hit<<endl;
            cout<<"-----------------------------------------"<<endl;
            //MFU();
        }
        else if(algorithm == 3)
        {
            cout<<"* LRU *"<<endl;
            for(int i=0;i<m;i++)
            {
                if(k<n)
                {
                    index =WhatIndexInRAM ( k, ram, order[i] );//The index that we replace is returned
                    if( index == -1 )
                    {
                        ram[k].ch = order[i];
                        fault ++;
                        k ++;
                        cout<<"fault "<<endl;
                    }
                    else
                    {
                        hit++;
                        cout<<"hit"<<endl;
                    }
                }
                else
                {
                    int victim;
                    index =WhatIndexInRAM ( k, ram, order[i] );
                    if(index == -1)
                    {

                        victim = ReturnFirstProcess(order,ram,i,n,k);
                        ram[victim].ch = order[i];
                        fault++ ;
                        cout<<"fault"<<endl;
                    }
                    else
                    {
                        hit++;
                        cout<<"hit "<<endl;
                    }
                }
                cout<<"I : "<<i+1<<"\t\t"<<order[i]<<" --> in RAM "<<endl;
                for(int j=0;j<n;j++)
                {
                    cout<<"RAM : "<<ram[j].ch<<" -->"<<ram[j].counter<<endl;
                }
                cout<<"***************"<<endl<<endl;
            }
            cout<<endl<<"-----------------------------------------"<<endl;
            cout<<"fault : "<<fault<<"\t";
            cout<<"hit : "<<hit<<endl;
            cout<<"-----------------------------------------"<<endl;
            //LRU();
        }
        else if(algorithm == 4)
        {
            cout<<"* MRU *"<<endl;
            for(int i=0;i<m;i++)
            {
                if(k<n)
                {
                    index =WhatIndexInRAM ( k, ram, order[i] );//The index that we replace is returned
                    if( index == -1 )
                    {
                        ram[k].ch = order[i];
                        fault ++;
                        k ++;
                        cout<<"fault "<<endl;
                    }
                    else
                    {
                        hit++;
                        cout<<"hit"<<endl;
                    }
                }
                else
                {
                    int victim;
                    index =WhatIndexInRAM ( k, ram, order[i] );
                    if(index == -1)
                    {

                        victim = ReturnLastProcess(order,ram,i,n,k);
                        ram[victim].ch = order[i];
                        fault++ ;
                        cout<<"fault"<<endl;
                    }
                    else
                    {
                        hit++;
                        cout<<"hit "<<endl;
                    }
                }
                cout<<"I : "<<i+1<<"\t\t"<<order[i]<<" --> in RAM "<<endl;
                for(int j=0;j<n;j++)
                {
                    cout<<"RAM : "<<ram[j].ch<<" -->"<<ram[j].counter<<endl;
                }
                cout<<"***************"<<endl<<endl;
            }
            cout<<endl<<"-----------------------------------------"<<endl;
            cout<<"fault : "<<fault<<"\t";
            cout<<"hit : "<<hit<<endl;
            cout<<"-----------------------------------------"<<endl;
            //MRU();
        }
        else if(algorithm == 5)
        {
            cout<<"* OPT *"<<endl;
            for(int i=0;i<m;i++)
            {
                if(k<n)
                {
                    index =WhatIndexInRAM ( k, ram, order[i] );//The index that we replace is returned
                    if( index == -1 )
                    {
                        ram[k].ch = order[i];
                        fault ++;
                        k ++;
                        cout<<"fault "<<endl;
                    }
                    else
                    {
                        hit++;
                        cout<<"hit"<<endl;
                    }
                }
                else
                {

                    int victim;
                    index =WhatIndexInRAM ( k, ram, order[i] );
                    if(index == -1)
                    {

                        victim = SearchItem(order,ram,i,n,k,m);
                        //cout<<"victim :"<<victim<<"     i:"<<i<<"   order[i]:"<<order[i]<<endl;
                        ram[victim].ch = order[i];

                        fault++ ;
                        cout<<"fault"<<endl;

                    }
                    else
                    {
                        hit++;
                        cout<<"hit "<<endl;

                    }

                }
                cout<<"I : "<<i+1<<"\t\t"<<order[i]<<" --> in RAM "<<endl;
                for(int j=0;j<n;j++)
                {
                    cout<<"RAM : "<<ram[j].ch<<" -->"<<ram[j].counter<<endl;
                }
                cout<<"***************"<<endl<<endl;
            }
            cout<<endl<<"-----------------------------------------"<<endl;
            cout<<"fault : "<<fault<<"\t";
            cout<<"hit : "<<hit<<endl;
            cout<<"-----------------------------------------"<<endl;
            //OPT();
        }cout<<endl;
    }while(algorithm != 0);




    return 0;
}

