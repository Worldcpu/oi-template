#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int x[MN],n,ans;

struct Line{
    int l,r,h,dat;

    friend bool operator<(const Line &x,const Line &y){
        return x.h<y.h;
    }
}ln[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,sum,len;
    }t[MN<<2];

    void pushup(int p){
        if(t[p].sum){
            t[p].len=x[t[p].r+1]-x[t[p].l];
        }else{
            t[p].len=t[ls].len+t[rs].len;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].len=t[p].sum=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        int l=t[p].l,r=t[p].r;
        if(fl>=x[r+1]||fr<=x[l]) return;
        if(x[l]>=fl&&x[r+1]<=fr){
            t[p].sum+=k;
            pushup(p);
            return;
        }
        int mid=(l+r)>>1;
        if(x[mid]>=fl) modify(ls,fl,fr,k);
        if(x[mid]<fr) modify(rs,fl,fr,k);
        pushup(p);
    }
}sg;


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        x[2*i-1]=x1;
        x[2*i]=x2;
        ln[2*i-1]={x1,x2,y1,1};
        ln[2*i]={x1,x2,y2,-1};
    }
    n<<=1;
    sort(ln+1,ln+1+n);
    sort(x+1,x+1+n);
    int tot=unique(x+1,x+1+n)-x-1;
    sg.build(1,1,tot-1);
    for(int i=1;i<n;i++){
        sg.modify(1,ln[i].l,ln[i].r,ln[i].dat);
        ans+=sg.t[1].len*(ln[i+1].h-ln[i].h);
    }
    cout<<ans;
    return 0;
}