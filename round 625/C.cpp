#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5;
const int M=1e6;
int n,m,p;

struct Tree
{
    int l, r;
    int maxn;
    int add;
}tree[4*M+50];

struct Data
{
    int x;
    int c;
}a[N], b[N];

void Build(int i, int l, int r)
{
    tree[i].l=l;
    tree[i].r=r;
    tree[i].maxn = -(2e9+5);
    if (tree[i].l==tree[i].r)
        return ;
    int mid=(l+r)/2;
    Build(i*2,l,mid);
    Build(i*2+1,mid+1,r);
}

void PushDown(int i)
{
    int x=tree[i].add;
    tree[i*2].add+=x;
    tree[i*2+1].add+=x;
    tree[i*2].maxn+=x;
    tree[i*2+1].maxn+=x;
    tree[i].add=0;
}

void PushUp(int i)
{
    tree[i].maxn = max(tree[i*2].maxn, tree[i*2+1].maxn);
}

bool cmp(Data a, Data b)
{
    return a.x < b.x;
}

void Add(int i, int l, int r, int x)
{
    if (l > r) return ;
    if (tree[i].l==l && tree[i].r==r)
    {
        tree[i].add+=x;
        tree[i].maxn+=x;
        return ;
    }
    PushDown(i);
    int mid=(tree[i].l+tree[i].r)/2;
    if (r<=mid)
        Add(i*2, l, r, x);
    if (l>=mid+1)
        Add(i*2+1, l, r, x);
    if (l<=mid && r>=mid+1)
    {
        Add(i*2, l, mid, x);
        Add(i*2+1, mid+1, r, x);
    }
    PushUp(i);
}

struct Monster
{
    int x,y,z;
}d[N];

bool cmp1(Monster a, Monster b)
{
    return a.x < b.x;
}

int Find(int i, int l, int r)
{
    if (tree[i].l==l && tree[i].r==r)
        return tree[i].maxn;
    PushDown(i);
    int mid=(tree[i].l+tree[i].r)/2;
    if (r<=mid) return Find(i*2, l, r);
    if (l>=mid+1) return Find(i*2+1, l, r);
    if (l<=mid && r>=mid+1)
        return max(Find(i*2, l, mid), Find(i*2+1, mid+1, r));
}

int minn[M+5];
int main()
{
    scanf ("%d %d %d", &n, &m, &p);
    for (int i=1; i<=n; i++)
        scanf ("%d %d", &a[i].x, &a[i].c);
    for (int i=1; i<=m; i++)
        scanf ("%d %d", &b[i].x, &b[i].c);
    for (int i=1; i<=p; i++)
        scanf ("%d %d %d", &d[i].x, &d[i].y, &d[i].z);
    Build(1,1,M);
    sort(a+1, a+1+n, cmp);
    sort(d+1, d+1+p, cmp1);
    for (int i=1; i<=m; i++)
    {
        if (minn[b[i].x] != 0)
            minn[b[i].x] = min(b[i].c, minn[b[i].x]);
        else minn[b[i].x] = b[i].c;
    }

    for (int i=1; i<=M; i++)
        if (minn[i] != 0) Add(1, i, i, 2e9+5-minn[i]);
    int k=1;
    int ans=-(2e9+5);
    for (int i=1; i<=n; i++)
    {
        while(k<=p && d[k].x<a[i].x)
        {
            Add(1, d[k].y+1, M, d[k].z);
            k++;
        }
        ans = max(ans, Find(1,1,M) - a[i].c);
    }
    printf ("%d\n", ans);

}
