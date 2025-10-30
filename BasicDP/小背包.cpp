#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e4+15;
int f[MN],v,n;

int main(){
    cin>>v>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        for(int j=v;j>=x;j--){
            f[j]=max(f[j],f[j-x]+x);
        }
    }
    cout<<v-f[v];

    return 0;
}