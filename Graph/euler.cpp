#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,id;
    
    bool operator<(const Edge &x)const{
        return v<x.v;
    }

};
int n,m,in[MN],out[MN];
vector<Edge> adj[MN];

namespace Euler{
    int cur[MN],sta[MN],top;
    bool vise[MN],vis[MN];

    void dfs(int u){
        for(int i=cur[u];i<adj[u].size();i=max(i+1,cur[u])){
            int v=adj[u][i].v;
            if(!vis[adj[u][i].id]){
                vis[adj[u][i].id]=1;
                cur[u]=i+1;
                dfs(v);
            }
        }
        sta[++top]=u;
    }

}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back({v,i});
        in[v]++,out[u]++;
    }
    int cnt=0,st=0,ed=0;
    bool flag=0;
    for(int i=1;i<=n;i++){
        if(in[i]!=out[i]){
            flag=0;
            cnt++;
            if(out[i]-in[i]==1){
                st=i;
            }else if(out[i]-in[i]==-1) ed=i;
            else{
                cout<<"No\n";
                return 0;
            }
        }
    }
    if(cnt!=0&&cnt!=2){
        cout<<"No\n";
    }else{
        if(cnt==0) st=ed=1;
        if(!st||!ed){
            cout<<"No\n";
            return 0;
        }
        for(int i=1;i<=n;i++){
            sort(adj[i].begin(),adj[i].end());
        }
        Euler::dfs(st);
        while(Euler::top){
            cout<<Euler::sta[Euler::top--]<<' ';
        }
    }

    return 0;
}