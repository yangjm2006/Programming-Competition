#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+100;
ll a[N],s[N];
void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n,greater<ll>());
    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
    if(n==1){
        cout<<"0\n";
        return;
    }
    cout<<"0 0 ";
    int tp=1;
    for(int i=3;i<=n;i++){
        tp=1;
        while(tp+i-1<=n&&s[tp+i-1]-s[tp]<=a[tp]){
            tp++;
        }
        if(tp+i-1>n) cout<<"0 ";
        else cout<<s[tp+i-1]-s[tp-1]<<" ";
    }
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}