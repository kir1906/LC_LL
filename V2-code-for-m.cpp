#include<iostream>
#include <algorithm>
#include<map>
#include<vector>
using namespace std;
    void compute(string s,vector<int>inp,vector<int>&outputs,int u)
    {
        int si=inp.size();
        if(s=="AND")
        {
            int y=outputs[inp[0]-1];
            for(int k=1;k<si;++k)
            y*=outputs[inp[k]-1];
            outputs[u]=y;
        }
        else if(s=="OR")
        {
            int y=outputs[inp[0]-1];
            for(int k=1;k<si;++k)
            y|=outputs[inp[k]-1];
            outputs[u]=y;
        }
        else if(s=="OR")
        {
            int y=outputs[inp[0]-1];
            for(int k=1;k<si;++k)
            y|=outputs[inp[k]-1];
            outputs[u]=y;
        }
        else if(s=="NAND")
        {
            int y=outputs[inp[0]-1];
            for(int k=1;k<si;++k)
            y*=outputs[inp[k]-1];
            outputs[u]=!y;
        }
        else if(s=="XOR")
        {
            int y=outputs[inp[0]-1];
            for(int k=1;k<si;++k)
            y^=outputs[inp[k]-1];
            outputs[u]=y;
        }
        else if(s=="XNOR")
        {
            int y=outputs[inp[0]-1];
            for(int k=1;k<si;++k)
            y^=outputs[inp[k]-1];
            outputs[u]=!y;
        }

    }
int main()
{
    cout<<"Enter the number of nodes"<<endl;
    int num,n;
    cin>>num;
    vector< vector<int> >cir(num);
    vector<int>outputs(num,-1);
    for(int j=0;j<num;++j)
    {
        cout<<"Path of Indiviual node"<<endl;
        cin>>n;
        for(int i=0;i<n;++i)
        {
        int x;
        cin>>x;
        cir[j].push_back(x);
        }
    }
    cout<<"Number of input nodes"<<endl;
    cin>>n;
    cout<<"enter inputs"<<endl;
    for(int j=0;j<n;++j)
    {
        int x;
        cin>>x;
        outputs[j]=x;
    }
    cout<<"Enter types of gate"<<endl;
    for(int j=n;j<num;++j)
    {
        cout<<j+1<<endl;
        string s;
        cin>>s;
        compute(s,cir[j],outputs,j);
    }
    int siz=outputs.size();
    for(int j=0;j<siz;++j)
    cout<<"Output of node "<<j+1<<" : "<<outputs[j]<<endl;
    cout<<endl;
    return 0;
}

/*
1 -> 1
2 -> 2
3 -> 3
4 -> 1,2
5 -> 2,3
6 -> 2,3
7 -> 5,6
8 -> 4,7
*/