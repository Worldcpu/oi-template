#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,m,tmp[MN];

struct FHQTreap{
    #define ls t[p].lson
    #define rs t[p].rson

    struct SNode{
        int lson,rson,dat,val,siz;
        int sum,pre,suf,msum;
        int covnum,iscov;
        bool isrev;
    }t[MN];
    int tot,gc[MN],top,rt;
    mt19937 mt;
    
    FHQTreap(){
        mt.seed(random_device{}());
        t[0].msum=-1e9;
        tot=top=rt=0;
    }

    int newnode(int val){
        int p=(top?gc[top--]:++tot);
        memset(&t[p],0,sizeof(t[p]));

        t[p].dat=mt();
        t[p].siz=1;
        t[p].val=t[p].sum=t[p].msum=val;
        t[p].pre=t[p].suf=max(0ll,val);

        return p;
    }

    void pushup(int p){
        t[p].siz = t[ls].siz + t[rs].siz + 1;
        t[p].sum = t[ls].sum + t[p].val + t[rs].sum;

        t[p].pre = max({ t[ls].pre, t[ls].sum + t[p].val + t[rs].pre, 0LL });
        t[p].suf = max({ t[rs].suf, t[rs].sum + t[p].val + t[ls].suf, 0LL });

        t[p].msum = max({ t[p].val, t[ls].suf + t[p].val + t[rs].pre,
                          t[ls].msum, t[rs].msum });
    }

    void docov(int p){
        if(!p) return;
        if(!t[p].iscov) return;     

        int c = t[p].covnum;
        int cs = c * t[p].siz;
        t[p].val = c;
        t[p].sum = cs;

        t[p].msum = max(t[p].val, t[p].sum);
        t[p].pre = t[p].suf = max(cs, 0LL);

        if (t[p].lson) { t[t[p].lson].iscov = 1; t[t[p].lson].covnum = c; }
        if (t[p].rson) { t[t[p].rson].iscov = 1; t[t[p].rson].covnum = c; }

        t[p].covnum = t[p].iscov = 0;
    }

    void dorev(int p){
        if(!p) return;
        if(!t[p].isrev) return;
    
        swap(t[p].lson,t[p].rson);
        swap(t[p].pre,t[p].suf);

        if(t[p].lson) t[t[p].lson].isrev ^= 1;
        if(t[p].rson) t[t[p].rson].isrev ^= 1;
        t[p].isrev=0;
    }

    void pushdown(int p){
        if(!p) return;
        // apply current node's lazy to itself and mark children (as in original correct code)
        docov(p);
        dorev(p);

        // Also ensure children's lazy states are applied similarly (keep consistent with original)
        if(t[p].lson){
            docov(t[p].lson);
            dorev(t[p].lson);
        }
        if(t[p].rson){
            docov(t[p].rson);
            dorev(t[p].rson);
        }
    }

    void split(int p,int k,int &x,int &y){
        if(!p){
            x=y=0;
            return;
        }
        pushdown(p);
        if(k>t[ls].siz){
            x=p;
            k-=t[ls].siz+1;
            split(t[p].rson,k,t[p].rson,y);
        }else{
            y=p;
            split(t[p].lson,k,x,t[p].lson);
        }
        pushup(p);
    }

    int merge(int x,int y){
        if(!x||!y) return x ? x : y;
        if(t[x].dat<t[y].dat){
            pushdown(x);
            t[x].rson=merge(t[x].rson,y);
            pushup(x);
            return x;
        }else{
            pushdown(y);
            t[y].lson=merge(x,t[y].lson);
            pushup(y);
            return y;
        }
    }

    // --- 修改：统一使用 (pos, len) 约定，与题解一致 ---
    void getqj(int pos,int len,int &x,int &y,int &z){
        if(len <= 0){
            x = rt; y = z = 0;
            return;
        }
        int l = pos;
        int r = pos + len - 1;
        split(rt,r,x,z);
        split(x,l-1,x,y);
    }

    // -----------------build--------------------
    
    int build(int l,int r,int a[]){
        if(l==r){
            return newnode(a[l]);
        }
        int mid=(l+r)>>1;
        return merge(build(l,mid,a),build(mid+1,r,a));
    }

    void insert(int pos,int tot,int a[]){
        int x,y,z;
        split(rt,pos,x,z);
        y=build(1,tot,a);
        rt=merge(merge(x,y),z);
    }

    void pushback(int k){
        rt=merge(rt,newnode(k));
    }

    // ----------------delete------------------


    void gcnode(int p){
        if(!p) return;
        gc[++top]=p;
        gcnode(t[p].lson);
        gcnode(t[p].rson);
    }

    void del(int pos,int tot){
        int x,y,z;
        // 修改：使用 (pos, tot) 语义
        getqj(pos,tot,x,y,z);
        gcnode(y);
        rt=merge(x,z);
    }

    //-----------------reverse----------------

    void reverse(int pos,int len){
        int x,y,z;
        getqj(pos,len,x,y,z);
        if(y){
            t[y].isrev^=1;
            dorev(y);
        }
        rt=merge(merge(x,y),z);
    }

    //-----------------cover----------------

    void cover(int pos,int len,int k){
        int x,y,z;
        getqj(pos,len,x,y,z);
        if(y){
            t[y].iscov=1;
            t[y].covnum=k;
            docov(y);
        }
        rt=merge(merge(x,y),z);
    }

    //------------------query---------------

    int getsum(int pos,int len){
        int x,y,z;
        getqj(pos,len,x,y,z);
        int ans = 0;
        if(y) ans = t[y].sum;
        rt=merge(merge(x,y),z);
        return ans;
    }

    int getmsum(){
        if(!rt) return 0;
        return t[rt].msum;
    }

    #undef ls
    #undef rs
}fhq;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.setf(std::ios::fixed);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        fhq.pushback(x);
    }
    while(m--){
        string op;
        int x,y,z;
        cin>>op;
        if(op[0]=='I'){
            cin>>x>>y;
            for(int i=1;i<=y;i++){
                cin>>tmp[i];
            }
            fhq.insert(x,y,tmp);
        }
        if(op[0]=='D'){
            cin>>x>>y;
            fhq.del(x,y);
        }
        if(op[0]=='R'){
            cin>>x>>y;
            // 修改：统一为 (pos, len)
            fhq.reverse(x,y);
        }
        if(op[0]=='G'){
            cin>>x>>y;
            // 修改：统一为 (pos, len)
            cout<<fhq.getsum(x,y)<<'\n';
        }
        if(op[0]=='M'){
            if(op[2]=='K'){
                cin>>x>>y>>z;
                // 修改：统一为 (pos, len, val)
                fhq.cover(x,y,z);
            }else{
                cout<<fhq.getmsum()<<'\n';
            }
        }
    }
    return 0;
}
