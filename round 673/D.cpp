#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5;
const int M=3e5+5;
const int Q=5e5+5;
int n,m,q;
int u[M], v[M], p[N];
int type[Q], pos[Q];
int del[M];
int fa[3*N], tot;
int lc[3*N], rc[3*N];
int s[3*N], t[3*N], total, a[3*N], w[3*N];
struct Tree{
    int l, r;
    int maxn;
}tr[12*N];

int Find(int k){
    if (k==fa[k]) return k;
    else return fa[k]=Find(fa[k]);
}

void Combine(int u, int v){
    int x=Find(u), y=Find(v);
    if (x==y) return ;
    tot++;
    fa[x]=fa[y]=tot;
    lc[tot]=x;
    rc[tot]=y;
}

void dfs(int u){
    s[u]=++total;
    if (u<=n) a[total]=p[u], w[p[u]]=total;
    if (lc[u]!=0) dfs(lc[u]);
    if (rc[u]!=0) dfs(rc[u]);
    t[u]=total;
}

void Build(int i, int l, int r){
    tr[i].l=l, tr[i].r=r;
    if (l==r) {tr[i].maxn=a[l]; return ;}
    int mid=(l+r)>>1;
    Build(i<<1, l, mid);
    Build(i<<1|1, mid+1, r);
    tr[i].maxn=max(tr[i<<1].maxn, tr[i<<1|1].maxn);
}

int Find(int i, int l, int r){
    if (tr[i].l==l && tr[i].r==r)
        return tr[i].maxn;
    int mid=(tr[i].l+tr[i].r)>>1;
    if (r<=mid) return Find(i<<1, l, r);
    if (l>=mid+1) return Find(i<<1|1, l, r);
    if (l<=mid && r>=mid+1)
        return max(Find(i<<1, l, mid), Find(i<<1|1, mid+1, r));
}

void Update(int i, int x){
    if (tr[i].l==tr[i].r){
        tr[i].maxn=0;
        return ;
    }
    int mid=(tr[i].l+tr[i].r)>>1;
    if (x<=mid) Update(i<<1, x);
    if (x>=mid+1) Update(i<<1|1, x);
    tr[i].maxn=max(tr[i<<1].maxn, tr[i<<1|1].maxn);
}

int main(){
    scanf ("%d %d %d", &n, &m, &q);
    for (int i=1; i<=n; i++)
        scanf ("%d", &p[i]);
    for (int i=1; i<=m; i++)
        scanf ("%d %d", &u[i], &v[i]);
    for (int i=1; i<=q; i++)
        scanf ("%d %d", &type[i], &pos[i]);
    for (int i=1; i<=q; i++)
        if (type[i]==2) del[pos[i]]++;
    for (int i=1; i<=3*n; i++)
        fa[i]=i;
    tot=n;
    for (int i=1; i<=m; i++)
        if (del[i]==0) Combine(u[i], v[i]);

    for (int i=q; i>=1; i--)
        if (type[i]==2){
            del[pos[i]]--;
            if (del[pos[i]]==0)
                Combine(u[pos[i]], v[pos[i]]);
        }
        else
            pos[i]=Find(pos[i]);

    //for (int i=1; i<=tot; i++)
    //    printf ("%d: [%d %d]\n", i, lc[i], rc[i]);
    for (int i=1; i<=tot; i++)
        if (fa[i]==i)
            dfs(i);
    Build(1,1,total);
    for (int i=1; i<=q; i++)
        if (type[i]==1){
            int tmp;
            printf ("%d\n", tmp=Find(1, s[pos[i]], t[pos[i]]));
            if (tmp!=0) Update(1, w[tmp]);
        }
}
