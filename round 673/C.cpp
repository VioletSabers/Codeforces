#include <bits/stdc++.h>
using namespace std;

const int N=3e5+5;
struct Tr{
    int nxt[2];
    int cnt;
}tr[30*N];
int tot=1;
long long ans0[35], ans1[35];
int a[N];

void Add(int x){
    int now=1;
    for (int i=30; i>=0; i--){

        int p=(x>>i)&1;
        if (tr[now].nxt[p]==0)
            tr[now].nxt[p]=++tot;

        if (p==0)
            ans0[i]+=tr[tr[now].nxt[1]].cnt;
        else
            ans1[i]+=tr[tr[now].nxt[0]].cnt;

        now=tr[now].nxt[p];
        tr[now].cnt++;
    }
}

int main(){
    int n;
    scanf ("%d", &n);
    for (int i=1; i<=n; i++)
        scanf ("%d", &a[i]);
    for (int i=1; i<=n; i++)
        Add(a[i]);

    int ans=0;
    long long anss=0;
    for (int i=30; i>=0; i--)
        if (ans0[i]>ans1[i]) ans+=1<<i, anss+=ans1[i];
        else anss+=ans0[i];
    printf ("%lld %d\n", anss, ans);
}
