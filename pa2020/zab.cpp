#include <bits/stdc++.h>
using namespace std;

int cnt[2][26];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    for (int k : {-1, 1}) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            cnt[j % 2][s[j] - 'a'] += k;
        }
    }
    
    for (int k = 0; k <= 1; k++) {
        for (int i = 0; i < 26; i++) {
            if (cnt[k][i] != 0) {
                cout << "NIE" << endl;
                exit(0);
            }
        }
    }
    
    cout << "TAK" << endl;
    return 0;
}
