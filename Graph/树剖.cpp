#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,ML=30;
int n,m,rt;
vector<int> adj[MN];

namespace Tree{
    int dfn[MN],st[ML+2][MN],dtot;

    void dfs(int u,int pre){
        dfn[u]=++dtot;
        st[0][dfn[u]]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs(v,u);
        }
    }

    int cmpdfn(int x,int y){
        return dfn[x]<dfn[y]?x:y;
    }

    void initst(){
        for(int i=1;i<=ML;i++){
            for(int j=1;j+(1<<i)-1<=n;j++){
                st[i][j]=cmpdfn(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
    }

    int lca(int x,int y){
        if(x==y) return x;
        x=dfn[x],y=dfn[y];
        if(x>y) swap(x,y);
        int lg=__lg(y-x++);
        return cmpdfn(st[lg][x],st[lg][y-(1<<lg)+1]);
    }

}using namespace Tree;

int main(){
    cin>>n>>m>>rt;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(rt,0);
    initst();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        cout<<lca(u,v)<<'\n';
    }
    return 0;
}