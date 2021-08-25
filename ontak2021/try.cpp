#include <bits/stdc++.h>
using namespace std;

enum mode {
    CHECK,
    PRINT
};

bool process(int i, vector<pair<int, int>> &rng, mode m) {
    int last = INT_MIN;
    
    for (auto r : rng) {
        if (last == INT_MIN) {
            last = r.first;
        } else {
            if (last + i < last || last + i > r.second) return false;
            last = max(last + i, r.first);
        }
        
        if (m == PRINT)
            cout << last << " ";
    }
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; 
    cin >> n;
    
    vector<pair<int, int>> rng(n);
    
    for (auto &i : rng)
        cin >> i.first >> i.second;
        
    uint32_t left = 0, right = 2e9;
    while (left < right) {
        uint32_t mid = (left + right) / 2;
        if (process(mid + 1, rng, CHECK))
            left = mid + 1;
        else 
            right = mid;
    }
    
    if (left > 0) {
        cout << left << endl;
        process(left, rng, PRINT);
        cout << endl;
    } else {
        cout << "NIE" << endl;
    }
    
    return 0;
}
