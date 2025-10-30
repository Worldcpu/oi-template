#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m;
string a,b;

namespace KMP{
    int nxt[MN];

    void initnxt(int n,const string &st){
        nxt[1]=0;
        for(int i=2,j=0;i<=n;i++){
            while(j&&st[i]!=st[j+1]) j=nxt[j];
            if(st[i]==st[j+1]) j++;
            nxt[i]=j;
        }
    }

}using namespace KMP;


int main(){
    cin>>a>>b;
    n=a.length(),m=b.length();
    a=" "+a,b=" "+b;
    initnxt(m,b);
    for(int i=1,j=0;i<=n;i++){
        while(j>0&&b[j+1]!=a[i]) j=nxt[j];
        if(b[j+1]==a[i]) j++;
        if(j==m){
            cout<<i-j+1<<'\n';
            j=nxt[j];
        }
    }
    for(int i=1;i<=m;i++) cout<<nxt[i]<<' ';
        

    return 0;
}