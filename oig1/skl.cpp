#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    unordered_map<int, int> cnt;
    vector<int> ord;
    
    while(n--) {
        int a, k;
        cin >> a >> k;
        
        cnt[a] += k;
        ord.push_back(a);
    }
    
    cout << cnt.size() << endl;
    
    for (int i : ord) {
        if (cnt.count(i)) {
            cout << i << " "  << cnt[i] << "\n";
            cnt.erase(i);
        }
    }
    
    return 0;
}
