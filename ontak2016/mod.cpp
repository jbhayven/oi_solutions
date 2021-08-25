#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 10;
const int MOD = 1e9 + 7;

int n;

int factor[MAX_N];
unordered_set<int64_t> big_factors;

struct {
    int64_t min_compat = (int64_t) MAX_N * MAX_N;
    vector<int> points;
} cycle[2][MAX_N];

struct {
    struct {
        int no;
        int pos;
    } cycle_info;
    
    int next;
    
} info[2][MAX_N];

void create_cycles(int t) {
    vector<bool> visited(n+1, false);
    int cycle_no = 1;
    
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
    
        for (int j = i, pos = 0; !visited[j]; j = info[t][j].next, pos++) {
            visited[j] = true;
            info[t][j].cycle_info = {
                .no = cycle_no,
                .pos = pos
            };
            
            cycle[t][cycle_no].points.push_back(j);
        }
        
        cycle_no++;
    }
}

void get_result_for_cycle(int i) {
    throw std::runtime_error("Not implemented");
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    for (int i = 0; i < 2; i++)
        for (int j = 1; j <= n; j++)
            cin >> info[i][j].next;
    
    create_cycles(0);
    create_cycles(1);
    
    for (int i = 1; i <= n; i++)
        get_result_for_cycle(i);
        
    int64_t result = 1;
    auto upd_result = [result](int a) {
        result *= a;
        result %= MOD;
    } 
        
    for (int i = 1; i <= n; i++)
        for (; factor[i] > 0; factor[i]--) 
            upd_result(i);
            
    for (int64_t fact : big_factors)
        upd_result(fact % MOD);
        
    cout << result << endl;
        
    return 0;
}
