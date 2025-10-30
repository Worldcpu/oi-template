#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m;

struct Trie{
    int t[MN][65],tot,cnt[MN];

    int getx(char a){
        if(a>='A'&&a<='Z'){
            return a-'A';
        }else if(a>='a'&&a<='z'){
            return a-'a'+26;
        }else return a-'0'+52;
    }

    void clear(){
        for(int i=0;i<=tot;i++){
            memset(t[i],0,sizeof(t[i]));
            cnt[i]=0;
        }
        tot=0;
    }

    void insert(const string &x){
        int p=0;
        for(auto ch:x){
            int k=getx(ch);
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
            cnt[p]++;
        }
    }

    int query(const string &st){
        int p=0;
        for(auto ch:st){
            int k=getx(ch);
            if(!t[p][k]) return 0;
            p=t[p][k];
        }
        return cnt[p];
    }
}t;

void init(){
    t.clear();   
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=n;i++){
        string qwq;
        cin>>qwq;
        t.insert(qwq);
    }   
    for(int i=1;i<=m;i++){
        string qwq;
        cin>>qwq;
        cout<<t.query(qwq)<<'\n';
    }
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}
