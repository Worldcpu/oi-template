#include<bits/stdc++.h>
using namespace std;
int n,ans;

namespace FASTIO{
    #ifndef LOCAL
        constexpr auto maxn=1<<20;
        char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;
        #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
        #define flush() (fwrite(out,1,p3-out,stdout))
        #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
        class Flush{public:~Flush(){flush();}}_;
    #endif
    #ifdef LOCAL
        #define getchar getchar_unlocked
        #define putchar putchar_unlocked
    #endif
    template<typename type>
    void read(type &x){
        x=0;bool flag(0);char ch=getchar();
        while(!isdigit(ch)) flag=ch=='-',ch=getchar();
        while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
        flag?x=-x:0;
    }
    void read(char &x){do{x=getchar();}while(isspace(x));}
    void read(char x[]){static char ch;ch=getchar();do{*(x++)=ch;}while(!isspace(ch=getchar())&&~ch);}
    void read(string &st){st.clear();static char ch;ch=getchar();do{st+=ch;}while(!isspace(ch=getchar())&&~ch);}
    template<typename type,typename... T>
    void read(type& x,T&... t){
        read(x);
        read(t...);
    }
    
    template<typename type>
    void write(type x){
        x<0?x=-x,putchar('-'):0;
        static short st[50],top(0);
        do{st[++top]=x%10,x/=10;}while(x);
        while(top) putchar(st[top--]|48);
    }
    void write(const char &x){putchar(x);}
    void write(const char ch[]){while(*ch) putchar(*(ch++));}
    void write(string &st){for(auto p:st) putchar(p);}
    template<typename type>
    void put(type x,bool flag=1){
        write(x);
        flag?putchar('\n'):putchar(' ');
    }
    #undef getchar
    #undef putchar
}using namespace FASTIO;


int main(){
    read(n);
    for(int i=1;i<=n;i++){
        int x;
        read(x);
        ans+=x;
    }   
    put(ans);

    return 0;
}