#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int a[N], b[N];
const int K=1e6;
int p[2000000];
long long ans[N];

int main()
{
    int n;
    scanf ("%d", &n);
    for (int i=1; i<=n; i++)
    {
        scanf ("%d", &b[i]);
        a[i]=b[i]-i+K;
    }
    long long anss=0;
    for (int i=1; i<=n; i++)
    {
        if (p[a[i]] == 0) ans[i]=b[i];
        else ans[i] = ans[p[a[i]]] + b[i];
        p[a[i]]=i;
        anss=max(anss, ans[i]);
    }
    printf ("%lld", anss);

}
