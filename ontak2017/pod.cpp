#include <bits/stdc++.h>
using namespace std;

class Automaton {
    struct State {
        unordered_map<char, State*> trans;
        State* suflink;
        int len;
        int pos;
        
        State(int pos) :
            trans(),
            suflink(nullptr),
            len(0),
            pos(pos) {}
        
        void attach(char c, State* other) {
            trans[c] = other;
            other->len = max(other->len, len + 1);
        }
        
        State *get_next(char c) {
            if (trans.count(c) == 0) return nullptr;
             
            return trans.at(c);
        }
    };
    
    State* start;
    State* last_state;
    string s;
    
    /* *c* belongs to [a-z] */
    void add_char(char c) {
        State* s = new State(last_state->pos + 1);
        State* mod = last_state;
        
        while (mod != nullptr && mod->get_next(c) == nullptr) {
            mod->attach(c, s);
            mod = mod->suflink;
        }
        if (mod != nullptr) {
            State* orig = mod->get_next(c);
            if (orig->len == mod->len + 1) {
                s->suflink = orig;
            } else {
                State* clone = new State(*orig);
                clone->len = mod->len + 1;
                orig->suflink = clone;
                
                while (mod != nullptr && mod->get_next(c) == orig) {
                    mod->attach(c, clone);
                    mod = mod->suflink;
                }
                s->suflink = clone;
            }
        }
        else s->suflink = start;
        
        last_state = s;
    }
public:
    Automaton(string s) : start(new State(0)), last_state(start), s(s) {
        for (char c : s) add_char(c);
    }
    
    long long get_pass_cnt() {
        stack<State*> to_check;
        State* curr = start;
        for (char c : s) {
            curr = curr->get_next(c);
            to_check.push(curr);
        }
        long long ans = 0;
        
        unordered_set<State*> visited;
        
        while(!to_check.empty()) { 
            State* curr = to_check.top(); to_check.pop();
            int init_depth = curr->pos;
            
            while(curr != start && visited.find(curr) == visited.end()) {
                visited.insert(curr);
                State* next = curr->suflink;
                if (init_depth - curr->pos > next->len)
                    ans += min(init_depth - curr->pos, curr->len) - next->len;
                curr = next;
            }
        }
        
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    string s; cin >> s;
    Automaton A(s);
    cout << A.get_pass_cnt() << endl;
    
    return 0;
}
