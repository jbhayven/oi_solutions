#include <bits/stdc++.h>
using namespace std;

void read_and_solve() {
    int n; cin >> n;
    
    vector<int> nums(n);
    for(int &num : nums) cin >> num;
    
    int cand = -1;
    int cnt = 0;
    
    /* find a candidate for the dominant */
    for(int num : nums) {
        if(cnt == 0) cand = num;
        
        if(num == cand) 
            cnt++;
        else 
            cnt--;
    }
    
    cnt = 0;
    for(int num : nums)
        if(num == cand) cnt++;
    
    if(2 * cnt <= n) 
        cout << "TAK" << endl;
    else if(2 * cnt - 1 == n) {
        int flags = 0;
        for(int num : nums) {
            if(num < cand) flags |= 1;
            if(num > cand) flags |= 2;
        }
        if(flags < 3) 
            cout << "TAK" << endl;
        else 
            cout << "NIE" << endl;
    } 
    else cout << "NIE" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; 
    
    while(t--) read_and_solve();
    
    return 0;
}
