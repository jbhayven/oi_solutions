#include <bits/stdc++.h>
using namespace std;

class Vertex {
    struct Centr_comp {
        using line = pair<uint64_t, uint32_t>; // line.first = base_prize, line.second = prize_per_unit
        Centr_comp* par_comp;
        vector<line> graph; 
        Vertex* center;
        
        unordered_map<Vertex*, uint64_t> dists;
    
        Centr_comp(Centr_comp *par, unordered_map<Vertex*, uint64_t> map, Vertex* v) : 
            par_comp(par), center(v), dists(map) {}
            
        double get_cross(line a, line b) {
            return (double)(b.second - a.second) / (double)(a.first - b.first);
        }
            
        uint64_t get_opt_cost(Vertex *v) {
            uint64_t dist = dists[v];
            
            if (graph.size() == 0) return UINT64_MAX;
            
            int i = 0;
            int j = graph.size() - 1;
            
            while (i != j) {
                int s = (i + j) / 2;
                
                if (get_cross(graph[s], graph[s + 1]) < dist) i = s + 1;
                else j = s;
            }
            
            return graph[i].first + dist * graph[i].second;
        }
        
        void add_source(Vertex* v, uint64_t cost, uint32_t prize_per_unit) {
            uint64_t dist = dists[v];
            
            uint64_t base_cost = cost + dist * prize_per_unit;
            line new_line = make_pair(cost, prize_per_unit);
            
            while (!graph.empty()) {
                if (graph.back().second == prize_per_unit) {
                    if (graph.back().first <= base_cost) {
                        return;
                    } else {
                        graph.pop_back();
                    }
                } else if (graph.back().second < prize_per_unit) {
                    if (graph.size() >= 2 && 
                        get_cross(graph.end()[-2], graph.end()[-1]) >= get_cross(graph.back(), new_line)) {
                            
                        graph.pop_back();
                    } else break;
                } else break;
            }
            
            graph.push_back(new_line);
        }
    };
    
    Centr_comp* comp;
    vector< pair<Vertex*, unsigned> > neigh;
    size_t size;
    uint64_t cost;
    
    void clean() {
        size = 0;
        for (auto v : neigh)
            if (v.first->comp == nullptr && v.first->size) v.first->clean();
    }
    
    size_t get_size() {
        size = 1;
        
        for (auto v : neigh)
            if (!v.first->size) size += v.first->get_size();
    
        return size;
    }
    
    Vertex* get_max_son() {
        pair<size_t, Vertex*> max_pair = make_pair(0, nullptr);
        
        for (auto v : neigh) {
            if (v.first->comp || v.first->size > size) continue;
            max_pair = max(max_pair, make_pair(v.first->size, v.first));
        }
        
        return max_pair.second;
    }
    
    bool is_centroid() {
        Vertex* max_son = get_max_son();
        
        return max_son == nullptr || max_son->size <= size / 2;
    }
    
    unordered_map<Vertex*, uint64_t> get_dist_map() {
        unordered_map<Vertex*, uint64_t> result = {{this, 0}};
        
        stack<Vertex*> to_visit;
        to_visit.push(this);
        
        while (!to_visit.empty()) {
            Vertex* curr = to_visit.top();
            to_visit.pop();
            
            for (auto v : curr->neigh) {
                if (v.first->comp || result.count(v.first) > 0) continue;
                result[v.first] = result[curr] + v.second;
                to_visit.push(v.first);
            }
        }
        
        return result;
    }
    
    void add_to_components() {
        Centr_comp *component = comp;
        while (component != nullptr) {
            component->add_source(this, cost, prize);
            component = component->par_comp;
        }
    }
public:
    uint64_t prize;
    
    Vertex() : comp(nullptr), neigh(), size(0), cost(UINT64_MAX) {}
    
    void add_neighbour(Vertex *other, unsigned len) {
        neigh.push_back(make_pair(other, len));
    }
    
    void centr_split(Centr_comp* par_comp = nullptr) {
        clean();
        get_size();
        
        Vertex* cand = this;
        while(!cand->is_centroid()) {
            cand = cand->get_max_son();
        }
        
        cand->comp = new Centr_comp(par_comp, get_dist_map(), cand);
        
        for (auto v : cand->neigh) {
            if (v.first->comp) continue;
            v.first->centr_split(cand->comp);
        }
    }
    
    void set_start() {
        cost = 0;
        
        add_to_components();
    }
    
    void set_opt_cost() {
        Centr_comp* component = comp;
        
        while (component != nullptr) {
            cost = min(cost, component->get_opt_cost(this));
            component = component->par_comp;
        }
    }
    
    void add_to_results() {
        set_opt_cost();
    
        add_to_components();
    }
    
    uint64_t get_cost() {
        return cost;
    }
    
    ~Vertex() {
        if (comp != nullptr) delete comp;
    }
};

void solve() {
    int n, s, t;
    cin >> n >> s >> t;
    s--, t--;
    
    vector<Vertex> vertices(n);
    
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        vertices[i].prize = p;
    }
    
    vertices[t].prize = 0;
    
    for (int i = 0; i < n - 1; i++) {
        int a, b, d; 
        cin >> a >> b >> d;
        
        a--, b--;
        
        vertices[a].add_neighbour(&vertices[b], d);
        vertices[b].add_neighbour(&vertices[a], d);
    }
    
    vertices[0].centr_split();
    
    vector<Vertex*> ordered({ &vertices[s] });
    for (Vertex &v : vertices)
        if (v.prize < vertices[s].prize)
            ordered.push_back(&v);
    
    sort(ordered.begin(), ordered.end(), 
         [](Vertex *a, Vertex *b){ 
             return a->prize < b->prize; 
         });
    
    vertices[s].set_start();
    for (Vertex *v : ordered)
        v->add_to_results();
    
    vertices[t].set_opt_cost();
    
    cout << vertices[t].get_cost() << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int z; cin >> z; while(z--) solve();
    
    return 0;
}
