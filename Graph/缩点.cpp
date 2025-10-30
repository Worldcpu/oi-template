#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,a[MN],f[MN],ans;
vector<int> adj[MN],G[MN];

namespace Tarjan{
    int dfn[MN],low[MN],st[MN],col[MN],top,dtot,w[MN],ctot;
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        vis[u]=1;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]) low[u]=min(low[u],dfn[v]);
        }
        if(low[u]==dfn[u]){
            ctot++;
            int p;
            do{
                p=st[top--];
                vis[p]=0;
                col[p]=ctot;
                w[ctot]+=a[p];
            }while(p!=u);
        }
    }
}using namespace Tarjan;

namespace Topo{
    int in[MN];

    void toposort(){
        queue<int> q;
        fill(f+1,f+1+ctot,0);
        for(int i=1;i<=ctot;i++){
            if(!in[i]){
                q.push(i);
                f[i]=w[i];
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:G[u]){
                f[v]=max(f[v],f[u]+w[v]);
                if(!--in[v]) q.push(v);
            }
        }
    }

}using namespace Topo;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=n;i++){
        for(auto v:adj[i]){
            if(col[i]!=col[v]){
                G[col[i]].push_back(col[v]);
                in[col[v]]++;
            }
        }
    }
    toposort();
    for(int i=1;i<=ctot;i++){
        ans=max(ans,f[i]);
    }
    cout<<ans<<'\n';
    return 0;
}