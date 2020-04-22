#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector< pair<double, int> > acts(n);
    for(int i = 0; i < n; i++) {
        double a, b; 
        cin >> a >> b;
        
        acts[i] = make_pair(b / a, i + 1);
    }
    
    sort(acts.begin(), acts.end());
    for(auto pair : acts) 
        cout << pair.second << endl;

    return 0;
}
