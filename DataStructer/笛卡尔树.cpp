#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e7+15;
int a[MN],n;

namespace Tree{
    int st[MN],lson[MN],rson[MN],top=0,rt;

    void build(int n){
        st[++top]=1;
        rt=1;
        for(int i=2;i<=n;i++){
            bool flag=0;
            while(top>0&&a[st[top]]>a[i]){
                top--;
                flag=1;
            }
            if(flag){
                lson[i]=st[top+1];
            }
            if(top){
                rson[st[top]]=i;
            }else{
                rt=i;
            }
            st[++top]=i;
        }
    }

}using namespace Tree;


int main(){
ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(n);
    ll l=0,r=0;
    for(int i=1;i<=n;i++){
        l^=1ll*i*(lson[i]+1);
        r^=1ll*i*(rson[i]+1);
    }
    cout<<l<<" "<<r;
    return 0;
}