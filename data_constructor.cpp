#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
int u[maxn],v[maxn];
int main(){
    freopen("1.in","w",stdout);
    srand(time(0));
    int n=10,m=58,s=rand()%n+1,t=rand()%n+1,k=rand()%10;
    while(t==s)
	{
        t=rand()%n+1;
    }
    int distance_max=100;
    cout<<n<<" "<<m<<" "<<s<<" "<<t<<" "<<k<<endl;
    for(int i=2;i<=n;++i)
	{
        int from=rand()%(i-1)+1;
        if(from==1)
		{
            from=s;
        }
		else
		{
            from=1;
        }
        int distance=rand()%distance_max;
        cout<<from<<" "<<i<<" "<<distance<<endl;
        // u[i]=from;
        // v[i]=i;
    }
    for(int i=n;i<=m;++i)
	{
        int distance=rand()%distance_max;
        cout<<rand()%n+1<<" "<<rand()%n+1<<" "<<distance<<endl;
    }
}
