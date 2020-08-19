#include <bits/stdc++.h>
using namespace std;

const int MAX_D = 205;
const int MAX_N = 5005;
const int MAX_M = 1000010;

int d, n, m;

struct add_info {
    int a, b;
    int k;
    bool changes;
    vector<int> *smaller_set;
    long long score;
} additions[MAX_M];

vector<int> *component[MAX_D][MAX_N];
unordered_set<int> *component_final[MAX_N];

void separate(vector<int> *component, int64_t &curr_score) {
    unordered_map<unordered_set<int>*, vector<int>> mappings;
    while (!component->empty()) {
        int a = component->back();
        component->pop_back();
                
        curr_score -= (2 * component_final[a]->size() - 1);
        component_final[a]->erase(a);
        mappings[component_final[a]].push_back(a);
    }
    for (auto &pair : mappings) {
        if (pair.first->empty()) {
            for (int i : pair.second) {
                pair.first->insert(i);
                curr_score += (2 * pair.first->size() - 1);
            }
        }
        else {
            unordered_set<int> *new_set = new unordered_set<int>();
            for (int i : pair.second) {
                new_set->insert(i);
                component_final[i] = new_set;
            }
            curr_score += new_set->size() * new_set->size();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> d >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> additions[i].a >> additions[i].b >> additions[i].k;
        additions[i].a--; 
        additions[i].b--; 
        additions[i].k--;;
    }
    
    for (int i = 0; i < d; i++)
        for (int j = 0; j < n; j++)
            component[i][j] = new vector<int>({j});
            
    for (int i = 0; i < m; i++) {
        int a = additions[i].a;
        int b = additions[i].b;
        int k = additions[i].k;
        
        if (component[k][a] == component[k][b]) {
            additions[i].changes = false;
            continue;
        }
        
        if (component[k][a]->size() < component[k][b]->size()) 
            swap(a, b);
        
        additions[i].changes = true;
        additions[i].smaller_set = component[k][b];
        
        for (int j : (*additions[i].smaller_set)) {
            component[k][a]->push_back(j);
            component[k][j] = component[k][a];
        }
    }
    
    /* Get final components */
    unordered_set<int> *comps_init = new unordered_set<int>();
    for (int i = 0; i < n; i++) {
        comps_init->insert(i);
        component_final[i] = comps_init;
    }
    int64_t curr_score = n * n;
    
    for (int k = 0; k < d; k++) {
        for (int j = 0; j < n; j++) {
            if (component[k][j]->empty()) 
                continue; // already considered
                
            separate(component[k][j], curr_score);
        }
    }
    
    /* Work backwards */
    for (int i = m-1; i >= 0; i--) {
        additions[i].score = curr_score;
        
        if (additions[i].changes)
            separate(additions[i].smaller_set, curr_score);
    }
    
    for (int i = 0; i < m; i++)
        cout << additions[i].score << "\n";
            
    return 0;
}
