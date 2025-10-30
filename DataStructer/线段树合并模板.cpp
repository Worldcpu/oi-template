#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e6+15,MV=1e6+15,ML=21;
int n,m,rt[MN],ans[MN];
vector<int> adj[MN];

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    
    struct Node{
        int mxv,id;

        Node(int mxvv=0,int idd=0){
            mxv=mxvv,id=idd;
        }

        friend Node operator+(const Node &x,const Node &y){
            if(x.mxv>=y.mxv) return x;
            else return y;
        }
    };

    struct SNode{
        int lson,rson;
        Node val;
    }t[MN*10];
    int tot;

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void update(int &p,int l,int r,int pos,int k){
        if(!p) p=++tot;
        if(l==r){
            t[p].val.mxv+=k;
            t[p].val.id=pos;
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) update(ls,l,mid,pos,k);
        else update(rs,mid+1,r,pos,k);
        pushup(p);
    }

    int merge(int x,int y,int l,int r){
        if(!x||!y) return x|y;
        int p=++tot;
        if(l==r){
            t[p].val=Node(t[x].val.mxv+t[y].val.mxv,l);
            return p;
        }
        int mid=(l+r)>>1;
        ls=merge(t[x].lson,t[y].lson,l,mid);
        rs=merge(t[x].rson,t[y].rson,mid+1,r);
        pushup(p);
        return p;
    }
}sg;

namespace Tree{
    int fa[ML+2][MN],dep[MN];

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        fa[0][u]=pre;
        for(int i=1;i<=ML;i++){
            fa[i][u]=fa[i-1][fa[i-1][u]];
        }
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
        }
    }

    void dfs2(int u,int pre){
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs2(v,u);
            rt[u]=sg.merge(rt[u],rt[v],1,MV);
        }
        ans[u]=(sg.t[rt[u]].val.mxv)?sg.t[rt[u]].val.id:0;
    }
    
    int lca(int x,int y){
        if(dep[x]<dep[y]) swap(x,y);
        for(int i=ML;i>=0;i--){
            if(dep[fa[i][x]]>=dep[y]) x=fa[i][x];
        }
        if(x==y) return x;
        for(int i=ML;i>=0;i--){
            if(fa[i][x]!=fa[i][y]) x=fa[i][x],y=fa[i][y];
        }
        return fa[0][x];
    }
}using namespace Tree;

int main(){
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    while(m--){
        int x,y,k;
        cin>>x>>y>>k;
        int lcaa=lca(x,y);
        sg.update(rt[x],1,MV,k,1);
        sg.update(rt[y],1,MV,k,1);
        sg.update(rt[lcaa],1,MV,k,-1);
        sg.update(rt[fa[0][lcaa]],1,MV,k,-1);
    }
    dfs2(1,0);
    for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
    return 0;
}