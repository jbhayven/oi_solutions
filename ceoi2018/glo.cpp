#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 202001;

int n, x;
int nums[MAX_N];

int long_left[MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> x;
    
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    
    set< pair<int, int> > best_results({{-1e9, 0}, {2e9, MAX_N}});
    for(int i = 1; i <= n; i++) {
        long_left[i] = (--best_results.lower_bound({nums[i], 0}))->second + 1;
        pair<int, int> entry = {nums[i], long_left[i]};
        
        // set contains pairs (a_1, b_1) and (a_2, b_2) if a_1 <= a_2 and b_1 < b_2
        while(best_results.lower_bound(entry)->second <= long_left[i])
            best_results.erase(best_results.lower_bound(entry));
        best_results.insert(entry);
    }
    
    int result = 0;
    best_results = set< pair<int, int> >({{-1e9, MAX_N}, {2e9, 0}}); // reinitialize
    for(int i = n; i > 0; i--) {
        result = max(result, long_left[i] + best_results.lower_bound({nums[i] - x + 1, 0})->second);

        int longest = best_results.lower_bound({nums[i] + 1, 0})->second + 1;
        pair<int, int> entry = {nums[i], longest};
        
        // set contains pairs (a_1, b_1) and (a_2, b_2) if a_1 <= a_2 and b_1 > b_2
        while((--best_results.lower_bound(entry))->second <= longest)
            best_results.erase(--best_results.lower_bound(entry));
        best_results.insert(entry);
    }
    
    cout << result << endl;
    
    return 0;
}
