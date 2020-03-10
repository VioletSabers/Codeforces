#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n;
char s[N];
int tot, a[N];
int p1[N], p2[N];
const int mod1 = 1e9+7, mod2 = 998244353;

long long f[N], g[N];
long long pow1[N], pow2[N];
long long b1[N], b2[N];
int sum[N];

long long calc(int x, int y)
{
    return ((f[y] - f[x-1]*pow1[y-x+1])%mod1 + mod1) % mod1;
}

long long CALC(int x, int y)
{
    return ((g[y] - g[x-1]*pow2[y-x+1])%mod2 + mod2) % mod2;
}

bool check(int s, int t, int ss, int tt, bool flag)
{
    if (flag)
        if (calc(s, t) == calc(ss, tt) && CALC(s, t) == CALC(ss, tt))
            return 1;
        else return 0;
    else
        if (calc(s, t) == ((b1[t-s+1] - calc(ss, tt))+mod1)%mod1 && CALC(s, t) == ((b2[t-s+1] - CALC(ss, tt))+mod2)%mod2)
            return 1;
        else return 0;
}

int main()
{
    scanf ("%d", &n);
    scanf ("%s", s+1);
    int num1=0;
    for (int i=1; i<=n; i++)
        if (s[i]=='0')
        {
            a[++tot]=num1%2;
            p1[i]=tot;
            p2[i]=tot;
            sum[i] = sum[i-1];
        }
        else
        {
            p1[i]=tot+1;
            p2[i]=tot;
            num1++;
            sum[i] = sum[i-1]+1;
        }
    pow1[0] = pow2[0] = 1;
    b1[0] = 0; b2[0] = 0;
    for (int i=1; i<N; i++)
    {
        pow1[i] = (pow1[i-1]*3) % mod1;
        pow2[i] = (pow2[i-1]*3) % mod2;
        b1[i] = ((b1[i-1] + 1)*3) % mod1;
        b2[i] = ((b2[i-1] + 1)*3) % mod2;
    }

    f[0]=0; g[0]=0;
    for (int i=1; i<=tot; i++)
    {
        f[i] = (f[i-1]*3 + a[i] + 1) % mod1;
        g[i] = (g[i-1]*3 + a[i] + 1) % mod2;
    }


    int q;
    scanf ("%d", &q);
    while (q--)
    {
        int l1, l2, len;
        scanf ("%d %d %d", &l1, &l2, &len);
        int s1, t1, s2, t2;
        s1=p1[l1], s2=p1[l2];
        t1=p2[l1+len-1], t2=p2[l2+len-1];
        if (s2-s1!=t2-t1)
        {
            printf ("NO\n");
            continue;
        }
        bool flag;
        if (sum[l1-1]%2 == sum[l2-1]%2)
            flag=1;
        else
            flag=0;
        if (check(s1, t1, s2, t2, flag))
            puts("YES");
        else
            puts("NO");
    }
}
