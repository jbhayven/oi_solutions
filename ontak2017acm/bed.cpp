#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    int sum = 18;
    
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        sum += a;
    }
    
    cout << sum / (n + 1) << endl;
    
    return 0;
}
