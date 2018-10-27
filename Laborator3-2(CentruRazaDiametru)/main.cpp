#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

void citire(int &n,int &m,vector <int> *&la,ifstream &f)
{
    f>>n>>m;
    la=new vector <int>[n+1];
    int i,x,y;
    for(i=1;i<=m;i++)
    {
        f>>x>>y;
        la[x].push_back(y);
        la[y].push_back(x);
    }
}
int BF(int s,int n,vector <int>*la,int *tata)
{
    int *viz=new int[n+1];
    int ultim=0;
    queue <int>c;
    tata[s]=0;
    viz[s]=1;
    c.push(s);
    while(!c.empty())
    {
        int x=c.front();
        ultim=x;
        c.pop();
        for(int i=0;i<la[x].size();i++)
        {
            int y=la[x][i];
            if(viz[y]==0)
            {
                viz[y]=1;
                tata[y]=x;
                c.push(y);
            }
        }
    }
    return ultim;
}

int main()
{
    vector<int>*la;
    int n,m,i,diam,u,v,r;
    int *tata;
    ifstream f("graf.in");
    citire(n,m,la,f);
    f.clear();
    tata=new int[n+1];
    u=BF(i,n,la,tata);
    v=BF(u,n,la,tata);
    diam=0;
    int x=v;
    while(x!=u)
    {
        diam++;
        x=tata[x];
    }
    r=(diam+1)/2;
    cout<<diam<<" "<<r;
    if(diam%2==0)
    {
        x=v;
        for(i=1;i<=r;i++)
        x=tata[x];
            cout<<x;
    }
    else
    {
        x=v;
        for(i=1;i<r;i++)
            x=tata[x];
        cout<<x<<" "<<tata[x];
    }
    return 0;
}
