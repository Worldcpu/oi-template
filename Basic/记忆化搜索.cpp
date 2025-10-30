#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
unordered_map<int,int> vis;

int dfs(int u){
    int ret=1;
    if(u==1) return 1;
    if(vis[u]) return vis[u];
    for(int i=1;i<=u/2;i++) ret+=dfs(i);
    vis[u]=ret;
    return ret;
}

int main(){
    cin>>n;
    cout<<dfs(n);

    return 0;
}