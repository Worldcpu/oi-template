#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int u,v,w;
}e[MN];
int n,m;

namespace DSU{
    int pre[MN];

    void initpre(){
        iota(pre+1,pre+MN,1);
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }
}using namespace DSU;

namespace Bor{
    int mxw[MN];
    bool vise[MN];

    bool cmp(int x,int y){
        if(!y) return 1;
        if(e[x].w!=e[y].w) return e[x].w<e[y].w;
        return x<y;
    }

    int Boru(){
        int ret=0;
        bool flag=1;
        while(flag){
            flag=0;
            fill(mxw+1,mxw+1+n,0);
            for(int i=1;i<=m;i++){
                if(vise[i]) continue;
                int ru=root(e[i].u),rv=root(e[i].v);
                if(ru==rv) continue;
                if(cmp(i,mxw[ru])) mxw[ru]=i;
                if(cmp(i,mxw[rv])) mxw[rv]=i;
            }
            for(int i=1;i<=n;i++){
                if(mxw[i]&&!vise[mxw[i]]){
                    flag=1;
                    ret+=e[mxw[i]].w;  
                    vise[mxw[i]]=1;
                    pre[root(e[mxw[i]].u)]=root(e[mxw[i]].v);
                }
            }
        }
        return ret;
    }

}

int main(){
    initpre();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    int ret=Bor::Boru(),cnt=0;
    for(int i=1;i<=n;i++){
        cnt+=(pre[i]==i);
    }
    if(cnt>1){
        cout<<"orz";
    }else cout<<ret;
    return 0;
}