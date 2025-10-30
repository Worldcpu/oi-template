#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
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

int main(){
    initpre();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        int rx=root(x),ry=root(y);
        if(op==1){
            pre[rx]=ry;
        }else{
            cout<<(rx==ry?"Y":"N")<<'\n';
        }
    }
    return 0;
}