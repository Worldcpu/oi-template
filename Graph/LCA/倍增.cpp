#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,ML=22;
int n,m,rt;
vector<int> adj[MN];

namespace PPM{
    #define getchar getchar_unlocked
    #define putchar putchar_unlocked

    template<typename type>
    void read(type &x){
        x=0;bool flag(0);char ch=getchar();
        while(!isdigit(ch)) flag=ch=='-',ch=getchar();
        while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
        flag?x=-x:0;
    }
    void read(char &x){do{x=getchar();}while(isspace(x));}
    void read(char x[]){static char ch;ch=getchar();do{*(x++)=ch;}while(!isspace(ch=getchar())&&~ch);}
    void read(string &x){x.clear();static char ch;ch=getchar();do{x.push_back(ch);}while(!isspace(ch=getchar())&&~ch);}
    template<typename type,typename... arg>
    void read(type &x,arg&... y){
        read(x);
        read(y...);
    }
    template<typename type>
    void write(type &x){
        x<0?x=-x,putchar('-'):0;
        static short st[50],top(0);
        do{st[++top]=x%10,x/=10;}while(x);
        while(top){putchar(st[top--]|48);}
    }
    void write(const char &x){putchar(x);}
    void write(char x[]){while(*x) putchar(*(x++));}
    void write(const string &x){for(int i=0;i<x.size();i++)putchar(x[i]);}
    template<typename type>
    void put(type x,bool flag=1){
        write(x);
        flag?putchar('\n'):putchar(' ');
    }
    #undef getchar
    #undef putchar
}using namespace PPM;


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
}using Tree::lca;


int main(){
    read(n,m,rt);
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Tree::dfs1(rt,0);   

    while(m--){
        int x,y;
        read(x,y);
        put(lca(x,y));
    }
    return 0;
}