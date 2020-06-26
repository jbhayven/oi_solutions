#include <bits/stdc++.h>
using namespace std;

#define WHITE 0    
#define BLACK 1

const int MAX_N = 200100;

class Path;
    
int n;
bool color[MAX_N];
int par[MAX_N];
int depth[MAX_N], sub[MAX_N];
int ans[MAX_N];
vector< vector<int> > children(MAX_N);
Path *my_path[MAX_N];

class Path {
    int head;
    int tail;
    multiset<int> black_childed;
public:
    static const int NONE = -1;
    
    void add_black_childed(int nd) {
        black_childed.insert(nd);
    }
    
    void remove_black_childed(int nd) {
        black_childed.erase(black_childed.find(nd));
    }
    
    int get_lowest_black(int nd) {
        auto greater = black_childed.upper_bound(nd);
        
        bool can_nd;
        if (greater == black_childed.end())            
            can_nd = ((depth[tail] - depth[nd]) % 2 == 1);
        else
            can_nd = ((depth[*greater] - depth[nd]) % 2 == 0);
            
        if (can_nd) 
            return nd;
        else 
            return *--greater;
    }
    
    int get(int nd, int curr = NONE) {
        if (curr == NONE)
            curr = nd;
            
        int stopper = get_lowest_black(curr);
        
        if (stopper == NONE) {
            if (get_head() < 0) exit(1);
            int curr_pos = par[get_head()];
            
            if (curr_pos == NONE) return depth[nd];
            else {
                if ((depth[nd] - depth[curr_pos]) % 2 == 1)
                    my_path[curr_pos]->remove_black_childed(curr_pos);
                    
                int result = my_path[curr_pos]->get(nd, curr_pos);
                
                if ((depth[nd] - depth[curr_pos]) % 2 == 0)
                    my_path[curr_pos]->add_black_childed(curr_pos);
                    
                return result;
            }
        }
        
        return depth[nd] - depth[stopper] - 1;
    }
    
    void set_head(int nd) {
        head = nd;
    }
    
    void set_tail(int nd) {
        tail = nd;
    }
    
    int get_head() {
        return head;
    }
    
    Path() : head(NONE), tail(NONE), black_childed({NONE}) {}
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    par[0] = Path::NONE; depth[0] = 0;
    for(int i = 1; i <= n; i++) {
        cin >> par[i];
    
        children[par[i]].push_back(i);
        depth[i] = depth[par[i]] + 1;
    }
    
    for(int i = n; i >= 0; i--) {
        sub[i] = 1;
        color[i] = BLACK;
        
        if(children[i].empty()) {
            my_path[i] = new Path();
            my_path[i]->set_tail(i);
        }
        else {
            int best_cnt = 0;
            
            for(int ch : children[i]) {
                sub[i] += sub[ch];
                
                if (sub[ch] > best_cnt) {
                    best_cnt = sub[ch];
                    my_path[i] = my_path[ch];
                }
            }
            
            for(int ch : children[i]) {
                if (color[ch] == BLACK) {
                    color[i] = WHITE;
                    if (my_path[ch] != my_path[i])
                        my_path[i]->add_black_childed(i);
                }
            }
        }
        
        my_path[i]->set_head(i);
    }
    
    for(int i = n; i >= 1; i--) {
        ans[i] = my_path[i]->get(i);
            
        my_path[i]->set_tail(par[i]);
    }
    
    for(int i = 1; i <= n; i++)
        cout << ans[i] << "\n";
    
    return 0;
}
