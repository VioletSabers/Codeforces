#include <bits/stdc++.h>
using namespace std;

const int N=3e5+5;
int lst[N];
int a[N];
int maxn[N], ans[N];

int main(){
    int T;
    scanf ("%d", &T);
    while (T--){
        int n;
        scanf ("%d", &n);
        ans[0]=1e9;
        for (int i=1; i<=n; i++){
            scanf ("%d", &a[i]);
            lst[a[i]]=maxn[a[i]]=0;
            ans[i]=1e9;
        }
        for (int i=1; i<=n; i++)
            maxn[a[i]]=max(maxn[a[i]], i-lst[a[i]]), lst[a[i]]=i;

        for (int i=1; i<=n; i++)
            if (lst[a[i]] != n+1)
                maxn[a[i]]=max(maxn[a[i]], n+1-lst[a[i]]), lst[a[i]]=n+1;

        for (int i=1; i<=n; i++)
            ans[maxn[a[i]]]=min(ans[maxn[a[i]]], a[i]);

        for (int i=1; i<=n; i++){
            ans[i]=min(ans[i-1], ans[i]);
            if (ans[i]==1e9) printf ("-1 ");
            else printf ("%d ", ans[i]);
        }
        printf ("\n");
    }
}
