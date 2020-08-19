#include <bits/stdc++.h>
using namespace std;

vector< vector<int>> rozw;

void put(vector<int> &perm, vector<bool> &taken, int first_sum,
         const array< vector<int>, 6 > &nums_in_perm, 
         const int min[], const int maks[], int in_pos[], const int k,
         int curr_pos = 0) {
    
    if (curr_pos == k) {
        fill(taken.begin(), taken.end(), false);
        int perm_elem = 1;
        
        for (int off_no = 0; off_no < k; off_no++) {
            int curr = in_pos[off_no];
            
            while(taken[perm_elem]) 
                perm_elem++;
            
            if (perm_elem + maks[curr] - min[curr] > perm.size()) 
                return;
        
            int base = perm_elem - min[curr];
            
            if (off_no == k - 1) {
                int check = 0;
                for (int j = 0; j < k; j++) 
                    check += j == curr ? base : perm[j];
                if (check != first_sum)
                    return;
            }
            
            int j = curr;
            for (int bonus : nums_in_perm[curr]) {
                int curr_perm_elem = base + bonus;
                if (taken[curr_perm_elem])
                    return;
                
                taken[curr_perm_elem] = true;
                perm[j] = curr_perm_elem;
                j += k;
            }
        }
        
        rozw.push_back(perm);
    }
    
    for (int i = 0; i < k; i++)
        if (in_pos[i] == -1) {
            in_pos[i] = curr_pos;
            put(perm, taken, first_sum, nums_in_perm, min, maks, in_pos, k, curr_pos + 1);
            in_pos[i] = -1;
        }
}

void solve() {
    int n, k; cin >> n >> k;
    vector<int> sums(n - k + 1);
    for (int &i : sums) cin >> i;
    
    array< vector<int>, 6 > nums_in_perm;
    for (int i = 0; i < k; i++) {
        int grow = 0;
        nums_in_perm[i].push_back(0);
        for (int j = i; j < (n - k); j += k) {
            grow += sums[j + 1] - sums[j];
            nums_in_perm[i].push_back(grow);
        } 
    }
    
    int min[6], maks[6];
    for (int i = 0; i < k; i++) {
        min[i] = *std::min_element(nums_in_perm[i].begin(), nums_in_perm[i].end());
        maks[i] = *std::max_element(nums_in_perm[i].begin(), nums_in_perm[i].end());
    }
    
    vector<int> perm(n, -1);
    vector<bool> taken(n + 1, false);
    int in_pos[6] = {-1, -1, -1, -1, -1, -1};
    
    rozw.clear();
    put(perm, taken, sums[0], nums_in_perm, min, maks, in_pos, k);
    
    cout << rozw.size() << endl;
    for (auto &v : rozw) {
        for (int i : v) cout << i << " ";
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int z; cin >> z; while(z--) {
        solve();
    }
    
    return 0;
}
