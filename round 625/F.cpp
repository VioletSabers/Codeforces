#include <bits/stdc++.h>
using namespace std;

const int T=2e5+5;
int n, m, h;
int dx[6]={1, -1, 0, 0, 0, 0};
int dy[6]={0, 0, 1, -1, 0, 0};
int dz[6]={0, 0, 0, 0, 1, -1};


struct Data
{
    int x, y, z;
    int num;
    int dir;
};
vector<Data>L;
queue<int>q;
vector<int>v[T];
int ans[T], vis[T];

int Calc(int x, int y, int z)
{
    return (x-1) *m*h + (y-1) *h + z;
}


bool judge(int p)
{
    int num=-1;
    for (int i=0; i<v[p].size(); i++)
        if (num==-1) num=L[v[p][i]].num;
        else
            if (num==L[v[p][i]].num) continue;
            else return 0;
    if (num==0) return 0;
    else return 1;
}

bool Judge(int x, int y)
{
    if (x==0 && y==1) return 0;
    if (x==1 && y==0) return 0;
    if (x==2 && y==3) return 0;
    if (x==3 && y==2) return 0;
    if (x==4 && y==5) return 0;
    if (x==5 && y==4) return 0;
    return 1;

}

bool BFS()
{
    while (!q.empty())
    {
        int id=q.front();
        int x=L[id].x, y=L[id].y, z=L[id].z, num=L[id].num, dir=L[id].dir;

        q.pop();
        int p=Calc(x, y, z);

        if (num == 0 || vis[p]==1)
        {
            for (int i=0; i<v[p].size(); i++)
            {
                int d=v[p][i];
                int xx=x+dx[L[d].dir], yy=y+dy[L[d].dir], zz=z+dz[L[d].dir];
                if (xx > n || xx < 1 || yy > m || yy < 1 || zz > h || zz < 1)
                    if (L[d].num != 0) return 0;
                    else continue;
                L[d].x=xx;
                L[d].y=yy;
                L[d].z=zz;
                q.push(d);
                v[Calc(xx, yy, zz)].push_back(d);
            }
            vis[p]=1;
            v[p].clear();
        }

        if (v[p].size() != 1)
            if (judge(p) == 0)
            {
                for (int i=0; i<v[p].size(); i++)
                {
                    int d=v[Calc(x, y, z)][i];
                    int xx=x+dx[L[d].dir], yy=y+dy[L[d].dir], zz=z+dz[L[d].dir];
                    if (xx > n || xx < 1 || yy > m || yy < 1 || zz > h || zz < 1)
                        if (L[d].num != 0) return 0;
                        else continue;
                    L[d].x=xx;
                    L[d].y=yy;
                    L[d].z=zz;
                    q.push(d);
                    v[Calc(xx, yy, zz)].push_back(d);
                }
                vis[p]=1;
                v[p].clear();
            }
            /*else
            {
                if (v[p].size() > 2 || Judge(L[v[p][0]].dir, L[v[p][1]].dir))
                {
                    ans[p]=L[v[p][0]].num;
                    v[p].clear();
                    vis[p]=2;
                }
            }*/
    }
    return 1;
}

int main()
{
    scanf ("%d %d %d", &n, &m, &h);
    for (int i=1; i<=m; i++)
        for (int j=1; j<=h; j++)
        {
            int x;
            scanf ("%d", &x);
            Data tmp=(Data){1, i, j, x, 0};
            q.push((int)q.size());
            L.push_back(tmp);
            v[Calc(1, i, j)].push_back((int)L.size()-1);
        }

    for (int i=1; i<=m; i++)
        for (int j=1; j<=h; j++)
        {
            int x;
            scanf ("%d", &x);
            Data tmp=(Data){n, i, j, x, 1};
            q.push((int)q.size());
            L.push_back(tmp);
            v[Calc(n, i, j)].push_back((int)L.size()-1);
        }

    for (int i=1; i<=n; i++)
        for (int j=1; j<=h; j++)
        {
            int x;
            scanf ("%d", &x);
            Data tmp=(Data){i, 1, j, x, 2};
            q.push((int)q.size());
            L.push_back(tmp);
            v[Calc(i, 1, j)].push_back((int)L.size()-1);
        }

    for (int i=1; i<=n; i++)
        for (int j=1; j<=h; j++)
        {
            int x;
            scanf ("%d", &x);
            Data tmp=(Data){i, m, j, x, 3};
            q.push((int)q.size());
            L.push_back(tmp);
            v[Calc(i, m, j)].push_back((int)L.size()-1);
        }

    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
        {
            int x;
            scanf ("%d", &x);
            Data tmp=(Data){i, j, 1, x, 4};
            q.push((int)q.size());
            L.push_back(tmp);
            v[Calc(i, j, 1)].push_back((int)L.size()-1);
        }

    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
        {
            int x;
            scanf ("%d", &x);
            Data tmp=(Data){i, j, h, x, 5};
            q.push((int)q.size());
            L.push_back(tmp);
            v[Calc(i, j, h)].push_back((int)L.size()-1);
        }
    if (BFS() == 0)
    {
        printf ("-1");
        return 0;
    }
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
            for (int k=1; k<=h; k++)
            {
                int p=Calc(i, j, k);
                if (!v[p].empty())
                    ans[p]=L[v[p][0]].num;
            }
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
        {
            for (int k=1; k<=h; k++)
                printf ("%d ", ans[Calc(i, j, k)]);
            printf ("\n");
        }
        printf ("\n");
    }

}
