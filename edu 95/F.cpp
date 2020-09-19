#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define ll long long
const int N=5e5+5;
int n, m;
ll l, r;
vector<int>v[N];
struct Tree{
    int l, r;
    pair<ll, ll>minn;
}tr[4*N];

void Build(int i, int l, int r){
    tr[i].l = l, tr[i].r = r;
    tr[i].minn = mp(1e18, 0);
    if (l==r) return;
    int mid=(l+r)>>1;
    Build(i*2, l, mid);
    Build(i*2+1, mid+1, r);
}

void Insert(int i, int pos, long long minn){
    if (tr[i].l==pos && tr[i].r==pos){
        tr[i].minn=mp(min(minn, tr[i].minn.first), pos);
        return ;
    }

    int mid=(tr[i].l+tr[i].r)>>1;
    if (pos<=mid) Insert(i*2, pos, minn);
    if (pos>mid) Insert(i*2+1, pos, minn);
    tr[i].minn=min(tr[i*2].minn, tr[i*2+1].minn);
}

pair<ll, ll> Find(int i, int l, int r){
    if (tr[i].l==l && tr[i].r==r)
        return tr[i].minn;
    int mid=(tr[i].l+tr[i].r)>>1;
    if (r<=mid) return Find(i*2, l, r);
    if (mid<l) return Find(i*2+1, l, r);
    if (l<=mid && r>mid) return min(Find(i*2, l, mid), Find(i*2+1, mid+1, r));
}

int main(){
    scanf ("%d %d %lld %lld", &n, &m, &l, &r);
    for (int i=1; i<=max(m, n); i++)
        for (int j=1; i*j<=max(m, n); j++)
            v[i*j].push_back(i);

    Build(1,1,max(n, m));
    ll L=m+1;
    for (ll x1=1; x1<=n; x1++){
        ll ln=(l+x1-1)/x1, rn=r/x1;
        while (ln<L){
            for (int k=0; k<v[L-1].size(); k++) Insert(1, v[L-1][k], L-1);
            L--;
        }
        int flag=0;
        for (int k=0; k<v[x1].size(); k++){
            ll a = v[x1][k];
            ll lb = a+1, rb = 1ll*n*a/x1, y1, b;
            if (lb > rb) continue;
            pair<ll, ll>tmp = Find(1, lb, rb);
            y1 = tmp.first, b=tmp.second;
            if (y1>rn) continue;
            else{
                printf ("%lld %lld %lld %lld\n", x1, y1, x1/a*b, y1/b*a);
                flag=1;
                break;
            }
        }
        if (!flag) printf ("-1\n");
    }

}
