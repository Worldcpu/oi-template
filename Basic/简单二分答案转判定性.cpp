#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,x[MN];

bool check(int k){
    int lst=0,tot=0;
    for(int i=1;i<=n;i++){
        if(!lst||x[i]-x[lst]>=k){
            lst=i;
            tot++;
        }
    }
    return tot>=m;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>x[i];
    sort(x+1,x+1+n);
    int l=1,r=x[n]-x[1],ret=l;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) l=mid+1,ret=mid;
        else r=mid-1;
    }
    cout<<ret;

    return 0;
}