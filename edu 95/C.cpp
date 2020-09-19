#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int T, n;
int a[N];
int f[N][2];

int main(){
    int T;
    scanf ("%d", &T);
    while (T--){
        scanf ("%d", &n);
        for (int i=1; i<=n; i++)
            scanf ("%d", &a[i]);
        f[0][0]=0;
        f[0][1]=1e9;
        for (int i=1; i<=n; i++){
            if (i!=1) f[i][0]=min(f[i-1][1], f[i-2][1]);
            else f[i][0]=f[i-1][1];

            if (i!=1) f[i][1]=min(f[i-1][0]+a[i], f[i-2][0]+a[i]+a[i-1]);
            else f[i][1]=f[i-1][0]+a[i];
        }
        printf ("%d\n", min(f[n][0], f[n][1]));
    }
}
