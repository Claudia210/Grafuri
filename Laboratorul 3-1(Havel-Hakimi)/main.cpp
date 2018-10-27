#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

struct varf
{
int eticheta;
int grad;
};

int comp(struct varf v1,struct varf v2)
{
    return v1.grad-v2.grad;
}
void afisare(int i,int n,varf *s)
{

    for(int j=i;j<=n;j++)
        cout<<s[j].grad<<" "<<s[j].eticheta<<endl;
}
int main()
{
    ifstream f("graf.in");
    int n,x,i;
    varf *s,v;
    vector<pair <int,int> >la;
    f>>n;
    int sum=0;
    s=new varf[n+1];
    for(i=1;i<=n;i++)
    {
        f>>x;
        v={i,x};
        s[i]=v;
        sum=sum+x;
    }

    f.close();
    if(sum%2==1)
        {cout<<"Secventa nu este grafica1!";
        return 0;}
    sort(s+1,s+n,comp);
    //afisare(1,n,s);
    if(s[1].grad>=n)
        {cout<<"Secventa nu este grafica2!";
        return 0;}
    i=1;
    while(s[i].grad>0)
    {
        for(int j=1;j<=s[i].grad;j++)
        {
            s[i+j].grad--;
            if(s[i+j].grad<0)
                {cout<"Secventa nu este grafica3!";return 0;}
            la.push_back(make_pair(s[i].eticheta,s[i+j].eticheta));
        }
        int k=i+s[i].grad;
        if(k+1<=n&&s[k+1].grad>s[k].grad)
        {
            int poz1=k-1;
            while(poz1>=1&&s[k].grad==s[poz1].grad)
                poz1--;
            poz1++;
            int poz2=k+2;
            while(poz2<=n&&s[k+1].grad==s[poz2].grad)
                poz2++;
            reverse(s+poz1,s+poz2);
        }
        s[i].grad=0;
        i++;
    }
    cout<<"Secventa grafica:";
    for(i=0;i<la.size();i++)
        cout<<la[i].first<<" "<<la[i].second<<endl;
    return 0;
}
