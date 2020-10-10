#include <bits/stdc++.h>
using namespace std;

const int N=3e5+5;
int n;
int a[N], f[N];
struct Tree{
    int l, r;
    int maxn;
    int add;
}tr[4*N];

struct Que{
    int l, r;
    int id;
}Q[N];
bool cmp(Que a, Que b){
    return a.r < b.r;
}

void Build(int i, int l, int r){
    tr[i].l=l;
    tr[i].r=r;
    if (l==r) return ;
    int mid=(l+r)>>1;
    Build(i*2, l, mid);
    Build(i*2+1, mid+1, r);
}

void PushDown(int i){
    int x=tr[i].add;
    tr[i*2].maxn+=x, tr[i*2].add+=x;
    tr[i*2+1].maxn+=x, tr[i*2+1].add+=x;
    tr[i].add=0;
}

void PushUp(int i){
    tr[i].maxn=max(tr[i*2].maxn, tr[i*2+1].maxn);
}

void Add(int i, int l, int r, int c){
    //printf ("%d %d\n", l, r);
    if (tr[i].l==l && tr[i].r==r){
        //printf("%d %d: %d\n", l, r, c);
        tr[i].maxn+=c, tr[i].add+=c;
        return ;
    }
    PushDown(i);
    int mid=(tr[i].l+tr[i].r)>>1;
    if (r<=mid) Add(i*2, l, r, c);
    if (l>mid) Add(i*2+1, l, r, c);
    if (l<=mid && r>mid){
        Add(i*2, l, mid, c);
        Add(i*2+1, mid+1, r, c);
    }
    PushUp(i);
}

int Find(int i, int l, int r, int x){
    //printf ("[%d %d %d: %d]\n", tr[i].l, tr[i].r, x, tr[i].maxn);
    if (l==r) return l;
    PushDown(i);
    int mid=(tr[i].l+tr[i].r)>>1;
    if (r<=mid) return Find(i*2, l, r, x);
    if (l>mid) return Find(i*2+1, l, r, x);
    if (l<=mid && r>mid){
        if (tr[i*2+1].maxn>=x) return Find(i*2+1, mid+1, r, x);
        else return Find(i*2, l, mid, x);
    }
}

int GetAns(int i, int pos){
    //printf ("%d %d\n", tr[i].l, tr[i].r);
    if (pos==tr[i].l && pos==tr[i].r) return tr[i].maxn;
    PushDown(i);
    int mid=(tr[i].l+tr[i].r)>>1;
    if (pos<=mid) return GetAns(i*2, pos);
    if (pos>mid) return GetAns(i*2+1, pos);
}

int ans[N];
int main(){
    int n, q;
    scanf ("%d %d", &n, &q);
    for (int i=1; i<=n; i++)
        scanf ("%d", &a[i]);
    for (int i=1; i<=q; i++){
        scanf ("%d %d", &Q[i].l, &Q[i].r);
        Q[i].r=n-Q[i].r;
        Q[i].l=Q[i].l+1;
        Q[i].id=i;
    }
    sort(Q+1, Q+1+q, cmp);
    Build(1,1,n);
    int now=0;
    for (int i=1; i<=n; i++)
        if (i-a[i]<=f[i-1] && i-a[i]>=0) f[i]=f[i-1]+1;
        else f[i]=f[i-1];
    for (int i=1; i<=q; i++){

        while (now!=Q[i].r){
            now++;
            //printf ("%d:\n", now);
            int k=now, pos;
            if (a[k]>k || f[k-1]<k-a[k]) continue;
            else if (a[k]==k) Add(1, 1, k, 1);
                 else{
                     pos=Find(1, 1, k-1, k-a[k]);
                     //printf ("Find: %d %d %d\n", 1, k-1, k-a[k]);
                     Add(1, 1, pos, 1);
                     //printf ("Add: %d %d\n", 1, pos);
                 }

        }
        ans[Q[i].id]=GetAns(1, Q[i].l);
    }
    for (int i=1; i<=q; i++)
        printf ("%d\n", ans[i]);
}
