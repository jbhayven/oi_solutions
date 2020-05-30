#include <bits/stdc++.h>
using namespace std;
    
using result_t = pair<int, multiset<int>>;

namespace std {
    template<>
    struct hash<result_t> {
        size_t operator()(const result_t &result) const {
            size_t result_hash = result.first;
            for(int fact : result.second) {
                result_hash *= 107;
                result_hash ^= fact;
            }
            return result_hash;
        }
    };
}
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    vector<int> factors;    
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if(n > 1) factors.push_back(n);
    
    unordered_set<int> divisors({1});
    
    while(!factors.empty()) {
        unordered_set<int> new_div;
        for(int div: divisors)
            new_div.insert(div * factors.back());
        divisors.merge(new_div);
        factors.pop_back();
    }
    
    vector<int> sorted_div;
    for(int div: divisors) sorted_div.push_back(div);
    sort(sorted_div.begin(), sorted_div.end());
    
    unordered_map<int, unordered_set<int>> options;
    options[1] = {0};
    
    for(int div: divisors) {
        for(int bulk : sorted_div) {
            if(bulk % div != 0) continue;
            for(int sum : options[bulk / div])
                options[bulk].insert(sum + div - 1);
        }
    }
    
    vector<int> sorted_result;
    for(int div: options[sorted_div.back()])
        sorted_result.push_back(div);
    sort(sorted_result.begin(), sorted_result.end());
    
    cout << sorted_result.size() << endl;
    for(int sum: sorted_result)
        cout << sum << " ";
    cout << endl;
    
    return 0;
}
