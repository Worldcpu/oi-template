#include<bits/stdc++.h>
#define double long double
using namespace std;
constexpr int MN=55;
constexpr double eps=1e-8;
int n;
double a[MN][MN];

namespace Gauss{
    
    int gauss(){
        int rk=1;
        for(int j=1;j<=n;j++){
            int h=rk;
            for(int i=rk;i<=n;i++){
                if(fabs(a[i][j])>fabs(a[h][j])) h=i;
            }
            if(fabs(a[h][j])<eps) continue;
            swap(a[rk],a[h]);
            double div=a[rk][j];
            for(int i=j;i<=n+1;i++){
                if(fabs(a[rk][i])>eps){
                    a[rk][i]/=div;
                }
            }
            for(int i=1;i<=n;i++){
                double tmp=a[i][j];
                if(i==rk) continue;
                for(int k=j;k<=n+1;k++){
                    a[i][k]-=a[rk][k]*tmp;
                }
            }
            rk++;
        }
        for(int i=rk;i<=n;i++){
            if(fabs(a[i][n+1])>eps){
                return -1;
            }
        }
        if(rk<=n) return 1;
        for(int i=n;i>=1;i--){
            for(int j=i+1;j<=n;j++){
                a[i][n+1]-=a[i][j]*a[j][n+1];
            }
        }
        return 0;
    }

    int gauss2(){
        int rk=1;
        for(int j=1;j<=n;j++){
            int h=rk;
            for(int i=rk;i<=n;i++){
                if(fabs(a[i][j])>fabs(a[h][j])) h=j;
            }
            if(fabs(a[h][j])<eps) continue;
            swap(a[h],a[rk]);
            auto div=a[rk][j];
            for(int i=j;i<=n+1;i++){
                if(fabs(a[rk][i])>eps){
                    a[rk][i]/=div;
                }
            }
            for(int i=1;i<=n;i++){
                auto tmp=a[i][j];
                if(i==rk) continue;
                for(int k=j;k<=n+1;k++){
                    a[i][k]-=tmp*a[rk][k];
                }
            }
            rk++;
        }
        for(int i=rk;i<=n;i++){
            if(fabs(a[i][n+1])>eps) return -1;
        }
        if(rk<=n) return 1;
        for(int i=n;i>=1;i--){
            for(int j=i+1;j<=n;j++){
                a[i][n+1]-=a[i][j]*a[j][n+1];
            }
        }
        return 0;
    }

}


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            cin>>a[i][j];
        }       
    }
    int ret=Gauss::gauss2();
    if(ret==-1) cout<<-1;
    else if(ret==1) cout<<0;
    else{
        for(int i=1;i<=n;i++){
            cout<<'x'<<i<<"="<<fixed<<setprecision(2)<<a[i][n+1]<<'\n';
        }
    }
    return 0;
}