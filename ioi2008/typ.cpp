#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    
    vector<string> words(n);
    for(string &s : words)
        cin >> s;
        
    string longest = "";
    
    for(const string &s : words)
        if(s.size() > longest.size())
            longest = s;
        
    sort(words.begin(), words.end(), [&](const string &a, const string &b) {
        for(size_t i = 0; i < min(a.size(), b.size()); i++) {
            if(a[i] == b[i]) continue;
            if(a[i] == longest[i]) return false;
            if(b[i] == longest[i]) return true;
            return a[i] < b[i];
        }
        return a.size() < b.size();
    });
    
    vector<char> op;
    string last = "";
    
    for(string &s : words){
        size_t i = 0;
        while(i < min(last.size(), s.size()) && last[i] == s[i]) i++;
        
        while(last.size() > i){
            op.push_back('-');
            last.pop_back();
        }
        
        while(last.size() < s.size()) {
            op.push_back(s[i]);
            last.push_back(s[i]);
            i++;
        }
        
        op.push_back('P');
    }
    
    cout << op.size() << endl;
    for(char c : op)
        cout << c << endl;
    
    return 0;
}
