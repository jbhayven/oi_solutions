#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    size_t n, k; cin >> n >> k;
    
    vector<int> cost(k);
    for(int &v : cost) cin >> v;
    sort(cost.begin(), cost.end());
    
    priority_queue<int, vector<int>, greater<int> > prefixes(cost.begin(), cost.end());
    
    while(prefixes.size() < n) {
        int disc = prefixes.top();
        prefixes.pop();
        
        for(int v : cost) 
            prefixes.push(disc + v);
    }
    
    multiset<int> lang;
    long long result = 0;
    for(size_t i = 0; i < n; i++) {
        lang.insert(prefixes.top());
        result += prefixes.top();
        prefixes.pop();
    }
    
    bool should_continue = true;
    while(should_continue) {
        stack<int> removed;
        
        int disc = *lang.begin();
        lang.erase(lang.begin());
        
        int profit = disc;
        
        for(int v : cost) {
            if(lang.size() == n) {
                if(disc + v >= *lang.rbegin())
                    break;
                profit += *(lang.rbegin());
                removed.push(*(lang.rbegin()));
                lang.erase(--lang.end());
            }
            profit -= (disc + v);
            lang.insert(disc + v);
        }
        
        if(profit <= 0) {
            for(int v : cost) {
                if(removed.empty()) 
                    break;
                    
                auto it = lang.find(disc + v);
                lang.erase(it);
                
                lang.insert(removed.top());
                removed.pop();
            }
            lang.insert(disc);
            should_continue = false;
        }
        else result -= profit;
    }
    
    cout << result << endl;
    
    return 0;
}
