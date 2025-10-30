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

    // int excrt(){
    //     int x,y,m1=a[1],b1=b[1],ans=(b1%m1+m1)%m1;
    //     for(int i=2;i<=n;i++){
    //         int m2=a[i],b2=b[i];
    //         int a=m1,b=m2,c=(b2-b1%m2+m2)%m2;
    //         int d=exgcd(a,b,x,y);
    //         if(c%d!=0) return -1;
    //         x=slowtim(x,c/d,b/d);
    //         ans=b1+x%m1;
    //         m1=m2/d*m1;
    //         ans=(ans%m1+m1)%m1;
    //         b1=ans;
    //     }
    // }

    int excrt(){
        int x,y,m1=a[1],b1=b[1];
        int ans=(b1%m1+m1)%m1;
        for(int i=2;i<=n;i++){
            int m2=a[i],b2=b[i];
            int a=m1,b=m2,c=(b2-b1%m2+m2)%m2;
            int d=exgcd(a,b,x,y);
            if(c%d!=0) return -1;
            x=slowtim(x,c/d,b/d);
            ans=b1+x*m1;
            m1=m2/d*m1;
            ans=(ans%m1+m1)%m1;
            b1=ans;
        }
        return ans;
    }

}using namespace CRT;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    cout<<excrt();
    
    return 0;
}