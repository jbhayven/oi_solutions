#include <bits/stdc++.h>
using namespace std;
    
const int MAX_N = 1e6 + 100;
    
int to_pos[MAX_N];
    
int get_to_pos(int i) {
    i++;
    int result = 0;
        
    while (i < MAX_N) {
        result += to_pos[i];
        i += (i & -i);
    }
    
    return result;
}

/* inc for all j <= i */
void inc_pos(int i) {
    i++;
    
    while (i > 0) {
        to_pos[i]++;
        i -= (i & -i);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    string jas, malgosia;
    cin >> jas >> malgosia;
    
    array< vector< int >, ('Z' - 'A' + 1) > wyst;
    for (int i = n - 1; i >= 0; i--)
        wyst[jas[i] - 'A'].push_back(i);
    
    uint64_t result = 0;
    
    for (int i = 0; i < n; i++) {
        int pair = wyst[malgosia[i] - 'A'].back();
        wyst[malgosia[i] - 'A'].pop_back();
        
        result += (pair + get_to_pos(pair) - i);
        inc_pos(pair);
    }
    
    cout << result << endl;
    
    return 0;
}
