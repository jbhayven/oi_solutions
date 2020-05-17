#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n; 
    
    char prev = '-', curr;
    while(--n) {
        cin >> curr;
        if(curr == '+' && prev == '-') cout << '(';
        if(curr == '-' && prev == '+') cout << ')';
        cout << '-';
        prev = curr;
    }
    
    if(prev == '+') cout << ')';
    cout << endl;
    
    return 0;
}
