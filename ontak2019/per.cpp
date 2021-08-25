#include <bits/stdc++.h>
using namespace std;

bool solve() {
    int n;
    cin >> n;
    
    vector<int> nums(n + 2, 1);
    
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
        
    for (int i = 1; i <= n; i++) {
        if (nums[i] > n) {
            return false;
        }
    }
    
    vector< int > last(n + 2, -1);
    vector< int > maybe(n + 2, -1);
    vector< bool > okay(n + 2, false);
        
    okay[0] = true;
    int i = 1;
    int prev_one = -1;
    
    while (i <= n) {
        int maks = 0;
        do {
            i++;
            if (maybe[i] > last[nums[i]] && maybe[i] >= prev_one) {
                okay[i] = true;
            }
        } while (nums[i] != 1);
        
        prev_one = last[1];
        last[1] = i;
    }
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int z; cin >> z; while(z--) {
        cout << (solve() ? "YES" : "NO") << endl;
    }
    
    return 0;
}
