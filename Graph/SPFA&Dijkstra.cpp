#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
struct Edge{
    int v,w;
};
int n,m,s;
vector<Edge> adj[MN];

namespace Dijkstra{
    int dis[MN];
    bool vis[MN];

    void dijk(int st){
        priority_queue<pir,vector<pir>,greater<pir>> q;
        fill(dis+1,dis+1+n,INF);
        dis[st]=0;
        q.push(pir(0,st));
        while(!q.empty()){
            auto u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    q.push(pir(dis[v],v));
                }
            }
        }
    }
    
}

namespace SPFA{
    int dis[MN];
    bool vis[MN];

    void spfa(int st){
        queue<int> q;
        fill(dis+1,dis+1+n,INF);
        q.push(st);
        dis[st]=0;
        vis[st]=1;
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
                        vis[v]=1;
                    }
                }
            }
        }
    }
}

int main(){
    cin>>n>>m>>s;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    Dijkstra::dijk(s);
    using Dijkstra::dis;
    for(int i=1;i<=n;i++){
        if(dis[i]==1e9) cout<<INT_MAX<<' ';
        else cout<<dis[i]<<' ';
    }
    
    return 0;
}