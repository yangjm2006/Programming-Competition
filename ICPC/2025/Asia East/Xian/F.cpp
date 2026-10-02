#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+100;
struct node{
    int u,v,tim;bool f;
    bool operator < (const node &x) const{
        return tim>x.tim;
    }
};
int t[N],a[N],ans[N];
vector<int> vec[N];
bool vis[N];
void solve(){
    priority_queue<node> q;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>t[i];
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]*=2;
        ans[i]=0;
        vec[i].clear();
    }
    for(int i=1;i<=n;i++) vec[t[i]].push_back(i);
    for(int i=1;i<=n;i++){
        if(a[t[i]]>a[i]) vis[i]=1;
        else vis[i]=0;
    }
    for(int i=1;i<=n;i++){
        if(vis[i]^vis[t[i]]) q.push((node){i,t[i],abs(a[i]-a[t[i]])/2,0});
    }
    while(!q.empty()){
        int u=q.top().u,v=q.top().v,tim=q.top().tim;bool f=q.top().f;
        q.pop();
        // cout<<u<<"++\n";
        if(ans[u]) continue;
        if(ans[v]!=0&&f==0) continue;
        ans[u]=tim;
        int pos;
        if(vis[u]) pos=a[u]+tim;
        else pos=a[u]-tim;
        for(auto x:vec[u]){
            int p;
            if(vis[x]) p=a[x]+tim;
            else p=a[x]-tim;
            q.push((node){x,u,tim+abs(p-pos),1});
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";cout<<'\n';
}
int main(){
    // ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    T=1;
    while(T--) solve();
    return 0;
}