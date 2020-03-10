#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n,m;
struct Edge
{
    int num;
    int next;
    bool en;
}edge[2 * N];
int tot, last[N];

void Add(int i, int j, bool en)
{
    tot++;
    edge[tot].num=j;
    edge[tot].next=last[i];
    edge[tot].en=en;
    last[i]=tot;
}


queue<int>q;
bool vis[N];
int dis[N];
void bfs(int S)
{
    q.push(S);
    vis[S]=1;
    while (!q.empty())
    {
        int u=q.front();
        q.pop();
        for (int k=last[u];k!=0;k=edge[k].next)
        {

            int v=edge[k].num;
            if (vis[v]) continue;
            if (edge[k].en==0) continue;
            //printf ("(%d %d)\n", u, v);
            dis[v]=dis[u]+1;
            q.push(v);
            vis[v]=1;
        }
    }
}

int p[N];
int main()
{
    scanf ("%d %d", &n, &m);
    for (int i=1; i<=m; i++)
    {
        int u,v;
        scanf ("%d %d", &u, &v);
        Add(u, v, 0);
        Add(v, u, 1);
    }
    int K;
    scanf ("%d", &K);
    for (int i=1; i<=K; i++)
        scanf ("%d", &p[i]);
    bfs(p[K]);
    /*for (int i=1; i<=n; i++)
        printf ("%d ", dis[i]);
    printf ("\n");*/
    int minn=0, maxn=0;
    for (int i=1; i<K; i++)
    {
        int u=p[i];
        int num=0;
        for (int k=last[u]; k!=0; k=edge[k].next)
        {
            int v=edge[k].num;
            if (edge[k].en) continue;
            if (v==p[i+1])
                if (dis[v]+1!=dis[u]) minn++;
            if (dis[v]+1==dis[u]) num++;
        }
        if (num >= 2 || (num==1 && dis[p[i+1]]+1!=dis[u]))
            maxn++;
    }
    printf ("%d %d\n", minn, maxn);
}
