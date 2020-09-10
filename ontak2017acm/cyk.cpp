#include <bits/stdc++.h>
using namespace std;

int _maxlen[500200];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    int *max_len = _maxlen + 250100;
    for (int j = -131000; j < 131000; j++)
        max_len[j] = -1e9;
    max_len[0] = 0;
    
    cin >> n;
    while (n--) {
        int len; cin >> len;
        string s; cin >> s;
        
        int delta = 0;
        for (char c : s)
            delta += c == '(' ? 1 : -1;
        
        if (delta > 0) {
            for (int j = 130000; j > -130000; j--)
                max_len[j] = max(max_len[j], max_len[j - delta] + len);
        } else {
            for (int j = -130000; j < 130000; j++)
                max_len[j] = max(max_len[j], max_len[j - delta] + len);
        }
    }
    
    cout << max_len[0] << endl;
    
    return 0;
}
