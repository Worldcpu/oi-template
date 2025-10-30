#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int T,n,m,MOD,jc[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(int p){
    jc[0]=1;
    for(int i=1;i<=p;i++){
        jc[i]=jc[i-1]*i%MOD;
    }
}

int getc(int n,int m){
    if(n<m) return 0;
    return jc[n]*ksm(jc[m],MOD-2)%MOD*ksm(jc[n-m],MOD-2)%MOD;
}

int lucas(int n,int m){
    if(n<m) return 0;
    if(!n) return 1;
    return lucas(n/MOD,m/MOD)*getc(n%MOD,m%MOD)%MOD;
}

void solve(){
    cin>>n>>m>>MOD;
    init(MOD);
    cout<<lucas(n+m,m)<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
}