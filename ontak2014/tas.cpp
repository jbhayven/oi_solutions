#include <bits/stdc++.h>
using namespace std;

void reverse_ranges(vector<pair<int, int>> &ranges, int a, int b) {
    int min_pos = ranges[a].second;
    int max_pos = ranges[b].second;
    
    for (int i = 0; i <= (b - a) / 2; i++)
        swap(ranges[a+i], ranges[b - i]);
        
    for (int i = a; i <= b; i++)
        ranges[i].second = (max_pos + min_pos - ranges[i].second);
}

stack<pair<int, int>> ans;

bool try_find(vector<pair<int, int>> &ranges, int k) {
    if (k == 0) {
        for (size_t i = 1; i < ranges.size(); i++) 
            if (ranges[i].first < ranges[i - 1].first) return false;
        return true;
    }
    
    bool sub_result = try_find(ranges, k - 1);
    if (sub_result == true) {
        ans.push({ranges[0].second, ranges[0].second});
        return true;
    }

    for (size_t a = 0; a < ranges.size(); a += 2)
        for (size_t b = a+1; b < ranges.size(); b += 2) {
                
        reverse_ranges(ranges, a, b);
        bool sub_result = try_find(ranges, k - 1);
        reverse_ranges(ranges, a, b);

        if (sub_result == true) {
            ans.push({ranges[a].second, ranges[b].second});
            return true;
        }
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n+2);
    nums[0] = 0; nums[n+1] = n+3;
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
        
    vector<bool> jest(n+1, false);
    for (int i = 1; i <= n; i++) {
        if (jest[nums[i]]) {
            cout << "NIE" << endl;
            exit(0);
        }
        jest[nums[i]] = true;
    }
    
    vector<pair<int, int>> range_deconstr;
    int i = 1; int gr = 0;
    for (int j = 2; j <= n+1; j++) {
        if (gr == 0) gr = nums[j] - nums[j-1];
        if (abs(gr) != 1 || nums[j] - nums[j-1] != gr) {
            range_deconstr.push_back({nums[i], i});
            if ((j-1) - i == 1) {
                range_deconstr.push_back({nums[i], i});
                range_deconstr.push_back({nums[j-1], j-1});
            }
            range_deconstr.push_back({nums[j-1], j-1});
            i = j;
            gr = 0;
        }
    }
    
    if (range_deconstr.size() > 24 || !try_find(range_deconstr, k)) 
        cout << "NIE" << endl;
    else {
        cout << "TAK" << endl;
        while (!ans.empty()) {
            cout << ans.top().first << " " << ans.top().second << endl;
            ans.pop();
        }
    }
    
    return 0;
}
