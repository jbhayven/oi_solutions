#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 100;

int need[MAX_N], a[MAX_N];
int c[MAX_N], l[MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m; 
    cin >> n >> m;
    
    for (int i = 0; i < m; i++)
        cin >> l[i];
    for (int i = 0; i < m; i++)
        cin >> c[i];
        
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    
    long long sum = 0;
    int wrong = m;
    int ans = 0;
    for (int i = 0; i < m; i++) {
        need[c[i]] = l[i];
        sum += l[i];
    }
    
    if (sum > n) {
        cout << 0 << endl;
        exit(0);
    }
                                              

    for (int i = 1; i <= n; i++) {
        if (i > sum) {
            if (need[a[i - sum]] == 0) wrong++;                                                
            need[a[i-sum]]++;                                                                 
            if (need[a[i-sum]] == 0) wrong--; 
        }
        
        {
            if (need[a[i]] == 0) wrong++;                                                
            need[a[i]]--;                                                                 
            if (need[a[i]] == 0) wrong--; 
        }
    
        if (!wrong)
            ans++;
    }
#undef UPD
    
    cout << ans << endl;    
    return 0;
}
