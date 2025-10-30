#include<bits/stdc++.h>
#define int long long //十年OI一场空，不开long long见祖宗
using namespace std;
constexpr int MN=5e5+15;
int n,m;
string a,b;

namespace EXKMP{
    int z[MN],p[MN];

    void getz(int n,const string &st){
        z[1]=n;
        for(int i=2,l=1,r=1;i<=n;i++){
            if(i<=r) z[i]=min(r-i+1,z[i-l+1]);
            while(i+z[i]<=n&&st[z[i]+1]==st[i+z[i]]) z[i]++;
            if(i+z[i]-1>r) l=i,r=i+z[i]-1;
        }
    }

    void getp(int n,int m,const string &a,const string &b){
        for(int i=1,l=0,r=0;i<=n;i++){
            if(i<=r) p[i]=min(r-i+1,z[i-l+1]);
            while(i+p[i]<=n&&p[i]+1<=m&&a[i+p[i]]==b[p[i]+1]) p[i]++;
            if(i+p[i]-1>r) l=i,r=i+p[i]-1;
        }
    }

}using namespace EXKMP;

signed main(){
    cin>>a>>b;
    n=a.length(),m=b.length();
    a=" "+a,b=" "+b;
    getz(m,b);
    getp(n,m,a,b);
	int ans=0;
	for(int i=1;i<=m;i++) ans^=1ll*i*(z[i]+1);
    cout<<ans<<'\n';
	ans=0;
	for(int i=1;i<=n;i++) ans^=1ll*i*(p[i]+1);
    cout<<ans<<'\n';
	return 0;
}
