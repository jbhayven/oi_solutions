#include <bits/stdc++.h>
using namespace std;

vector< vector<bool> > answers;

bool verify(const vector<int> &pals, const vector<bool> &seq) {
    if (seq.size() != pals.size()) return false;
    
    int k = 0;
    int center = 0;
    for (int i = 1; i < pals.size(); i++) {
        if (i > k) {
            center = i;
            k = i;
        }
        
        int result;
        
        if (center == i) result = 0;
        else result = min(pals[center - (i - center)], k - i) + 1;
        
        while (i - result >= 0 && 
               i + result < seq.size() && 
               seq[i - result] == seq[i + result]) {
                   
            center = i;
            result++;
            k = max(k, i + result - 1);
        }
        
        if (result - 1  != pals[i]) 
            return false;
    }
    
    return true;
}

void try_ans(const vector<int> &seq, 
             const vector<int> &sugg, 
             vector<bool> &ans, int pos = 0) {
                 
    if (pos == ans.size()) {
        if (verify(seq, ans)) 
            answers.push_back(ans);
            
        return;
    }
    
    int sugg_loc = -1;
    if (sugg[pos] != -1) {
        if (sugg[pos] < pos)
            sugg_loc = ans[sugg[pos]];
        else 
            sugg_loc = 1 - ans[pos - 2];
    }
    
    for (int i = 0; i <= 1; i++) {
        if (sugg_loc >= 0 && sugg_loc != i) 
            continue;
        
        ans[pos] = i;
        try_ans(seq, sugg, ans, pos + 1);
    }
}

void solve() {
    answers.clear();
    
    int n; cin >> n;
    vector<int> seq(n);
    for (int &i : seq) cin >> i;

    vector<bool> ans(n, 0);
    vector<int> direction(n, -1);
    
    int j = 0;
    
    for (int i = 0; i < n; i++) {
        if (i + seq[i] >= n || i - seq[i] < 0) {
            cout << 0 << endl;
            return;
        }
        if (j == i) {
            if (i > 1)
                direction[i] = i + 2;
            j++;
        }
        while(j <= i + seq[i]) {
            direction[j] = i - (j - i);
            j++;
        }
    }
    
    try_ans(seq, direction, ans);
    
    cout << answers.size() << endl;
    for (const auto &v : answers) {
        for (int i : v) cout << i;
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
