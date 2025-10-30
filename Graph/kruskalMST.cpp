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

namespace Kru{

    bool cmp(Edge x,Edge y){
        return x.w<y.w;
    }

    int kru(){
        int ret=0;
        sort(e+1,e+1+m,cmp);
        for(int i=1;i<=m;i++){
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru!=rv){
                ret+=e[i].w;
                pre[ru]=rv;
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
    int ret=Kru::kru(),cnt=0;
    for(int i=1;i<=n;i++){
        cnt+=(pre[i]==i);
    }
    if(cnt>1){
        cout<<"orz";
    }else cout<<ret;
    return 0;
}