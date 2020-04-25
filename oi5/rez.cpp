#include <bits/stdc++.h>
using namespace std;

const int MAX_K = 30100;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    vector< pair<int, int> > zam(n);
    
    for(auto &z : zam)
        cin >> z.first >> z.second;
        
    auto comp = [](auto a, auto b) {
        return a.second != b.second 
               ? a.second > b.second 
               : a.first > b.first;
    };
        
    sort(zam.begin(), zam.end(), comp);
    
    vector<int> best_use(MAX_K, 0);
    
    for(int i = 1; i <= MAX_K; i++) {
        best_use[i] = best_use[i-1];
        while(!zam.empty() && zam.back().second == i) {
            auto z = zam.back();
            zam.pop_back();
            
            best_use[i] = max(best_use[i], best_use[z.first] + (i - z.first));
        }
    }
    
    cout << best_use[MAX_K] << endl;
    
    return 0;
}
