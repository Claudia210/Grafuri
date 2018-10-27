#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#define infinit INT_MAX
using namespace std;

struct muchie
{
    int v1;
    int v2;
    int cost;
};

void Prim(int s,int &n,vector<muchie>&apcm,vector <pair <int,double> > *la)
{
    int *tata,*viz,v,u;
    double *d,cost_uv;
    d=new double[n+1];
    tata=new int[n+1];
    viz=new int[n+1];
    for(v=1;v<=n;v++)
    {
        d[v]=infinit;
        tata[v]=0;
        viz[v]=0;
    }
    d[s]=0;
    priority_queue <pair <double,int> > c;
    c.push({-d[s],s});
    while(!c.empty())
    {
        v=c.top().second;
        c.pop();
        viz[v]++;
        if(viz[v]==1)
        {cout<<v<<endl;
          for(int j=0;j<la[v].size();j++)
          {
              u=la[v][j].first;
              cost_uv=la[v][j].second;
              if(viz[u]==0)
              {
                  if(d[u]>cost_uv)
                  {
                  tata[u]=v;
                  d[u]=cost_uv;
                  c.push({-d[u],u});
                  cout<<u<<endl;
                  }

              }
           }}
    }
    for(int i=1;i<=n;i++)
       if(d[i]!=infinit)
       cout<<i<<" :"<<d[i]<<endl;
    else
        cout<<i<<" :inf"<<endl;
muchie *m;
m=new muchie[n+1];
for(v=1;v<=n;v++)
    if(tata[v]!=0)
{
    m[v].v1=v;
    m[v].v2=tata[v];
    m[v].cost=d[v];
    //cout<<m[v].v1<<" "<<m[v].v2<<"-"<<m[v].cost<<endl;
    apcm.push_back(m[v]);
}


}

int main()
{
    ifstream f("graf.in");
    int n,m,s,i,j,x,y,c,v;
    vector<pair <int,double> >*la;
    vector<muchie>apcm;
    f>>n>>m;
    la=new vector <pair <int,double> >[n+1];
    for(i=1;i<=m;i++)
    {
        f>>x>>y>>c;
        la[x].push_back(make_pair(y,c));
        la[y].push_back(make_pair(x,c));
    }
    for(i=1;i<=n;i++)
       {
        cout<<i<<":";
    for(j=0;j<la[i].size();j++)
        cout<<la[i][j].first<<" "<<la[i][j].second<<"   ";
    cout<<endl;}
    f.close();
    cin>>s;
    Prim(s,n,apcm,la);
    if(apcm.size()<n-1)
        cout<<"Graful nu e conex!";
    else
    {
        double cost=0;
        for(v=0;v<apcm.size();v++)
        {cout<<apcm[v].v1<<" "<<apcm[v].v2<<"-"<<apcm[v].cost<<endl;
            cost+=apcm[v].cost;}
            cout<<"Cost:"<<cost;

    }
    return 0;
}
