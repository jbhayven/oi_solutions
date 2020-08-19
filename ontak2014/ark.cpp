#include <bits/stdc++.h>
using namespace std;

#define MOD (1000 * 1000 * 1000 + 33)

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    
    vector<int> cols(n + 2, -1);
    for (int i = 1; i <= n; i++)
        cin >> cols[i];
    
    vector<vector<int>> results(n + 2, vector<int>(305, 0));
    results[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int lev = k; lev >= 0; lev--) { // avoid interference
            int j = i-1;
            while (!(cols[j] < cols[i])) j--;
        
            int sum = 0;
            while (j + 1 < i) {
                sum += results[j][lev];
                sum %= MOD;
                
                j++;
                
                results[j][lev + 1] += sum;
                results[j][lev + 1] %= MOD;
            }
            
            results[i][lev + 1] += sum; // do not include results[i-1][lev]
            results[i][lev + 1] %= MOD;
            
            sum += results[j][lev];
            sum %= MOD;
            
            j++;
            
            while (!(cols[j+1] < cols[i])) {
                sum += results[j][lev];
                sum %= MOD;
                
                j++;
                
                results[j][lev + 1] += sum;
                results[j][lev + 1] %= MOD;
            }
            
            results[i][lev] += results[i-1][lev]; // this is special
            results[i][lev] %= MOD;
        }
    }
    
    int result = 0;
    
    for (int i = 0; i <= k; i++) {
        result += results[n][i];
        result %= MOD;
    }
    
    cout << result << endl;
    
    return 0;
}
