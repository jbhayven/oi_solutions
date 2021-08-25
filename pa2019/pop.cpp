#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 210;
const int64_t NEG_INF = LONG_LONG_MIN / 10;

int64_t result_base[70][MAX_N][MAX_N];
int64_t result_edge[70][MAX_N][MAX_N];

int64_t a[MAX_N]; 
int64_t sum_of[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    long long m;
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++)
        cin >> a[i];
        
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = i; k <= j; k++)
                sum_of[i][j] += a[k];
        
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) {
            result_base[0][i][j] = i >= j ? 0 : NEG_INF;
            result_edge[0][i][j] = i > j || (i == j && m % 2 == 0) ? 0 : NEG_INF;
        }
        
    for (int p = 1; p < 61; p++)
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++) {
                result_base[p][i][j] = result_base[p-1][i][j];
                result_edge[p][i][j] = result_edge[p-1][i][j];
                
                for (int k = i; k <= j; k++) {
                    result_base[p][i][j] = 
                        max(result_base[p][i][j], 
                            result_base[p - 1][i][k-1] + p * a[k] + result_base[p - 1][k+1][j] + sum_of[k+1][j]);
                            
                    result_base[p][i][j] = 
                        max(result_base[p][i][j], 
                            result_base[p - 1][i][k] + result_base[p - 1][k+1][j] + sum_of[k+1][j]);

                    if (m % (2LL << p) >= (1LL << p) - 1 && m % (2LL << p) != (2LL << p) - 1) {
                        result_edge[p][i][j] =
                            max(result_edge[p][i][j],
                                result_base[p - 1][i][k-1] + p * a[k] + result_edge[p - 1][k+1][j] + sum_of[k+1][j]);
                                
                        result_edge[p][i][j] =
                            max(result_edge[p][i][j],
                                result_base[p - 1][i][k] + result_edge[p - 1][k+1][j] + sum_of[k+1][j]);
                    }
                }
            }
    
    cout << result_edge[60][1][n] << endl;

    return 0;
}
