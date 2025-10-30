#include<bits/stdc++.h>
using namespace std;
constexpr int MN=114;
int n;
bitset<MN> a[MN];


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x;
            cin>>x;
            a[i][j]=x;
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                a[i][j]=a[i][j]|(a[i][k]&a[k][j]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<a[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}