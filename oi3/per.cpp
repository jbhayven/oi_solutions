#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned n; cin >> n;
    
    vector<unsigned> perm(1, 0);
    while(perm.size() < n) {
        vector<unsigned> temp(perm);
        perm.clear();
        
        for(unsigned val : temp) 
            perm.push_back(2*val + 1);
        for(unsigned val : temp)
            perm.push_back(2*val);
    }
    
    for(unsigned entry : perm)
        if(entry <= n - 1)
            cout << entry << endl;
    return 0;
}
