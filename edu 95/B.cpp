#include <bits/stdc++.h>
using namespace std;

const int N=105;
int a[N], l[N];
int q[N], cnt;

bool cmp(int a, int b){return a>b;}
int main(){
    int T;
    scanf ("%d", &T);
    while (T--){
        int n;
        cnt=0;
        scanf ("%d", &n);
        for (int i=1; i<=n; i++)
            scanf ("%d", &a[i]);
        for (int i=1; i<=n; i++){
            scanf ("%d", &l[i]);
            if (!l[i])
                q[++cnt]=a[i];
        }
        sort(q+1,q+1+cnt,cmp);
        int ans=0, sum=0;
        for (int i=1, j=0; i<=n; i++)
            if (!l[i]) printf ("%d ", q[++j]);
            else printf ("%d ", a[i]);
        printf ("\n");
    }
}
