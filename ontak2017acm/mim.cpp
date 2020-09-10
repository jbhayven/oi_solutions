#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    cin >> n;
    
    int max = 0;
    int x = 0;
    
    for (int i = 0; i < n; i++) {
        int a; 
        cin >> a;
        max = std::max(max, a);
        x ^= a;
    }
    
    if (max <= 1) cout << "NIE" << endl;
    else if(x > 0) cout << "TAK" << endl;
    else cout << "NIE" << endl;
    
    return 0;
}
