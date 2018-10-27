#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct muchie
{
    int v1;
    int v2;
    double cost;
};
//Kruskal
void initializare(int v,int *tata,int *h)
{
    tata[v]=h[v]=0;
}
int reprez(int v,int *tata)
{
    while(tata[v]!=0)
        v=tata[v];
    return v;
}
void reuneste(int u,int v,int *tata,int *h)
{
    int ru,rv;
    ru=reprez(u,tata);
    rv=reprez(v,tata);
    if(h[ru]>h[rv])
        tata[rv]=ru;
    else
    {
        tata[ru]=rv;
        if(h[ru]==h[rv])
            h[rv]=h[rv]+1;
    }
}
int comp(muchie m1,muchie m2)
{
   if (m1.cost<m2.cost)
    return 1;
return 0;
}
void kruskal(int &n,int &m,muchie *&mc,vector <muchie>&apcm,ifstream &f,ofstream &g)
{
    f>>n>>m;
    int *tata,*h;
    tata=new int [n+1];
    h=new int [n+1];
    mc=new muchie[m];
    int v,i,u;
    for(v=1;v<=n;v++)
        initializare(v,tata,h);
    for(i=1;i<=m;i++)
        {f>>mc[i].v1>>mc[i].v2>>mc[i].cost;
        cout<<mc[i].v1<<" "<<mc[i].v2<<"-"<<mc[i].cost<<endl;}
        cout<<endl;
    sort(mc,mc+m+1,comp);
    for(i=1;i<=m;i++)
        cout<<mc[i].v1<<" "<<mc[i].v2<<"-"<<mc[i].cost<<endl;
    cout<<endl;
    int nrmuchii=0;
    for(i=1;i<=m;i++)
    {
      u=mc[i].v1;
      v=mc[i].v2;
      if(reprez(u,tata)!=reprez(v,tata))
      {
          apcm.push_back(mc[i]);
          reuneste(u,v,tata,h);
          nrmuchii++;
          if(nrmuchii==n-1)
            break;
      }
    }
}
void creare_lista(int &n,vector <muchie> &apcm,vector <int> *&la)
{
    int i,j;
    la=new vector <int>[n+1];
    for(i=0;i<n;i++)
    {
       int x=apcm[i].v1;
       int y=apcm[i].v2;
       la[x].push_back(y);
       la[y].push_back(x);
    }
for(i=1;i<=n;i++)
{cout<<i<<" :";
for( j=0;j<la[i].size();j++)
    cout<<la[i][j]<<" ";
cout<<endl;}
}
void DF(int x,vector<int> *la,int *tata,int *viz,ofstream &g)
{
    viz[x]=1;
    for(int i=0;i<la[x].size();i++)
    {
        int y=la[x][i];
        if(viz[y]==0)
        {
            tata[y]=x;
            DF(y,la,tata,viz,g);
        }
        else
            if(y!=tata[x])
        {
            cout<<"Ciclul format de muchia adaugata:";
            int v=x;
            while(v!=y)
            {
                cout<<v<<" ";
                v=tata[v];
            }
            cout<<y<<" "<<x<<endl;
        }
    }
}
int main()
{
   ifstream f("graf.in");
   ofstream g("graf.out");
   int n,m,i;
   muchie *mc;
   vector <muchie> apcm;
   kruskal(n,m,mc,apcm,f,g);
   if(apcm.size()<n-1)
        cout<<"Graful nu este conex";
   else
   {
       double cost=0;
       g<<"Muchiile arborelui partial de cost minim:"<<endl;
       for(i=0;i<apcm.size();i++)
       {
           g<<apcm[i].v1<<" "<<apcm[i].v2<<" - "<<apcm[i].cost<<endl;
           cost+=apcm[i].cost;
       }
       g<<"Cost total:"<<cost;

   }
   f.close();
   g.close();
   muchie much;
   cin>>much.v1>>much.v2>>much.cost;
   apcm.push_back(much);
for(i=0;i<apcm.size();i++)
       {
           cout<<apcm[i].v1<<" "<<apcm[i].v2<<" - "<<apcm[i].cost<<endl;
           //cost+=apcm[i].cost;
       }
   vector<int> *la;
   //la=new vector<int>[n+1];
   creare_lista(n,apcm,la);
int *viz=new int [n+1];
int *tata=new int [n+1];
DF(much.v1,la,tata,viz,g);
    return 0;
}
