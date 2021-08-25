#include <bits/stdc++.h>
using namespace std;

int to_val(std::string &s) {
    return s[0] * 1000 + s[1];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    std::map<int, int> cnt;
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        std::string s;
        cin >> s;
        
        cnt[to_val(s)]++;
    }
    
    if (cnt.size() < 5 * 3) {
        cout << "NIE" << endl;
        exit(0);
    }
    
    std::array<std::string, 3> special = {"5A", "5B", "5C"};
    for (auto &s : special) {
        if (cnt[to_val(s)] < 2) {
            cout << "NIE" << endl;
            exit(0);
        }
    }
    
    cout << "TAK" << endl;
    return 0;
}
