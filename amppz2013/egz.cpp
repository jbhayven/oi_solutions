#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k;
    cin >> n >> k;
    
    if (k > n / 2) {
        cout << "NIE" << endl;
    } else {
        int start = n / 2;
        int end = 0;
        
        if (n % 2) {
            cout << 1 << " " << n / 2 + 1 << " " << n << " ";
            end = 1;
        }
        
        while (start > end) {
            cout << start << " " << start + (n / 2) << " ";
            start--;
        }
        
        cout << endl;
    }
    
    
    return 0;
}
