#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <map>
#include <algorithm>
#include <cassert>

using Vertex = int;
using Length = long long;
const Length INF = std::numeric_limits<long long>::max();
using Edge = std::pair<Vertex, Length>;
using Graph = std::vector<std::vector<Edge>>;

class BlockHeap {
    public:
        BlockHeap(int M, Length B);
        void insert(Vertex v, Length l);
        void batch_prepend(const std::vector<std::pair<Vertex, Length>>& L);
        std::pair<Length ,std::vector<Vertex>> pull();
        bool empty();
        void debug();

    private:
        int M_;
        Length B_;

        std::set<std::pair<Length, Vertex>> que_;
        std::unordered_map<Vertex, Length> d_;
};

BlockHeap::BlockHeap(int M, Length B) {
    M_ = M;
    B_ = B;
}

std::pair<Length, std::vector<Vertex>> BlockHeap::pull() {
    std::vector<Vertex> S;
    for(int i = 0; i < M_; i++) {
        if(que_.empty()) {
            break;
        }
        std::pair<Length, Vertex> p = *que_.begin();
        que_.erase(p);
        d_.erase(p.second);
        S.push_back(p.second);
    }
    if(que_.empty()) {
        return std::make_pair(B_, S);
    } else {
        return std::make_pair(que_.begin()->first, S);
    }
}

void BlockHeap::batch_prepend(const std::vector<std::pair<Vertex, Length>>& L) {
    for(int i = 0; i < (int)L.size(); i++) {
        insert(L[i].first, L[i].second);
    }
}

void BlockHeap::insert(Vertex v, Length l) {
    if(d_.count(v) != 0 && d_[v] < l) {
        return;
    } else if (d_.count(v) != 0 && d_[v] >= l) {
        que_.erase(std::make_pair(d_[v], v));
    }
    que_.insert(std::make_pair(l, v));
    d_[v] = l;
}

bool BlockHeap::empty() {
    return que_.empty();
}

void BlockHeap::debug() {
    std::cout << "D= [";
    for(auto p: que_) {
        std::cout << "(V=" << p.second << ", v=" << p.first << "), ";
    }
    std::cout << "]" << std::endl;
}

class Heap {
    public:
        void push(Vertex v, Length l);
        std::pair<Vertex, Length> top();
        void pop();
        bool empty();
        void debug();

    private:
        int M_;
        Length B_;

        std::set<std::pair<Length, Vertex>> que_;
        std::unordered_map<Vertex, Length> d_;

};

void Heap::push(Vertex v, Length l) {
    if(d_.count(v) != 0 && d_[v] < l) {
        return;
    } else if (d_.count(v) != 0 && d_[v] >= l) {
        que_.erase(std::make_pair(d_[v], v));
    }
    que_.insert(std::make_pair(l, v));
    d_[v] = l;
}

std::pair<Vertex, Length> Heap::top() {
    auto p = *que_.begin();
    return std::make_pair(p.second, p.first);
}

void Heap::pop() {
    d_.erase(top().second);
    que_.erase(que_.begin());
}

bool Heap::empty() {
    return que_.empty();
}

void Heap::debug() {
    std::cout << "H= [";
    for(auto p: que_) {
        std::cout << "(V=" << p.second << ", v=" << p.first << "), ";
    }
    std::cout << "]" << std::endl;
}

class ShortestPath {
    public:
        ShortestPath(Vertex s, const Graph& G);
        std::pair<Length, std::vector<Vertex>> BMSSP(int l, Length B, const std::vector<Vertex>& S);
        std::pair<std::vector<Vertex>, std::vector<Vertex>> find_pivots(Length B, const std::vector<Vertex>& S);
        void print_dhat();

    private:
        int t_;
        int k_;
        std::vector<Length> dhat_;
        Graph G_;

        std::pair<Length, std::vector<Vertex>> base_case(Length B, const std::vector<Vertex>& S);

        std::vector<Vertex> prev_;
        std::vector<int> tree_size_;
        std::vector<std::vector<Vertex>> F_;
};

ShortestPath::ShortestPath(Vertex s, const Graph& G) {
    G_ = G;
    int N = G_.size();
    k_ = std::ceil(pow(std::log2(N), 1.0 / 3.0));
    t_ = std::floor(pow(std::log2(N), 2.0 / 3.0));
    dhat_ = std::vector<Length>(N, INF);
    dhat_[s] = 0;
    prev_ = std::vector<Vertex>(N, -1);
    tree_size_ = std::vector<Vertex>(N, -1);
    F_ = std::vector<std::vector<Vertex>>(N, std::vector<Vertex>());
}

namespace {
    int find_tree_size(int u, std::vector<int>& tree_size, const std::vector<std::vector<Vertex>>& F) {
        if(tree_size[u] != -1) return tree_size[u];
        int res = 1;
        for(int i = 0; i < (int)F[u].size(); i++) {
            Vertex v = F[u][i];
            res += find_tree_size(v, tree_size, F);
        }
        return tree_size[u] = res;
    }

    void debug_vertex_set(std::vector<Vertex> S) {
        std::cout << "[";
        for(int i = 0; i < (int)S.size(); i++) {
            std::cout << S[i] << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

void ShortestPath::print_dhat() {
    for(int i = 0; i < (int)dhat_.size(); i++) {
            std::cout << dhat_[i] << ' ';
    }
    // std::cout << "[";
    // for(int i = 0; i < (int)dhat_.size(); i++) {
    //     if(dhat_[i] == INF) {
    //         std::cout << "INF" << ", ";
    //     } else {
    //         std::cout << dhat_[i] << ", ";
    //     }
    // }
    // std::cout << "]" << std::endl;
}

std::pair<Length, std::vector<Vertex>> ShortestPath::BMSSP(int l, Length B, const std::vector<Vertex>& S) {
    // std::cout << "BMSSP k=" << k_ << ", t=" << t_ << ", l=" << l << ", B=" << B << ", S=";
    // debug_vertex_set(S);
    // print_dhat();
    if(l == 0) {
        return base_case(B, S);
    }
    auto pw = find_pivots(B, S);
    std::vector<Vertex> P = pw.first; std::vector<Vertex> W = pw.second;
    // std::cout << "P= "; debug_vertex_set(P);
    // std::cout << "W= "; debug_vertex_set(W);

    int M = std::pow(2, (l - 1) * t_);
    BlockHeap D(M, B);
    Length Bd = INF;
    for(int i = 0; i < (int)P.size(); i++) {
        Vertex u = P[i];
        D.insert(u, dhat_[u]);
        Bd = std::min(Bd, dhat_[u]);
    }
    // D.debug();
    std::unordered_set<Vertex> U;

    while((int)U.size() < k_ * std::pow(2, l * t_) && !D.empty()) {
        auto bs = D.pull();
        Length Bi = bs.first; std::vector<Vertex> Si = bs.second;
        auto bu = BMSSP(l - 1, Bi, Si);
        Length Bid = bu.first; std::vector<Vertex> Ui = bu.second;
        // std::cout << "Bid=" << Bid << std::endl;
        // std::cout << "Ui="; debug_vertex_set(Ui);
        // std::cout << "U="; debug_vertex_set(std::vector<Vertex>(U.begin(), U.end()));
        for(int j = 0; j < (int)Ui.size(); j++) {
            // if(U.count(Ui[j]) != 0) {
            //     std::cout << "Ufound" << " " << Ui[j] << " " << dhat_[Ui[j]] << " " << Bi << " " << Bid << std::endl;
            // }
            U.insert(Ui[j]);
        }

        std::vector<std::pair<Vertex, Length>> K;
        for(int j = 0; j < (int)Ui.size(); j++) {
            Vertex u = Ui[j];
            for(int k = 0; k < (int)G_[u].size(); k++) {
                Vertex v = G_[u][k].first; Length w = G_[u][k].second;
                if(dhat_[v] >= dhat_[u] + w) {
                    Length new_dist = dhat_[u] + w;
                    dhat_[v] = new_dist;
                    if(Bi <= new_dist && new_dist < B) {
                        D.insert(v, new_dist);
                    } else if(Bid <= new_dist && new_dist < Bi) {
                        K.push_back(std::make_pair(v, new_dist));
                    }
                }
            }
        }
        for(int i = 0; i < (int)Si.size(); i++) {
            int u = Si[i];
            if(Bid <= dhat_[u] && dhat_[u] < Bi) K.push_back(std::make_pair(u, dhat_[u]));
        }
        D.batch_prepend(K);
        Bd = Bid;
    }
    Bd = std::min(Bd, B);
    for(int i = 0; i < (int)W.size(); i++) {
        Vertex u = W[i];
        if(dhat_[u] < Bd) U.insert(u);
    }
    if(l == 3) {
        for(int i = 0; i < (int)G_.size(); i++) {
            // if(!U.count(i) && dhat_[i] != INF) {
            //     std::cout << "found: " << i << " " << dhat_[i] << std::endl;
            // }
        }
    }
    // std::cout << "BMSSP k=" << k_ << ", t=" << t_ << ", l=" << l << ", B=" << B << ", Bd=" << Bd << std::endl;
    // std::cout << "U size:=" << U.size() << " " << (D.empty() ? "empty" : "notempty") << std::endl;
    return std::make_pair(Bd, std::vector<Vertex>(U.begin(), U.end()));
}

std::pair<Length, std::vector<Vertex>> ShortestPath::base_case(Length B, const std::vector<Vertex>& S) {
    assert(S.size() == 1);

    Vertex x = S[0];
    // std::cout << "base_case k=" << k_ << ", t=" << t_ << ", B=" << B << ", x=" << x << std::endl; 

    std::unordered_set<Vertex> U0(S.begin(), S.end());
    Heap H;
    H.push(x, dhat_[x]);

    while(!H.empty() && (int)U0.size() < k_ + 1) {
        auto p = H.top(); H.pop();
        Vertex u = p.first; Length d = p.second;
        U0.insert(u);

        for(int i = 0; i < (int)G_[u].size(); i++) {
            int v = G_[u][i].first; Length w = G_[u][i].second;
            if(dhat_[v] >= dhat_[u] + w && dhat_[u] + w < B) {
                dhat_[v] = dhat_[u] + w;
                H.push(v, dhat_[v]);
            }
        }
        // H.debug();
    }

    if((int)U0.size() <= k_) {
        return make_pair(B, std::vector<Vertex>(U0.begin(), U0.end()));
    } else {
        Length Bd = -INF;
        std::vector<Vertex> U;
        for(auto u: U0) {
            Bd = std::max(Bd, dhat_[u]);
        }
        for(auto u: U0) {
            if(dhat_[u] < Bd) {
                U.push_back(u);
            }
        }
        return make_pair(Bd, U);
    }
}


std::pair<std::vector<Vertex>, std::vector<Vertex>> ShortestPath::find_pivots(Length B, const std::vector<Vertex>& S) {
    std::unordered_set<Vertex> W(S.begin(), S.end());
    std::vector<Vertex> Wp = S;

    for(auto v: W) {
        prev_[v] = -1;
    }

    for(int i = 0; i < k_; i++) {
        std::vector<Vertex> Wi; 
        for(int j = 0; j < (int)Wp.size(); j++) {
            Vertex u = Wp[j];
            for(int k = 0; k < (int)G_[u].size(); k++) {
                Vertex v = G_[u][k].first; Length w = G_[u][k].second;
                if(dhat_[v] >= dhat_[u] + w) {
                    dhat_[v] = dhat_[u] + w;
                    prev_[v] = u;
                    // if(dhat_[u] + w < B) {
                        Wi.push_back(v);
                    // }
                }
            }
        }
        for(int k = 0; k < (int)Wi.size(); k++) {
            W.insert(Wi[k]);
        }
        if((int)W.size() >= k_ * (int)S.size()) {
            return std::make_pair(S, std::vector<Vertex>(W.begin(), W.end()));
        }
        Wp = Wi;
        // std::cout << "Wp ="; debug_vertex_set(Wp);
    }

    for(auto v: W) {
        tree_size_[v] = -1;
        F_[v].clear();
    }
    for(auto v: W) {
        Vertex u = prev_[v];
        if(u == -1) continue;
        F_[u].push_back(v);
    }
    std::vector<Vertex> P;
    for(int i = 0; i < (int)S.size(); i++) {
        Vertex u = S[i];
        // std::cout << "find_tree_size: " << u << " " << find_tree_size(u, tree_size_, F_) << std::endl;
        if(find_tree_size(u, tree_size_, F_) >= k_ && prev_[u] == -1) {
            P.push_back(u);
        }
    }
    return std::make_pair(P, std::vector<Vertex>(W.begin(), W.end()));
}




void find_shortest_path(int s, const Graph& G) {
    int N = (int)G.size();
    double t = std::floor(std::pow(std::log2(N), 2.0 / 3.0));
    double l = std::ceil(std::log2(N) / t);
    ShortestPath shortest_path(s, G);
    std::vector<Vertex> S;
    S.push_back(s);
    auto bu = shortest_path.BMSSP(l, INF, S);
    // std::cout << "Bfinal:=" << bu.first << std::endl;
    shortest_path.print_dhat();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, s;
    std::cin >> N >> M >> s;
    s--;
    Graph G(N);
    for(int i = 0; i < M; i++) {
        int a, b; Length c;
        std::cin >> a >> b >> c;
        a--,b--;
        G[a].push_back(std::make_pair(b, c));
    }
    find_shortest_path(s, G);
    return 0;
}