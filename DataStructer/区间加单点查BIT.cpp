#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m;

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    void modify(int l,int r,int k){
        modify(l,k);
        modify(r+1,-k);
    }
}bit;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        bit.modify(i,i,x);
    }
    while(m--){
        int op,l,r,k;
        cin>>op;
        if(op==1){
            cin>>l>>r>>k;
            bit.modify(l,r,k);
        }else{
            cin>>k;
            cout<<bit.query(k)<<'\n';
        }
    }   
    return 0;
}