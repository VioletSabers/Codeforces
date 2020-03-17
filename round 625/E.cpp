#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n;
struct Edge
{
    int num;
    int next;
}edge[2*N];
int tot, last[N];
int dfn[N], d[N];
int tim;
int c[N];
int fa[N][20];
vector<int>node;
stack<int>stk;

int f[N], ans[N];
int V[N];
int id[N];

void Add(int i, int j)
{
    tot++;
    edge[tot].num=j;
    edge[tot].next=last[i];
    last[i]=tot;
}

void dfs(int u, int ff)
{
    d[u]=d[ff]+1;
    dfn[u]=++tim;
    fa[u][0]=ff;
    for (int k=last[u]; k!=0; k=edge[k].next)
    {
        int v=edge[k].num;
        if (v==ff) continue;
        dfs(v, u);
    }
}

bool cmp1(int a, int b)
{
    return dfn[a] < dfn[b];
}

int LCA(int x, int y)
{
    if (d[x]>d[y]) swap(x,y);
    for (int i=19; i>=0; i--)
        if (d[fa[y][i]] >= d[x]) y=fa[y][i];
    if (x==y) return x;
    for (int i=19; i>=0; i--)
        if (fa[y][i]!=fa[x][i]) y=fa[y][i], x=fa[x][i];
    return fa[x][0];
}
vector<int>son[N];

int Calc(int x, int y)
{
    return d[x]+d[y]-2*d[LCA(x, y)];
}

void dfs1(int u)
{
    for (int k=0; k<son[u].size(); k++)
        dfs1(son[u][k]);
    for (int k=0; k<son[u].size(); k++)
    {
        int v=son[u][k];
        if (ans[v]==0) continue;
        int T=(Calc(id[ans[v]], u) + V[ans[v]]-1)/V[ans[v]];
        if (ans[u]==0 || T<f[u] || (T==f[u] && ans[v]<ans[u]))
        {
            ans[u]=ans[v];
            f[u]=T;
        }
    }
}

void dfs2(int u, int fa)
{
    int T;
    if (fa!=0) T=(Calc(id[ans[fa]], u) + V[ans[fa]]-1)/V[ans[fa]];
    else T=1e9;
    if (ans[u]==0 || T<f[u] || (T==f[u] && ans[fa]<ans[u]))
    {
        ans[u]=ans[fa];
        f[u]=T;
    }
    for (int k=0; k<son[u].size(); k++)
    {
        int v=son[u][k];
        dfs2(v, u);
    }
}

int main()
{
    scanf ("%d", &n);
    for (int i=1; i<n; i++)
    {
        int u,v;
        scanf ("%d %d",&u,&v);
        Add(u,v);
        Add(v,u);
    }
    dfs(1, 0);
    for (int j=1; j<=19; j++)
        for (int i=1; i<=n; i++)
            fa[i][j]=fa[fa[i][j-1]][j-1];
    int q;
    scanf ("%d", &q);
    while (q--)
    {
        int k, m;
        scanf ("%d %d", &k, &m);
        for (int i=1; i<=k; i++)
        {
            int u, v;
            scanf ("%d %d", &u, &v);
            id[i]=u;
            V[i]=v;
            node.push_back(u);
            ans[u]=i;
        }

        for (int i=1; i<=m; i++)
        {
            scanf ("%d", &c[i]);
            node.push_back(c[i]);
        }
        node.push_back(1);
        sort(node.begin(), node.end(), cmp1);

        int last=1, len=node.size();
        stk.push(1);

        for (int i=0; i<len-1; i++)
            node.push_back(LCA(node[i], node[i+1]));
        sort(node.begin(), node.end(), cmp1);

        /*for (int i=0; i<node.size();i++)
            printf ("%d ", node[i]);
        printf ("\n");*/

        for (int i=0; i<node.size(); i++)
        {
            if (node[i]==last) continue;
            else
            {
                while (1)
                {
                    int u=stk.top();
                    int p=LCA(u, node[i]);
                    //printf ("%d %d %d\n", p, u, node[i]);
                    if (p==u)
                    {
                        son[p].push_back(node[i]);
                        break;
                    }
                    else stk.pop();
                }
                stk.push(node[i]);
            }
            last=node[i];
        }


        /*for (int i=0; i<node.size(); i++)
        {
            int u=node[i];
            printf ("%d: ", u);
            for (int j=0; j<son[u].size(); j++)
                printf ("%d ", son[u][j]);
            printf ("\n");
        }
        printf ("\n");*/
        dfs1(1);
        dfs2(1, 0);

        for (int i=1; i<=m; i++)
            printf ("%d ", ans[c[i]]);
        //for (int i=1; i<=m; i++)
        //    printf ("%d ", f[c[i]]);
        printf ("\n");

        for (int i=0;i<node.size(); i++)
        {
            ans[node[i]]=0, f[node[i]]=0;
            while(!son[node[i]].empty()) son[node[i]].pop_back();
        }
        while (!node.empty()) node.pop_back();
        while (!stk.empty()) stk.pop();
        tot=0;

    }
}
