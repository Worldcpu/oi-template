#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m;

struct FHQTreap{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson,val,dat,siz;
    }t[MN];
    int tot,rt;

    FHQTreap(){
        srand(random_device{}());
    }

    int newnode(int k){
        int p=++tot;
        t[p].lson=t[p].rson=0;
        t[p].val=k,t[p].dat=rand();
        t[p].siz=1;
        return p;
    }

    void pushup(int p){
        t[p].siz=t[ls].siz+t[rs].siz+1;
    }

    void split(int p,int k,int &x,int &y){
        if(!p){
            x=y=0;
            return;
        }
        if(k>=t[p].val){
            x=p;
            split(rs,k,rs,y);
        }else{
            y=p;
            split(ls,k,x,ls);
        }
        pushup(p);
    }
    
    int merge(int x,int y){
        if(!x||!y) return x|y;
        if(t[x].dat<t[y].dat){
            t[x].rson=merge(t[x].rson,y);
            pushup(x);
            return x;
        }else{
            t[y].lson=merge(x,t[y].lson);
            pushup(y);
            return y;
        }
    }

    void insert(int k){
        int x,y,z;
        split(rt,k,x,z);
        y=newnode(k);
        rt=merge(merge(x,y),z);
    }

    void del(int k){
        int x,y,z;
        split(rt,k,x,z);
        split(x,k-1,x,y);
        y=merge(t[y].lson,t[y].rson);
        rt=merge(merge(x,y),z);
    }

    int getrankval(int k){
        int x,y,z;
        split(rt,k-1,x,y);
        int ans=t[x].siz+1;
        rt=merge(x,y);
        return ans;
    }

    int topk(int p,int k){
        int lz=t[ls].siz;
        if(lz+1==k) return t[p].val;
        if(lz>=k) return topk(ls,k);
        else return topk(rs,k-t[ls].siz-1);
    }

    int getpre(int k){
        int x,y;
        split(rt,k-1,x,y);
        int ans=topk(x,t[x].siz);
        rt=merge(x,y);
        return ans;
    }

    int getsuf(int k){
        int x,y;
        split(rt,k,x,y);
        int ans=topk(y,1);
        rt=merge(x,y);
        return ans;
    }

}fhq;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        fhq.insert(x);
    }
    int lst=0,ans=0;
    while(m--){
        int op,x;
        cin>>op>>x;
        x^=lst;
        if(op==1){
            fhq.insert(x);
        }
        if(op==2){
            fhq.del(x);
        }
        if(op==3){
            int qwq=fhq.getrankval(x);
            ans^=qwq;
            lst=qwq;
        }
        if(op==4){
            int qwq=fhq.topk(fhq.rt,x);
            ans^=qwq;
            lst=qwq;
        }
        if(op==5){
            int qwq=fhq.getpre(x);
            ans^=qwq;
            lst=qwq;
        }
        if(op==6){
            int qwq=fhq.getsuf(x);
            ans^=qwq;
            lst=qwq;
        }
    }
    cout<<ans;
    return 0;
}