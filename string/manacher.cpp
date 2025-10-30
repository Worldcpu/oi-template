#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e7+15;
int ans;
string st;

namespace Manacher{
    int p[MN];
    string s;

    void inits(const string &st){
        s.push_back('~');
        s.push_back('$');
        for(auto p:st){
            s.push_back(p);
            s.push_back('$');
        }
        s.push_back('^');
    }

    void manacher(){
        int r=0,c;
        for(int i=1;i<s.size();i++){
            if(i<r){
                p[i]=min(p[2*c-i],r-i);
            }
            while(s[i+p[i]+1]==s[i-p[i]-1]) p[i]++;
            if(p[i]+i>r){
                r=i+p[i];
                c=i;
            }
        }
    }

}

int main(){
    cin>>st;
    Manacher::inits(st);
    Manacher::manacher();
    for(int i=0;i<Manacher::s.size();i++){
        ans=max(ans,Manacher::p[i]);
    }
    cout<<ans;
    return 0;
}