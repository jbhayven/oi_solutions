#include <bits/stdc++.h>
using namespace std;

int sums[8000][3];
int sum_pts[8000][3];
    
int x_pows[5010][3];
int y_pows[5010][3];
int x_antipows[5010][3];
int y_antipows[5010][3];

const array<int, 3> primes = {(int) 1e9 + 7, (int) 1e9 + 9, (int) 1e9 + 33};

int quick_pow(long long a, int pow, int MOD) {
    long long result = 1;
    
    while (pow > 0) {
        if (pow & 1) {
            result *= a;
            result %= MOD;
        }
        a *= a;
        a %= MOD;
        pow >>= 1;
    }
    
    return result;
}
    
void get_pows() {
    for (int i = 0; i < 3; i++) {
        int MOD = primes[i];
        
        int x_pow = 2;
        int x_anti = quick_pow(x_pow, MOD - 2, MOD);
        int y_pow = 3;
        int y_anti = quick_pow(y_pow, MOD - 2, MOD);
        
        x_pows[0][i] = 1;
        x_antipows[0][i] = 1;
        y_pows[0][i] = 1;
        y_antipows[0][i] = 1;
        
        for (int j = 1; j <= 5000; j++) {
            x_pows[j][i] = (long long) x_pows[j-1][i] * x_pow % MOD;
            x_antipows[j][i] = (long long) x_antipows[j-1][i] * x_anti % MOD;
            y_pows[j][i] = (long long) y_pows[j-1][i] * y_pow % MOD;
            y_antipows[j][i] = (long long) y_antipows[j-1][i] * y_anti % MOD;
        }
    }
}
    
array<int, 3> get_hash(int x, int y) {
    array<int, 3> result;
    
    for (int i = 0; i < 3; i++) {
        long long temp = x > 0 ? x_pows[x][i] : x_antipows[-x][i];
        temp *= y > 0 ? y_pows[y][i] : y_antipows[-y][i];
        temp %= primes[i];
        result[i] = temp;
    }
    
    return result;
}
    
int main() {
    get_pows();
    
    for (int i = -5000; i <= 5000; i++)
        for (int j = -5000; j <= 5000; j++) {   
            auto res = get_hash(i, j);
            int pos = lroundl(ceil(sqrt(i * i + j * j)));
            for (int k = 0; k < 3; k++) {
                sums[pos][k] += res[k];
                sums[pos][k] %= primes[k];
            }
        }
        
    for (int j = 0; j < 3; j++)
        sum_pts[0][j] = 1;
    for (int i = 1; i <= 5000; i++)
        for (int j = 0; j < 3; j++)
        sum_pts[i][j] = (sums[i][j] + sum_pts[i-1][j]) % primes[j];
        
    unordered_map<int, pair<int, int>> wins[5010];
    for (int r = 1; r <= 5000; r++)
        for (int l = 0; l < r; l++) {
            array<int, 3> res;
            for (int k = 0; k < 3; k++)
                res[k] = (sum_pts[r][k] - sum_pts[l][k] + primes[k]) % primes[k];
            wins[r][res[0]] = {res[1], res[2]};
        }
    
    int min_x = 5010;
    int max_x = -5010;
    int min_y = 5010;
    int max_y = -5010;
    array<int, 3> sum = {0, 0, 0};
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        min_x = min(min_x, x);
        max_x = max(max_x, x);
        min_y = min(min_y, y);
        max_y = max(max_y, y);
        
        auto to_sum = get_hash(x, y);
        for (int k = 0; k < 3; k++) 
            sum[k] = (sum[k] + to_sum[k]) % primes[k];
        
        if (i % 4 != 0 ||
            (max_x - min_x) % 2 != 0 ||
            (max_y - min_y) % 2 != 0 ||
            max_x - min_x != max_y - min_y) {
                printf("NIE\n");
                continue;
        }
        
        int mid_x = (max_x + min_x) / 2;
        int mid_y = (max_y + min_y) / 2;
        int r = (max_x - min_x) / 2;
        
        auto pt_move_hash = get_hash(-mid_x, -mid_y);
        array<int, 3> temp;
        for (int k = 0; k < 3; k++)
            temp[k] = (long long) pt_move_hash[k] * sum[k] % primes[k];
        
        if (wins[r].count(temp[0]) > 0 && 
            wins[r].at(temp[0]) == make_pair(temp[1], temp[2]))
            printf("TAK\n");
        else 
            printf("NIE\n");
    }
    
    return 0;
}
