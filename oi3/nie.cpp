#include <bits/stdc++.h>
using namespace std;

vector<int> legal_positionings() {
    vector< pair<int, int> > illegal = {
        {0, 7}, {0, 5}, {3, 8}, {3, 2}, {1, 6}, {1, 8}, {2, 7}, {5, 6}
    };
    
    vector<int> result;
    for(int i = 0; i < (1 << 9); i++) {
        bool is_ok = true;
        for(auto entry : illegal) {
            if((i & (1 << entry.first)) && (i & (1 << entry.second))) {
                is_ok = false;
                break;
            }
        }
        if (is_ok) result.push_back(i);
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    array< pair<int, int>, (1 << 6) > result;
    result[0] = {0, 1};
    
    int n; cin >> n;
    
    vector<int> masks = legal_positionings();
    
    for(int i = 0; i < n; i++) {
        int z; cin >> z; z--;
        
        array< pair<int, int>, (1 << 6) > new_result;
        for(auto mask : masks) {
            if (z >= 0 && (mask & (1 << z))) continue;
            
            int bonus = __builtin_popcount(mask % (1 << 3));
            int old_mask = mask >> 3;
            int new_mask = mask % (1 << 6);
            
            if(new_result[new_mask].first < result[old_mask].first + bonus)
                new_result[new_mask] = {result[old_mask].first + bonus, 0};
            
            if(new_result[new_mask].first == result[old_mask].first + bonus)
                new_result[new_mask].second += result[old_mask].second;
        }
        
        result = new_result;
    }
    
    pair<int, int> final_result{0, 0};
    for(auto entry : result) {
        if(entry.first > final_result.first)
            final_result = {entry.first, 0};
            
        if(entry.first == final_result.first)
            final_result.second += entry.second;
    }
    
    cout << final_result.first << " " << final_result.second << endl;
    return 0;
}
