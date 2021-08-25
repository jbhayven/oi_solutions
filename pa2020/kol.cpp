#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 10;

int n, m;
int col[3][MAX_N];
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        
        --k;
        
        col[k][l]++;
        col[k][r + 1]--;
    }
    
    int green = 0;
    int col_curr[3] = {0, 0, 0};
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++)
            col_curr[j] += col[j][i];
        
        if (col_curr[0] && col_curr[1] && !col_curr[2])
            green++;
    }
    
    cout << green << endl;
    
    return 0;
}
