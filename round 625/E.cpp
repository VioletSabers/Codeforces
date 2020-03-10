#include <bits/stdc++.h>
using namespace std;

const int N=5005;
int a[N];

int main()
{
    int n,m;
    scanf ("%d %d", &n, &m);
    int ans=0, i;
    for (i=1; i<=n; i++)
        if (ans+(i-1)/2 <= m)
        {
            ans+=(i-1)/2;
            a[i]=i;
        }
        else
            break;
    if (i==n+1 && ans!=m)
    {
        printf ("-1");
        return 0;
    }

    if (ans==m)
    {
        for (int j=i; j<=n; j++)
            a[j]=1e9-(n-j)*(a[i-1]+1);
    }
    else
    {
        a[i]=a[i-1]+a[i-2*(m-ans)];
        i++;
        for (int j=i; j<=n; j++)
            a[j]=1e9-(n-j)*(a[i-1]+1);
    }
    for (int i=1; i<=n; i++)
        printf ("%d " ,a[i]);
}
