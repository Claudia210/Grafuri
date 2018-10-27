#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#define infinit INT_MAX

using namespace std;

void citire(int &n,vector <pair<int,double> >*&la,int &k,int *&control,ifstream &f)
{
    int m,v,u,cost,i;
    f>>n>>m;
    la=new vector <pair<int,double> >[n+1];

    for(i=1;i<=m;i++)
    {
        f>>v>>u>>cost;
        la[v].push_back(make_pair(u,cost));
        la[u].push_back(make_pair(v,cost));
    }
    for(v=1;v<=n;v++)
    {
        cout<<v<<":";
        for(u=0;u<la[v].size();u++)
            cout<<la[v][u].first<<"-"<<la[v][u].second<<" ";
        cout<<endl;

    }
      f>>k;
    control=new int [n+1];
    for(v=1;v<=n;v++)
        control[v]=0;
    for(v=1;v<=k;v++)
    {
        f>>u;
        control[u]=1;
    }
}
int Dijkstra(int s,int n,vector <pair <int,double> >*la,int *tata,int *control,ifstream &f)
{

    int *viz,*d;
    int dist_uv,u,v,i;
    viz=new int [n+1];
    tata=new int [n+1];
    d=new int [n+1];
    for(v=1;v<=n;v++)
    {
        tata[v]=0;
        viz[v]=0;
        d[v]=infinit;
    }

    d[s]=0;
    viz[s]=1;
    if(control[s]==1)
        return s;
    priority_queue <pair <double,int> >c;
    c.push({-d[s],s});
    while(!c.empty())
    {
        v=c.top().second;
        //cout<<v<<" ";
        c.pop();
for(i=0;i<la[v].size();i++)
        {
          u=la[v][i].first;
          dist_uv=la[v][i].second;
          //cout<<u<<" "<<dist_uv<<" ";


          if(viz[u]==0)
          {
              if(d[v]+dist_uv<d[u])
              {
                  d[u]=d[v]+dist_uv;
                  tata[u]=v;
                  viz[u]=1;
          cout<<d[u]<<" ";
                  if(control[u]==1)

                    return u;

                    c.push(make_pair(d[u],u));

              }
          }
        }
    }
    return -1;
}
void afisare_drum(int v,int*tata)
{
    while(v!=0)
        {v=tata[v];
    cout<<v<<" ";}
}

int main()
{
    int n,v,s,*tata,k,*control;
    vector<pair <int,double> >*la;
    ifstream f("graf.in");
    citire(n,la,k,control,f);
    cin>>s;
    v=Dijkstra(s,n,la,tata,control,f);
    cout<<v;
    if(v==-1)
        cout<<"Nu exista drum!";
    else
        afisare_drum(v,tata);
    return 0;
}
