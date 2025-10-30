#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,q,MOD,a[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,sum,add,mul;
    }t[MN<<2];

    void domul(int p,int k){
        t[p].sum=t[p].sum*k%MOD;
        t[p].add=t[p].add*k%MOD;
        t[p].mul=t[p].mul*k%MOD;
    }

    void doadd(int p,int k){
        t[p].sum=(t[p].sum+k*(t[p].r-t[p].l+1)%MOD)%MOD;
        t[p].add=(t[p].add+k)%MOD;
    }

    void pushdown(int p){
        if(t[p].mul!=1){
            domul(ls,t[p].mul);
            domul(rs,t[p].mul);
            t[p].mul=1;
        }
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void pushup(int p){
        t[p].sum=(t[ls].sum+t[rs].sum)%MOD;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].add=0,t[p].mul=1;
        if(l==r){
            t[p].sum=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void add(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) add(ls,fl,fr,k);
        if(mid<fr) add(rs,fl,fr,k);
        pushup(p);
    }

    void mul(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            domul(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) mul(ls,fl,fr,k);
        if(mid<fr) mul(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].sum;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret=(ret+query(ls,fl,fr))%MOD;
        if(mid<fr) ret=(ret+query(rs,fl,fr))%MOD;
        return ret;
    }

}sg;


signed main(){
    cin>>n>>q>>MOD;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sg.build(1,1,n);
    while(q--){
        int op,l,r,x;
        cin>>op>>l>>r;
        if(op==1){
            cin>>x;
            sg.mul(1,l,r,x);
        }
        if(op==2){
            cin>>x;
            sg.add(1,l,r,x);
        }
        if(op==3){
            cout<<sg.query(1,l,r)<<'\n';
        }
    }

    return 0;
}