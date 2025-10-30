#include<bits/stdc++.h>
#define double long double
using namespace std;
constexpr int MN=17;
constexpr double eps=1e-7;
int n;
double a[MN],L,R;

double f(double x){
    double ans=0;
    for(int i=0;i<=n;i++){
        ans=ans*x+a[i];
    }
    return ans;
}

int main(){
    cin>>n>>L>>R;
    for(int i=0;i<=n;i++){
        cin>>a[i];
    }

    while(R-L>=eps){
        auto mid=(L+R)/2;
        if(f(mid+eps)>f(mid-eps)) L=mid;
        else R=mid;
    }

    cout<<fixed<<setprecision(5)<<R;

    return 0;
}