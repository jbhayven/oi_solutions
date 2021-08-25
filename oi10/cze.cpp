#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int m, n;
    cin >> m >> n;
    m--, n--;
    
    vector<int> v(m), h(n);
    
    for (int &i : v) cin >> i;
    for (int &i : h) cin >> i;
    
    sort(h.begin(), h.end());
    
    int result = accumulate(h.begin(), h.end(), 0);
    
    for (int i : v) {
        int temp = 0;
        int add = INT_MAX;
        
        for (int j = 0; j <= n; j++) {
            add = min(add, (n - j + 1) * i + temp);
            if (j < n) temp += h[j];
        }
        
        result += add;
    }
    
    cout << result << endl;
    return 0;
}
