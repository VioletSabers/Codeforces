#include <bits/stdc++.h>
using namespace std;

const int N=1e4+5;
int T;
int tot, x[3*N], y[3*N], z[3*N];
int a[N];

void Add(int s, int t, int p){
    tot++;
    x[tot]=s;
    y[tot]=t;
    z[tot]=p;

    a[s] -= p*s;
    a[t] += p*s;

}

int main(){
    int T;
    scanf ("%d", &T);
    while (T--){
        int n;
        scanf ("%d", &n);
        int sum=0;
        for (int i=1; i<=n; i++)
            scanf ("%d", &a[i]), sum+=a[i];
        if (sum%n!=0){
            printf ("-1\n");
            continue;
        }
        sum/=n;
        tot=0;
        for (int i=2; i<=n; i++)
            if (a[i]%i==0)
                Add(i, 1, a[i]/i);
            else
                Add(1, i, i-a[i]%i), Add(i, 1, a[i]/i);

        for (int i=2; i<=n; i++)
            if (a[i]!=sum) Add(1, i, sum-a[i]);

        printf ("%d\n", tot);
        for (int i=1; i<=tot; i++)
            printf ("%d %d %d\n", x[i], y[i], z[i]);
    }
}
