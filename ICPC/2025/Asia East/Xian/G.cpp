#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a.begin(),a.end());
    int ans1=0,ans2=0;
    for(int i=0;i<n;i++)
        if(ans1>=a[i]) ans1++;
        else ans1--;
    for(int i=n-1;i>=0;i--)
        if(ans2<a[i]) ans2--;
        else ans2++;
    cout<<ans1<<" "<<ans2;
    return 0;
}