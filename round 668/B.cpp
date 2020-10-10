#include <bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int to[2*N], nxt[2*N], lst[N], d[N];
int cnt;

void Add(int u, int v){
    cnt++, to[cnt]=v, nxt[cnt]=lst[u], lst[u]=cnt;
    cnt++, to[cnt]=u, nxt[cnt]=lst[v], lst[v]=cnt;
}

int node, maxn;
void dfs(int u, int fa, int dep){
    d[u]=dep;
    if (dep>maxn) node=u, maxn=dep;
    for (int k=lst[u]; k!=0; k=nxt[k]){
        int v=to[k];
        if (v==fa) continue;
        dfs(v, u, dep+1);
    }
}

int main(){
    int T;
    scanf ("%d", &T);
    while (T--){
        int n, a, b, da, db;
        scanf ("%d %d %d %d %d", &n, &a, &b, &da, &db);
        cnt=0;
        for (int i=1; i<=n; i++)
            lst[i]=0;
        for (int i=1; i<n; i++){
            int u,v;
            scanf ("%d %d", &u, &v);
            Add(u, v);
        }
        maxn=node=0;
        dfs(a, 0, 0);
        int root=node;
        if (d[b]<=da){
            printf ("Alice\n");
            continue;
        }
        maxn=node=0;
        dfs(root, 0, 0);
        int d=maxn;
        if(d<=2*da){
            printf ("Alice\n");
            continue;
        }
        if(2*da>=db){
            printf ("Alice\n");
            continue;
        }
        printf ("Bob\n");

    }
}
