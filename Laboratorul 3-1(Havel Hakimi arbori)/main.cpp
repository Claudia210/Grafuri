#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
using namespace std;
struct varf
{
    int eticheta;
    int grad;
};

int main()
{
    int n,sum,i,x;
    varf v;
    queue <varf> T;
    queue <varf> NT;
    ifstream f("graf.in");
    f>>n;
    sum=0;
    for(i=1;i<=n;i++)
    {
        f>>x;
        if(x<=0)
        {
            cout<<"Segventa nu e arborescenta!";
            return 0;
        }
        sum=sum+x;
        v={i,x};
        if(x==1)
            T.push(v);
        else
            NT.push(v);
    }
    if(sum!=2*(n-1))
    {
        cout<"Segventa nu e arborescenta!";
        return 0;
    }
    while(!NT.empty())
    {
        cout<<T.front().eticheta<<" "<<NT.front().eticheta<<endl;
        T.pop();
        NT.front().grad--;
        if(NT.front().grad==1)
        {
            T.push(NT.front());
            NT.pop();
        }
    }
    varf v1,v2;
    v1=T.front();
    T.pop();
    v2=T.front();
    T.pop();
    cout<<v1.eticheta<<" "<<v2.eticheta;
    return 0;
}
