#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,ML=30;
int st[ML+2][MN],n,a[MN],q;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}


void initst(){
    for(int i=1;i<=ML;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i-1)]);
        }
    }
}

int query(int l,int r){
    int lg=__lg(r-l+1);
    return max(st[lg][l],st[lg][r-(1<<lg)+1]);
}

int main(){
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        st[0][i]=a[i];
    }
    initst();
    while(q--){
        int l,r;
        l=read(),r=read();
        cout<<query(l,r)<<'\n';
    }

    return 0;
}