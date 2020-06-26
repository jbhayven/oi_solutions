#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1010;
const int MAX_Q = 1010100;
    
bool is_free[MAX_N][MAX_N];
int furthest[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    
    for(int i = 0; i < n; i++) {
        string row; cin >> row;
        for(int j = 0; j < m; j++)
            if(row[j] == '.') is_free[i+1][j+1] = true;
    }
    
    vector<int> x1(q), x2(q), y1(q), y2(q);
    vector<bool> ans(q, true);
    
    for(int i = 0; i < q; i++)
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    
    // Select queries:
    vector<list<int>> for_given_x(n+1);
    vector<list<int>> for_given_y(m+1);
    for(int i = 0; i < q; i++) {
        for_given_x[x1[i]].push_back(i);
        for_given_y[y2[i]].push_back(i);
    }
    
    // Find the furthest tile to the right the i-th row 
    // can be reached going upwards.
    for(int i = 0; i <= n + 1; i++)
        for(int j = 0; j <= m + 1; j++)
            if (is_free[i][j])
                furthest[i][j] = j;
            else 
                furthest[i][j] = 0;
    
    for(int i = n; i >= 0; i--) {
        for(int k = i+1; k <= n; k++)
            for(int j = 1; j <= m; j++) 
                if (is_free[k][j])
                    furthest[k][j] = max(furthest[k-1][j], furthest[k][j-1]);
                else furthest[k][j] = 0;
    
        // Update answers
        for(int q_no : for_given_x[i]) 
            ans[q_no] = ans[q_no] && (furthest[x2[q_no]][y2[q_no]] >= y1[q_no]);
    }
    // Done
    
    // Find the highest tile the j-th column can be reached going right.
    for(int i = 0; i <= n + 1; i++)
        for(int j = 0; j <= m + 1; j++)
            if (is_free[i][j])
                furthest[i][j] = i;
            else 
                furthest[i][j] = INT_MAX;
    
    for(int j = 1; j <= m; j++) {
        for(int col = j - 1; col > 0; col--)
            for(int i = n; i > 0; i--) 
                if (is_free[i][col])
                    furthest[i][col] = min(furthest[i+1][col], furthest[i][col+1]);
                else 
                    furthest[i][col] = INT_MAX;
    
        // Update answers
        for(int q_no : for_given_y[j]) 
            ans[q_no] = ans[q_no] && (furthest[x1[q_no]][y1[q_no]] <= x2[q_no]);
    }
    // Done
    
    for (bool val : ans)
        if(val) cout << "YES\n";
        else cout << "NO\n";
    
    return 0;
}
