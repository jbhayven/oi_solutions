#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    unordered_map<char, int> occ;
    string load;
    
    while (cin >> load) {
        for (char c : load)
            occ[c]++;
    }
    
    for (char c = 'a'; c <= 'z'; c++)
        if (occ[c]) cout << c << " " << occ[c] << endl;
    
    for (char c = 'A'; c <= 'Z'; c++)
        if (occ[c]) cout << c << " " << occ[c] << endl;
    
    return 0;
}
