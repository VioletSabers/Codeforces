#include <bits/stdc++.h>
using namespace std;

const int mod=998244353;
const int N=2e5+5;
int n, m;
int a[N], b[N], d[N];
long long sum[N];

long long Pow(long long a, int b){
    long long ans=1;
    while (b){
        if (b&1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return ans;
}

int Find(int x){
    int l=0, r=n;
    while (l<r){
        int mid=(l+r+1)>>1;
        if (d[mid]<x) l=mid;
        else r=mid-1;
    }
    return l;
}

int main(){
    scanf ("%d %d", &n, &m);
    for (int i=1; i<=n; i++)
        scanf ("%d", &d[i]);
    for (int i=1; i<=m; i++)
        scanf ("%d %d", &a[i], &b[i]);
    sort(d+1, d+1+n);
    for (int i=1; i<=n; i++)
        sum[i]=(sum[i-1]+d[i]) % mod;

    for (int i=1; i<=m; i++){
        int pos = Find(b[i]);
        //printf ("[%d]\n", pos);
        int num=n-pos;
        if (num < a[i]){
            printf ("0\n");
            continue;
        }
        long long ans;
        ans = sum[pos] * Pow(num+1, mod-2) % mod * (num+1-a[i]) % mod;
        ans = (ans + (sum[n]-sum[pos]) * Pow(num, mod-2) % mod * (num-a[i]) % mod) % mod;
        printf ("%lld\n", (ans+mod)%mod);
    }
}
