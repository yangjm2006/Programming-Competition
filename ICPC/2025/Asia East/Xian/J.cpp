#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+100;
ll c[N];
vector<int>G[N];
ll dep[N];
ll val[N],mi1val[N],mi2val[N];
ll fax[32][N],valx[32][N];


void dfs(int x,int f){
    val[x]=c[x];
    fax[0][x]=f;
    dep[x]=dep[f]+1;
    ll sum1 = 1e18,sum2=1e18;
    for(int v:G[x]){
        if(v==f)continue;
        dfs(v,x);
        if(val[v]<=sum1){
            sum2=sum1;
            sum1=val[v];
        }
        else if(val[v]<sum2)sum2=val[v];
    }
    mi1val[x]=sum1;
    mi2val[x]=sum2;
    val[x]=min(val[x],sum1+sum2);
}
int pw[32];

void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        G[i].clear();
        val[i]=1e18;
    }
    int u,v;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    dfs(1,1);
    int now,tar;

    queue<int>q;
    q.push(1);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int v:G[x]){
            if(v==fax[0][x])continue;
            q.push(v);
        }
        if(dep[x]>1){
            if(val[x]==mi1val[fax[0][x]])valx[0][x]=mi2val[fax[0][x]];
            else valx[0][x]=mi1val[fax[0][x]];
        }
        for(int i=1;pw[i]<dep[x];i++){
            fax[i][x]=fax[i-1][fax[i-1][x]];
            valx[i][x]=valx[i-1][fax[i-1][x]]+valx[i-1][x];
        }
    }
    

    for(int i=1;i<=m;i++){
        cin>>now>>tar;
        bool op=0;
        ll ans = 0;
        while(now!=tar){
            if(dep[now]<=dep[tar]){
                break;
            }
            // cout<<now<<" ! "<<tar<<'\n';
            int tpx=dep[now]-dep[tar];
            int ths = 0;
            // cout<<tpx<<'\n';
            while((tpx&1)!=1){
                tpx>>=1;
                ths++;
            }
            // cout<<ths<<'\n';
            // cout<<'\n';
            ans+=valx[ths][now];
            now=fax[ths][now];
            if(now==tar){
                op=1;
            }
        }
        if(op){
            cout<<ans<<'\n';
        }
        else cout<<"-1\n";
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    pw[0]=1;
    for(int i=1;i<32;i++)pw[i]=pw[i-1]*2;
    while(T--) solve();
    return 0;
}

/*
3
5 5
1 2 3 4 5
1 2
1 3
2 4
2 5
3 1
2 1
4 1
5 1
5 2
5 5
1 5 1 1 1
1 2
1 3
2 4
2 5
3 1
2 1
4 1
5 1
2 5
6 5
9 9 8 2 4 4
1 2
1 3
1 4
1 5
1 6
2 1
3 1
4 1
5 1
6 1

*/