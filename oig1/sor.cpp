#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    vector<string> words;
    int n;
    
    cin >> n;
    words.resize(n);
    for (auto &s : words) cin >> s;
    
    sort(words.begin(), words.end(), [](const string &s1, const string &s2) {
        if (s1.size() < s2.size()) return true;
        if (s1.size() > s2.size()) return false;
        
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] == s2[i]) continue;
            return s1[i] < s2[i];
        }
        
        return false;
    });
    
    for (auto &s : words)
        cout << s << endl;
    
    return 0;
}
