#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+100;
struct edge{
    int v,nxt;
}e[N*2];
int _,head[N];
void adde(int u,int v){
    e[++_].v=v;e[_].nxt=head[u];head[u]=_;
}
ll c[N],s[N],val[N];
void dfs1(int u,int fa){
    ll ans1=1e18,ans2=1e18;
    vector<int> vec;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa) continue;
        dfs1(v,u);
        if(ans1>val[v]){
            ans2=ans1;
            ans1=val[v];
        }else if(ans2>val[v]){
            ans2=val[v];
        }
        vec.push_back(v);
    }
    for(auto v:vec){
        if(ans1==val[v]) s[v]=ans2;
        else s[v]=ans1;
    }
    val[u]=min(c[u],ans1+ans2);
}
int dfn[N],dn,st[20][N];
void dfs2(int u,int fa){
    st[0][dfn[u]=++dn]=fa;
    s[u]+=s[fa];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa) continue;
        dfs2(v,u);
    }
}
int get(int x,int y){
    return dfn[x]<dfn[y]?x:y;
}
int lca(int x,int y){
    if(x==y) return x;
    x=dfn[x];y=dfn[y];
    if(x>y) swap(x,y);
    x++;
    int k=__lg(y-x+1);
    return get(st[k][x],st[k][y-(1<<k)+1]);
}
void solve(){
    int n,m;
    cin>>n>>m;
    _=dn=0;for(int i=1;i<=n;i++) head[i]=0;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1,u,v;i<=n-1;i++){
        cin>>u>>v;
        adde(u,v);adde(v,u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int k=1;k<=__lg(n);k++){
        for(int i=1;i+(1<<k-1)<=n;i++){
            st[k][i]=get(st[k-1][i],st[k-1][i+(1<<k-1)]);
        }
    }
    for(int i=1,x,y;i<=m;i++){
        cin>>x>>y;
        if(lca(x,y)==y) cout<<s[x]-s[y]<<'\n';
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
*/