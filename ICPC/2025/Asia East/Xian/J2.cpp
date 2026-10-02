#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+100;
ll c[N];
vector<int>G[N];
ll fa[N],fax[N],dep[N];
ll val[N],mi1val[N],mi2val[N];
ll valf[N];

ll mxdep;

void dfs(int x,int f){
    val[x]=c[x];
    fa[x]=f;
    dep[x]=dep[f]+1;
    mxdep=max(mxdep,dep[x]);
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

void solve(){
    int n,m;
    cin>>n>>m;
    mxdep = 0;
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
    int w=sqrt(mxdep);

    for(int i=1;i<=n;i++){
        if(dep[i]>w){
            int now=i;
            ll ans = 0;
            int tp=w;
            while(tp>0){
                if(val[now]==mi1val[fa[now]])ans+=mi2val[fa[now]];
                else ans+=mi1val[fa[now]];
                now=fa[now];
                tp--;
            }
            fax[i]=now;
            valf[i]=ans;
        }
    }

    for(int i=1;i<=m;i++){
        cin>>now>>tar;
        bool op=0;
        ll ans = 0;
        while(now!=tar){
            if(dep[now]-w>=dep[tar]){
                ans+=valf[now];
                now=fax[now];
                if(now==tar){
                    op=1;
                }
                continue;
            }
            if(dep[now]<=dep[tar]){
                if(now==tar){
                    op=1;
                }
                break;
            }
            if(val[now]==mi1val[fa[now]])ans+=mi2val[fa[now]];
            else ans+=mi1val[fa[now]];
            now=fa[now];
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