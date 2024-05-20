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
int count;
bool vst[maxn],vis[maxn],ontree[maxm];
int fa[maxn];//��¼���·�����ϵ�ĸ��� 
struct edge{
	int next,v,to;
}e[maxm],e_rev[maxm];

//ͬʱ������ͼ 
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

struct node{
  	int x,v;
  	bool operator<(node a) const { return v>a.v; } //�������ȶ���dij 
  	bool operator>(node a) const { return v>a.v; } //������ƫ���ȽϽڵ��С���������������ϰ�� 
};
priority_queue<node> Q;

//��ͼ����dij 
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

//�����·���� 
void dfs(int x)
{
  	vis[x]=true;
  	for(int i=h_rev[x];i;i=e_rev[i].next)
  	{
  		int y=e_rev[i].to;
  		if(vis[y])continue;
		if(d[y]==d[x]+e_rev[i].v)
		{
			//���������·���ϣ��������� 
			fa[y]=x;
			ontree[i]=true;
			dfs(y);		
		} 
  	}
}

struct LeftistTree{
  	int cnt_,rt[maxn],lc[maxn*20],rc[maxn*20],dist[maxn*20];
  	//dist:�����·d������ڵ���� 
  	node v[maxn*20];
  	LeftistTree() { dist[0]=-1; }

  	int newnode(node w)
  	{
    	cnt_++;
    	v[cnt_]=w;
    	return cnt_;
  	}

  	//��ƫ���ϲ� 
  	int merge(int x, int y)
  	{
		if(!x||!y)return x+y;
    	if(v[x]>v[y])swap(x,y);
    	int p=++cnt_;
    	lc[p]=lc[x];
    	v[p]=v[x];
    	rc[p]=merge(rc[x], y);
    	if(dist[lc[p]]<dist[rc[p]])swap(lc[p],rc[p]);
    	dist[p]=dist[rc[p]]+1;
    	return p;
  	}
}st;

void dfs2(int x)
{
  	vis[x]=true;
  	if(fa[x])st.rt[x]=st.merge(st.rt[x],st.rt[fa[x]]);
  	for(int i=h_rev[x];i;i=e_rev[i].next)
  	{
  		int y=e_rev[i].to;
  		if(fa[y]==x&&!vis[y])dfs2(y);
	}
}

void Build()
{
	//����ƫ�����ݽṹ������ά����Ϣ
	for(int x=1;x<=n;x++)
	{
		if(!vst[x])continue;
      	for (int i=h[x];i;i=e[i].next)
      	{
      		if(ontree[i])continue;//��ͼ�ϱߵı�ź���ͼ�����ͬ 
      		int y=e[i].to;
      		if(!vst[y])continue;
			st.rt[x]=st.merge(st.rt[x],st.newnode({y,d[y]+e[i].v-d[x]}));
		}
	}
	for(int i=1;i<=n;i++)vis[i]=false;
	dfs2(t);
}

void Solve()
{
	if(st.rt[s])Q.push({st.rt[s],d[s]+st.v[st.rt[s]].v});
  	while(!Q.empty())
	{
    	node n_t=Q.top();
    	int x=n_t.x,v=n_t.v;
    	Q.pop();
    	count++;
    	if(count==k-1)
		{
      		printf("%d\n",v);
      		return;
    	}
    	if(st.lc[x])  // �ɲ���ɾ��ֱ�Ӱ����Ҷ��Ӽ������ȶ�����
      		Q.push({st.lc[x],v-st.v[x].v+st.v[st.lc[x]].v});
    	if(st.rc[x])
      		Q.push({st.rc[x],v-st.v[x].v+st.v[st.rc[x]].v});
    	int y=st.rt[st.v[x].x];
    	if(y)Q.push({y,v+st.v[y].v});
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
    //k==1:���· 
    if(k==1)
    {
    	cout<<(vst[s] ? d[s] : -1)<<endl;
    	return 0;
	}
   dfs(t);
   Build();
   Solve();
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
