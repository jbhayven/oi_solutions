#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 310;

int n = 0;
int64_t bonus[MAX_N];

vector<int64_t> seq;

bool add(int i) {
    if (i > n) return true;
    
    seq.push_back(-1e12);
    
    int64_t sign = bonus[i] >= 0 ? 1 : -1;
    int64_t to_push = sign * bonus[i];
    int64_t big_sum = 0;
    int seq_len = i;
    
    for (int j = 1; j <= i; j++) {
        int64_t curr;
        
        if (to_push == 0) curr = 0;
        else if (sign > 0) curr = (to_push - 1) / seq_len + 1;
        else curr = to_push / seq_len;
        
        seq.push_back(sign * curr);
        
        big_sum += seq.back();
        if (big_sum > bonus[j])
            return false;
        
        to_push -= curr;
        seq_len--;
    }
    
    return add(i + 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> bonus[i];
        
    if (add(1)) {
        cout << "TAK" << endl;
        cout << seq.size() << endl;
        for (int64_t i : seq) cout << i << " ";
        cout << endl;
    } else {
        cout << "NIE" << endl;
    }
    
    return 0;
}
