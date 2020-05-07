#include <bits/stdc++.h>
using namespace std;

struct state_t {
    array<int, 3> vals;
    
    state_t() :
        vals{0, 0, 0}
    {}
    
    state_t(array<int, 3> tab) :
        vals(tab)
    {}
    
    const state_t operator+=(const state_t &other) {
        for (int i = 0; i < 3; i++)
            vals[i] += other.vals[i];
        
        return *this;
    } 
    
    const state_t operator-=(const state_t &other) {
        for (int i = 0; i < 3; i++)
            vals[i] -= other.vals[i];
        
        return *this;
    } 
    
    bool operator<=(const state_t &other) const {
        for (int i = 0; i < 3; i++)
            if(vals[i] > other.vals[i])
                return false;
                
        return true;
    }
    
    bool operator>=(const state_t &other) const {
        for (int i = 0; i < 3; i++)
            if(vals[i] < other.vals[i])
                return false;
                
        return true;
    }
    
    bool operator==(const state_t &other) const {
        for (int i = 0; i < 3; i++)
            if(vals[i] != other.vals[i])
                return false;
                
        return true;
    }
    
    friend istream& operator>>(istream &is, state_t &state) {
        for (int &val : state.vals) is >> val;
        
        return is;
    }
};

template <> 
class std::hash<state_t> {
public:
    size_t operator()(const state_t &state) const {
        return state.vals[0] + 100 * state.vals[1] + 10000 * state.vals[2];
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int d; cin >> d;
    while(d--) {
        state_t start, end;
        cin >> start >> end;
        
        int r; cin >> r;
        vector< pair<state_t, state_t> >rules(r);
        for(auto &rule : rules)
            cin >> rule.first >> rule.second;
            
        queue<state_t> cand;
        unordered_map<state_t, int> time;
        
        const state_t limit({20, 20, 20});
        
        time[start] = 0;
        cand.push(start);
        bool success = false;
        while(!cand.empty()) {
            state_t curr = cand.front(); cand.pop();
                    
            if(curr >= end) {
                success = true;
                cout << time[curr] << endl;
                break;
            }
                    
            for(auto &rule : rules) {
                if(curr >= rule.first) {
                    state_t new_state = curr;
                    new_state -= rule.first;
                    new_state += rule.second;
                    
                    if(new_state <= limit && time.count(new_state) == 0) {
                        time[new_state] = time[curr] + 1;
                        cand.push(new_state);
                    } 
                }
            }
        }
        
        if(!success)
            cout << "NIE" << endl;
    }
    
    return 0;
}
