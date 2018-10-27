#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define infinit INT_MAX
using namespace std;

vector <int> sortare_topologica_bf(vector<pair<int,double> >*la,int *gin,int n)
{
    vector <int>sort_top;
    queue <int> c;
    int x,y,i;
    for(i=1;i<=n;i++)
        if(gin[i]==0)
        c.push(i);
    while(!c.empty())
    {
        x=c.front();
        c.pop();
        sort_top.push_back(x);
        for(i=0;i<la[x].size();i++)
        {
            y=la[x][i].first;
            gin[y]--;
            if(gin[y]==0)
                c.push(y);
        }
    }
    return sort_top;
}
void drum_minim_dag(vector <pair<int,double> >*la,int s,int *gin,int n)
{
    int *d=new int[n+1];
    int *tata=new int[n+1];
    int x,y;
    vector<int>sort_top=sortare_topologica_bf(la,gin,n);
    for(int i=1;i<=n;i++)
    {
        tata[i]=0;
        d[i]=infinit;
    }
    d[s]=0;
    cout<<"Ordinea topologica in care se calculeaza etichetele:";
    for(int i=0;i<sort_top.size();i++)
    {
        x=sort_top[i];
        cout<<x<<" ";
        for(int i=0;i<la[x].size();i++)
        {
            y=la[x][i].first;
            if(d[y]>d[x]+la[x][y].second)
                tata[y]=x;
        }
    }
    cout<<"Vectorul de tati:"<<endl;
    for(int i=1;i<=n;i++)
        cout<<tata[i]<<" ";
}

int main()
{
    ifstream f("graf.in");
    int m,n,x,y,c,i,j,s,mc;
    int *gin;
    vector<pair<int,double> >*la;
    f>>n>>m;
    gin=new int[n+1];
    la=new vector<pair<int,double> >[n+1];
    for(i=1;i<=n;i++)
        gin[i]=0;
    for(i=1;i<=m;i++)
    {
        f>>x>>y>>c;
        la[x].push_back(make_pair(y,c));
        gin[y]++;
    }
    f>>s;
    drum_minim_dag(la,s,gin,n);
    return 0;
}
