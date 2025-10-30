#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,mod,b;

int phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0){
                n/=i;
            }
        }
    }
    if(n>=2) ans=ans/n*(n-1);
    return ans;
}

int ksm(int a,int b,int MOD){
    int ret=1;
    while(b>0){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int read(int mod){
    int x=0;bool flag(0);char ch=getchar();
        while(!isdigit(ch)) ch=getchar();
        while(isdigit(ch)) ((x=(x<<3)+(x<<1)+(ch^48))>=mod?x%=mod,flag=1:0),ch=getchar();
    if(flag) return (x+mod);
    else return x;
}

signed main(){
    cin>>a>>mod;
    cerr<<phi(mod);
    b=read(phi(mod));
    cout<<ksm(a,b,mod);

    return 0;
}