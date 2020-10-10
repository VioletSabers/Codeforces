#include <bits/stdc++.h>
using namespace std;

const int N=205;
char s[N][N];
int cnt, to[4*N*N], nxt[4*N*N], lst[4*N*N];
int n, m;

struct edge{
	int to,next,f;
}e[16*N*N];
int tot,head[4*N*N];

void add(int x,int y,int v){
	e[++tot]=(edge){y,head[x],v};
	head[x]=tot;
	e[++tot]=(edge){x,head[y],0};
	head[y]=tot;
}

int F(int x, int y, int p){
    int num=(x-1)*m+y;
    return num*2-1+p;
}

int visT, T, S;
int vis[4*N*N], q[4*N*N], dis[4*N*N], cur[4*N*N];
bool bfs(){
	int h=0,t=1;
	vis[S]=++visT;
	q[1]=S; dis[S]=0; cur[S]=head[S];
	while (h!=t){
		int x=q[++h];
		for (int i=head[x];i;i=e[i].next)
			if (vis[e[i].to]!=visT&&e[i].f){
				dis[e[i].to]=dis[x]+1;
				vis[e[i].to]=visT;
				cur[e[i].to]=head[e[i].to];
				if (e[i].to==T) return 1;
				q[++t]=e[i].to;

			}
	}
	return 0;
}

int C(int i){ return i%2? i+1:i-1;}
int dfs(int x,int flow){
	if (x==T) return flow;
	int k,rest=flow;
	for (int &i=cur[x];i&&rest;i=e[i].next)
		if (dis[e[i].to]==dis[x]+1&&vis[e[i].to]==visT&&e[i].f){
			k=dfs(e[i].to,min(e[i].f,flow));
			e[i].f-=k; e[C(i)].f+=k; rest-=k;
			if (!rest) break;
		}
	if (rest) dis[x]=-1;
	return flow-rest;
}

int dinic(){
    int ans=0;
    for (;bfs();ans+=dfs(S,1<<20)) ;
    return ans;
}

int main(){
    scanf ("%d %d", &n, &m);
    for (int i=1; i<=n; i++)
        scanf ("%s",s[i]+1);
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++){
            if(s[i][j]=='#' && s[i][j+1]=='#' && s[i-1][j]=='#')
                add(F(i, j, 1), F(i-1, j, 0), 1);
            if(s[i][j]=='#' && s[i][j+1]=='#' && s[i+1][j]=='#')
                add(F(i, j, 1), F(i, j, 0), 1);
            if(s[i][j]=='#' && s[i][j-1]=='#' && s[i-1][j]=='#')
                add(F(i, j-1, 1), F(i-1, j, 0), 1);
            if(s[i][j]=='#' && s[i][j-1]=='#' && s[i+1][j]=='#')
                add(F(i, j-1, 1), F(i, j, 0), 1);
        }
    S=F(n,m,2);
    T=F(n,m,3);
    //printf ("S=%d\n", S);
    //printf ("T=%d\n", T);
    int num=0, numm=0;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++){
            add(S, F(i, j, 1), 1);
            add(F(i, j, 0), T, 1);
            if (s[i][j]=='#') num++;
            if (s[i][j]=='#' && s[i+1][j]=='#') numm++;
            if (s[i][j]=='#' && s[i][j+1]=='#') numm++;

        }
    int ans=dinic();
    printf ("%d\n", num-numm+ans);
}
