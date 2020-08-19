#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int z; cin >> z; while (z--) {
        int n; cin >> n;
        
        vector<int> nums(n);
        long long sum = 0;
        for (int &i: nums) {
            cin >> i;
            sum += i;
        }
        
        sort(nums.begin(), nums.end());
        while (!nums.empty() && nums.back() >= sum - nums.back()) {
            sum -= nums.back();
            nums.pop_back();
        }
        
        cout << sum << endl;
    }
    
    return 0;
}
