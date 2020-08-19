#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, k;
    cin >> n >> k;
        
    int mob = 0;
    long long sum = 0;
    priority_queue<int> planets;
    vector<int> nums(n);
    for (int &i: nums) {
        cin >> i;
        sum += i;
    }
    
    sort (nums.begin(), nums.end());
    
    for (int i: nums) {
        while (k < i) {
            cout << k << " " << i << endl;
            if (planets.empty()) {
                cout << -1 << endl;
                return;
            }
            
            mob++;
            k += planets.top();
            sum -= planets.top();
            planets.pop();
        }
        planets.push(i);
    }
    
    while (k < sum) {
        mob++;
        k += planets.top();
        sum -= planets.top();
        planets.pop();
    }
    
    cout << mob << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int z; cin >> z; while(z--) {
        solve();
    }
    return 0;
}
