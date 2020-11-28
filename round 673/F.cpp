#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define maxn 200000
#define mod 998244353
#define inf 0x3f3f3f3f

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef double db;

const int N=1e5+5;
int a[N];
int n, m;
int p[5][2]={0,0,-1,0,1,0,0,1,0,-1};
bool lim[N];
int link[N], used[N];

int to[10*N], lst[N], nxt[10*N], cnt;
int ans[N];
char d[N];

int C(int x, int y){return x*m+y;}
pii C(int x){return x<0|x>=n*m?mp(-1,-1):mp(x/m, x%m);}

bool dfs(int u, int cas){
    for (int k=lst[u]; k!=0; k=nxt[k]){
        int v=to[k];
        if (used[v]!=cas){
            used[v]=cas;
            if (link[v]==-1 || dfs(link[v], cas)){
                link[u]=v;
                link[v]=u;
                return 1;
            }
            else{
                if (lim[link[v]]==0){
                    link[link[v]]=-1;
                    link[u]=v;
                    link[v]=u;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void Add(int u, int v){
    cnt++, nxt[cnt]=lst[u], to[cnt]=v, lst[u]=cnt;
    cnt++, nxt[cnt]=lst[v], to[cnt]=u, lst[v]=cnt;
}

char T(int x, int y, int xx, int yy){
    if (yy==y+1) return 'R';
    if (yy==y-1) return 'L';
    if (xx==x-1) return 'U';
    if (xx==x+1) return 'D';
}

void Find(int u){
    pii cor=C(u);
    int x=cor.fi, y=cor.se;
    if (link[u]==-1){
        rep(k,1,4){
            int xx=x+p[k][0], yy=y+p[k][1];
            if (xx<0 || xx>=n || yy<0 || yy>=m || a[C(xx,yy)]>=a[u])
                continue;
            d[u]=T(x,y,xx,yy);
            ans[u]=a[u]-a[C(xx, yy)];
            break;
        }
    }
    else{
        int xx, yy;
        pii corr;
        corr=C(link[u]);
        xx=corr.fi, yy=corr.se;
        d[u]=T(x,y,xx,yy);
        if (ans[link[u]])
            ans[u]=a[u]-ans[link[u]];
        else
            ans[u]=1;
    }
}

int main(){
    int T;
    scanf ("%d", &T);
    while (T--){
        scanf ("%d %d", &n, &m);
        rep(i,0,n*m-1)
            link[i]=-1;
        rep(i, 0, n*m-1) scanf ("%d", &a[i]);
        bool ok=1;
        rep(i, 0, n*m-1){
            pii xy=C(i);
            bool flag=0;
            int num=0;
            rep(k, 1, 4){
                int x=xy.fi+p[k][0], y=xy.se+p[k][1];
                if (x<0 || x>=n || y<0 || y>=m || a[C(x,y)]>a[i])
                    continue;
                flag=1;
                if (a[C(x,y)]==a[i] && C(x,y)<i)
                    Add(C(x,y), i);
                else if (a[C(x,y)]!=a[i]) num++;
            }
            if (!flag){
                ok=0; break;
            }
            if (num==0)
                lim[i]=1;
        }
        if (!ok){
            printf ("NO\n");
            continue;
        }
        int cas=0;
        rep(i, 0, n*m-1){
            if (!lim[i]) continue;
            if (link[i]==-1 && !dfs(i, ++cas)){
                ok=0;
                break;
            }
        }
        if (!ok){
            printf ("NO\n");
            continue;
        }
        rep(i,0,n*m-1)
            if (ans[i]==0) Find(i);
        printf ("YES\n");
        rep(i,0,n-1){
            rep(j,0,m-1) printf("%d ", ans[C(i,j)]);
            printf("\n");
        }
        rep(i,0,n-1){
            rep(j,0,m-1) printf("%c ", d[C(i,j)]);
            printf("\n");
        }
        cnt=0;
        rep(i,0,n*m-1) lim[i]=ans[i]=d[i]=used[i]=lst[i]=0, link[i]=-1;
    }
}
