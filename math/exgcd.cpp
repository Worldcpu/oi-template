#include<bits/stdc++.h>
#define int long long
using namespace std;

int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

void solve(){
    int a,b,c,x,y;
    cin>>a>>b>>c;
    int d=exgcd(a,b,x,y);
    if(c%d!=0){
        cout<<-1<<'\n';
        return;
    }
    x=x*c/d,y=y*c/d;
    int tx=b/d,ty=a/d,k=ceil((1.0-x)/tx);
    x+=tx*k,y-=ty*k;
    if(y<=0){
            int ansy=y+ty*1ll*ceil((1.0-y)/ty);
            cout<<x<<" "<<ansy<<'\n';
    }else{
            cout<<(y-1)/ty+1<<" "<<x<<" "<<(y-1)%ty+1<<" "<<x+(y-1)/ty*tx<<" "<<y<<'\n';
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }


    return 0;
}