#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 10;

int seq[MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n; 
    
    for (int i = 1; i <= n; i++)
        cin >> seq[i];
        
    int p; cin >> p;
    
    for (int i = 1; i <= p; i++) {
        int a, b;
        cin >> a >> b;
        if (b - a > 70) cout << "TAK" << endl;
        else {
            vector<int> nums;
            for (int j = a; j <= b; j++) 
                nums.push_back(seq[j]);
            sort(nums.begin(), nums.end());
            
            bool found = false;
            for (int j = 2; j < nums.size(); j++)
                if (nums[j-2] + nums[j-1] > nums[j]) {
                    found = true;
                    cout << "TAK" << endl;
                    break;
                } 
                
            if (!found) cout << "NIE" << endl;
        }
    }
    
    return 0;
}
