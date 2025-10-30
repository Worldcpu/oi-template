#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],b[MN];

namespace CRT{
    int exgcd(int a,int b,int &x,int &y){
        if(!b){
            x=1,y=0;
            return a;
        }
        int d=exgcd(b,a%b,y,x);
        y-=a/b*x;
        return d;
    }

    int inv(int a,int MOD){
        int x,y;
        exgcd(a,MOD,x,y);
        return (x+MOD)%MOD;
    }

    int slowtim(int a,int b,int MOD){
        int ret=0;
        while(b){
            if(b&1) ret=(ret+a)%MOD;
            a=(a+a)%MOD;
            b>>=1;
        }
        return ret;
    }

    int crt(){
        int modpw=1,ans=0;
        for(int i=1;i<=n;i++){
            modpw*=a[i];
        }
        for(int i=1;i<=n;i++){
            int m=modpw/a[i],mt=inv(m,a[i]),ci=m*mt;
            ans=(ans+slowtim(b[i],ci,modpw))%modpw;
        }
        return (ans+modpw)%modpw;
    }

}using namespace CRT;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    cout<<crt();
    
    return 0;
}