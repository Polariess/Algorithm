#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=2005;
const int maxm=4000001;
int n,m,s,t,k;
int cnt,h[maxn];
int cnt_rev,h_rev[maxn];
int d[maxn];
int count[maxn];
bool vst[maxn];
struct edge{
	int next,v,to;
}e[maxm],e_rev[maxm];

//同时建正反图 
void add(int x,int y,int z)
{
    e[++cnt].next=h[x];
    e[cnt].to=y;
    e[cnt].v=z;
    h[x]=cnt;
    
    e_rev[++cnt_rev].next=h_rev[y];
    e_rev[cnt_rev].to=x;
    e_rev[cnt_rev].v=z;
    h_rev[y]=cnt_rev;
}

struct node {
  	int x,v;
  	bool operator<(node a) const { return v>a.v; }
};
priority_queue<node> Q;

struct node2{
  	int x,v;
  	bool operator<(node2 a) const { return v+d[x]>a.v+d[a.x]; }
};
priority_queue<node2> q;

//反图上跑dij 
void Dij_rev()
{
	for(int i=1;i<=n;i++)d[i]=0x3ffff;
	d[t]=0;
  	Q.push({t, 0});
  	while(!Q.empty())
	{
    	node n_t=Q.top();
    	int x=n_t.x,v=n_t.v;
    	Q.pop();
    	if(vst[x])continue;
    	vst[x]=true;
    	for(int i=h_rev[x];i;i=e_rev[i].next)
		{
			int y=e_rev[i].to;
			if(d[y]>d[x]+e_rev[i].v)
			{
				d[y]=d[x]+e_rev[i].v;
				Q.push({y,d[y]});
			}
		}
  	}
}

//正向图上A*搜索解决k短路 
void A_Star()
{
	q.push({s, 0});
  	while(!q.empty())
	{
    	node2 n_t=q.top();
    	int x=n_t.x,v=n_t.v;
    	q.pop();
    	count[x]++;
    	if(x==t&&count[x]==k)
		{
      		printf("%d\n",v);
      		return;
    	}
    	if(count[x]>k) continue;
    	for(int i=h[x];i;i=e[i].next)
			q.push({e[i].to,v+e[i].v});
    }
  	printf("-1\n");
}

int main()
{
    cin>>n>>m>>s>>t>>k;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
    }
    Dij_rev();
    A_Star();
}
/*
5 7 1 5 10086
1 2 1
1 3 2
2 5 4
2 4 2
4 5 3
3 5 4
2 1 1

ans:6728
*/ 
