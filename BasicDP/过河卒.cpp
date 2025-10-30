#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=25;
int n,m,a,b,f[MN][MN],g[MN][MN];

void prework(int x,int y){
    f[x][y]=1;
    f[x-1][y-2]=1;
    f[x-2][y-1]=1;
    f[x-2][y+1]=1;
    f[x-1][y+2]=1;
    f[x+1][y-2]=1;
    f[x+2][y-1]=1;
    f[x+2][y+1]=1;
    f[x+1][y+2]=1;
}

signed main(){
    cin>>n>>m>>a>>b;
    a++,b++,n++,m++;
    prework(a,b);
    g[1][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i==1&&j==1) continue;
            if(!f[i][j]) g[i][j]=g[i-1][j]+g[i][j-1];
        }
    }
    cout<<g[n][m];
    

    return 0;
}