#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15;
int n,ans;

namespace Phi{
    int phi[MN];
    bitset<MN> vis;
    vector<int> prime;

    void getphi(int n){
        vis[0]=vis[1]=1;
        phi[1]=1;
        for(int i=2;i<=n;i++){
            if(!vis[i]){
                prime.push_back(i);
                phi[i]=i-1;
            }
            for(auto p:prime){
                if(p*i>n) break;
                vis[p*i]=1;
                if(i%p==0){
                    phi[i*p]=phi[i]*p;
                    break;
                }
                phi[i*p]=phi[i]*phi[p];
            }
        }
        for(int i=1;i<=n;i++){
            phi[i]+=phi[i-1];
        }
    }

}



signed main(){
    cin>>n;
    Phi::getphi(n);
    for(auto p:Phi::prime){
        ans+=2*Phi::phi[n/p]-1;
    }
    cout<<ans;
    return 0;
}