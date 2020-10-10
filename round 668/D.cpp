#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
int p[N], ans[N], tot, num[N], n;
bool used[N];
vector<int>v[N];

int F(int p){
    if (p>n) return p-n;
    else return p+n;
}

int main(){
    scanf ("%d", &n);
    if (n%2==0){
        printf ("First\n");
        fflush(stdout);
        for (int i=1; i<=2*n; i++)
            p[i]=i%n+1;
        for (int i=1; i<=2*n; i++)
            printf ("%d ", p[i]);
        printf ("\n");
        fflush(stdout);
        printf ("0\n");
        fflush(stdout);
        return 0;
    }
    else{
        printf ("Second\n");
        fflush(stdout);
        for (int i=1; i<=2*n; i++){
            scanf ("%d", &p[i]);
            v[p[i]].push_back(i);
        }
        for (int i=1; i<=n; i++){
            int pos=i;
            while (used[pos]==0){
                if (!num[v[pos][1]%n]){
                    num[v[pos][1]%n]=1;
                    ans[++tot]=v[pos][1];
                    used[pos]=1;
                    pos=p[F(v[pos][1])];
                    continue;
                }
                if (!num[v[pos][0]%n]){
                    num[v[pos][0]%n]=1;
                    ans[++tot]=v[pos][0];
                    used[pos]=1;
                    pos=p[F(v[pos][0])];
                    continue;
                }
            }
        }
        int sum=0;
        for (int i=1; i<=n; i++)
            sum=(sum+ans[i])%(2*n);
        if (sum==0)
            for (int i=1; i<=n; i++)
                printf ("%d ", ans[i]);
        else
            for (int i=1; i<=n; i++)
                printf ("%d ", F(ans[i]));
        printf ("\n");
        fflush(stdout);
        printf ("0\n");
        fflush(stdout);

    }
}
