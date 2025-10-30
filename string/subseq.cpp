#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,q,m;
vector<int> nxt[MN];

int main(){
    int type;
    cin>>type>>n>>q>>m;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        nxt[x].push_back(i);
    }
    while(q--){
        int len,pos=0;
        bool flag=1;
        cin>>len;
        for(int i=1;i<=len;i++){
            int x;
            cin>>x;
            if(!flag) continue;
            auto ret=lower_bound(nxt[x].begin(),nxt[x].end(),pos+1);
            if(ret==nxt[x].end()) flag=0;
            else pos=*ret;
        }
        if(flag){
            cout<<"Yes\n";
        }else cout<<"No\n";
    }

    return 0;
}