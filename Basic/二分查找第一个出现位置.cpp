#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m,a[MN];


int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    while(m--){
        int x;
        cin>>x;
        auto it=lower_bound(a+1,a+1+n,x)-a;
        if(a[it]!=x){
            cout<<-1<<' ';
        }else cout<<it<<' ';
        // int l=1,r=n,ret=1;
        // while(l<=r){
        //     int mid=(l+r)>>1;
        //     if(a[mid]>=x) r=mid-1,ret=mid;
        //     else l=mid+1;
        // }
        // if(a[l]!=x){
        //     cout<<-1<<' ';
        // }else cout<<ret<<' ';
    }
    
    return 0;
}