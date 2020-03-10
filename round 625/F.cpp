#include <bits/stdc++.h>
using namespace std;

const int N=2e6+5;
int n;
long long a[N];
int tot;
long long p[N], used[N];

void Init()
{
    for (int i=2; i<=2e6; i++)
    {
        if (used[i]==0)
            p[++tot]=i;
        for (int j=1; j<=tot && p[j]*i<=2e6; j++)
        {
            used[p[j]*i]=1;
            if (i%p[j]==0) break;
        }
    }
}

long long ans=1e18;
long long f[N];
int total;

void Calc(long long x)
{
    long long anss=0;
    for (int i=1; i<=n; i++)
        if (a[i] < x)
            anss += x-a[i];
        else
            anss+=min(x-a[i]%x, a[i]%x);
    ans=min(ans, anss);
    //printf ("%lld %lld\n", x, anss);
}

void C(long long x)
{
    if (x==0) return ;
    total=0;
    for(int i=1; p[i]*p[i]<=x; i++)
    {
        if (x%p[i]==0) f[++total]=p[i];
        while (x%p[i]==0) x/=p[i];
    }
    if (x!=1)
        f[++total]=x;

    for (int k=1; k<=total; k++)
        Calc(f[k]);
}

long long rand_()
{
    return 1ll*rand()*65536 + rand();
}

int main()
{
    Init();
    scanf ("%d", &n);
    for (int i=1; i<=n; i++)
        scanf ("%lld", &a[i]);

    srand(time(0));
    for (int i=1; i<=20; i++)
    {
        int p=rand_()%n+1;
        C(a[p]-1);
        C(a[p]);
        C(a[p]+1);
    }
    printf ("%lld", ans);
}
