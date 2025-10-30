#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
struct Edge{
    int v,w;
};
int n,m;
vector<Edge> adj[MN];

namespace SPFA{
    int dis[MN],cnt[MN];
    bool vis[MN];

    bool spfa(int st){
        queue<int> q;
        fill(dis+1,dis+1+n,INF);
        fill(vis+1,vis+1+n,0);
        fill(cnt+1,cnt+1+n,0);
        q.push(st);
        dis[st]=0;
        vis[st]=1;
        cnt[st]++;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    if(!vis[v]){
                        q.push(v);
                        cnt[v]++;
                        vis[v]=1;
                        if(cnt[v]>n) return 1;
                    }
                }
            }
        }
        return 0;
    }
}

void init(){
    for(int i=1;i<=n;i++){
        adj[i].clear();
    }
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        if(w>=0){
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }else adj[u].push_back({v,w});
    }
    cout<<(SPFA::spfa(1)?"YES":"NO")<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
}