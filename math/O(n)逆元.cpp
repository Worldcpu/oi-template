#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e6+15;
int n,MOD,inv[MN];

void initpw(){
    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
    }
}

signed main(){
    cin>>n>>MOD;
    initpw();
    for(int i=1;i<=n;i++){
        cout<<inv[i]<<'\n';
    }
    return 0;
}