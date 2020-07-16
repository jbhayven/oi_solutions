#include <bits/stdc++.h>
using namespace std;

#define CAN_ADD     1
#define CAN_SUB     2
#define CAN_MULT    4
#define LEFT_BRACK  8
#define RIGHT_BRACK 16

#define MAX_N 55
#define MAX_M 125

const int MOD = 1e9 + 7;

vector<int> update_numbers(const vector<int> numbers[],
                           int len, const vector<int> &digits, int m) {
    vector<int> new_numbers(m, 0);
    
    for (int d : digits) {
        for (int i = 0; i < m; i++) {
            int new_val = (10 * i + d) % m;
            new_numbers[new_val] += numbers[len - 1][i];
            new_numbers[new_val] %= MOD;
        }
    }
        
    /* We won't populate the number vector with extensions of 0 */
    if (len == 2 && find(digits.begin(), digits.end(), 0) != digits.end())
        for (int d : digits) new_numbers[d % m]--;
        
    return new_numbers;
}

vector<int> update_bracks(const vector<int> exprs[], int len, int flags, int m) {
    if (len > 2 && (flags & LEFT_BRACK) && (flags & RIGHT_BRACK))
        return vector<int>(exprs[len - 2]);
    
    return vector<int>(m, 0); 
}

vector<int> update_mults(const vector<int> bracks[], 
                         const vector<int> mults[], 
                         const vector<int> numbers[], 
                         int len, int flags, int m) {
    vector<int> result(m, 0);
    
    if (len <= 2 || (flags & CAN_MULT) == false) 
        return result; // only numbers can be less-than-three-character expressions

    for (int i = 1; i < len - 1; i++) {
        int j = len - i - 1; 
        /* Lengths: i and j */
        
        /* For each pair expr_1 @ expr_2 of total length = len... */
        for (int k = 0; k < m; k++) {
            for (int l = 0; l < m; l++) {
                long long left = (long long) numbers[i][k] + bracks[i][k] + mults[i][k];
                long long right = numbers[j][l] + bracks[j][l];
                int comb = (left * right) % MOD;
                
                result[(k * l) % m] += comb;
                result[(k * l) % m] %= MOD;
            }
        }
    }
    
    return result;
}

vector<int> get_next_result(int len, 
                            const vector<int> exprs[],
                            const vector<int> bracks[],
                            const vector<int> mults[],
                            const vector<int> numbers[], 
                            int flags, int m) {
    vector<int> new_result(m, 0);
    for (int i = 0; i < m; i++) {
        new_result[i] += numbers[len][i];
        new_result[i] += bracks[len][i];
        new_result[i] %= MOD;
        new_result[i] += mults[len][i];
        new_result[i] %= MOD;
    }
        
    for (int i = 1; i < len - 1; i++) {
        int j = len - i - 1; 
        /* Lengths: i and j */
        
        /* For each pair expr_1 @ expr_2 of total length = len... */
        for (int k = 0; k < m; k++) {
            for (int l = 0; l < m; l++) {
                long long left = exprs[i][k];
                long long right = (long long) numbers[j][l] + bracks[j][l] + mults[j][l];
                int comb = (left * right) % MOD;
                
                if (flags & CAN_ADD) {
                    new_result[(k + l) % m] += comb;
                    new_result[(k + l) % m] %= MOD;
                }
                if (flags & CAN_SUB) {
                    new_result[(k + m - l) % m] += comb;
                    new_result[(k + m - l) % m] %= MOD;
                }
            }
        }
    }
    
    return new_result;
}                       

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    vector<int> digits;
    int flags = 0;
    
    int n, m, k, l;
    cin >> n >> m >> k >> l;
    
    string allow;
    cin >> allow;
    
    for (char c : allow) {
        switch (c) {
        case '(':
            flags |= LEFT_BRACK;
            break;
        case ')':
            flags |= RIGHT_BRACK;
            break;
        case '+':
            flags |= CAN_ADD;
            break;
        case '-':
            flags |= CAN_SUB;
            break;
        case '*':
            flags |= CAN_MULT;
            break;
        default:
            digits.push_back(c - '0');
            break;
        }
    }
    
    /* Initialize the result structure */
    vector<int> numbers[MAX_N]; // number of integers with given remainder
    vector<int> mults[MAX_N];   // number of multiplications with given remainder
    vector<int> bracks[MAX_N];  // number of bracketed expressions with given remainder
    vector<int> exprs[MAX_N];   // result for given length and remainder   
    
    vector<int> init_nums(m, 0);
    for (int i : digits) init_nums[i % m]++;
    
    /* Initialize for len = 1 */
    numbers[1]  = init_nums;
    mults[1]    = vector<int>(m, 0);
    bracks[1]   = vector<int>(m, 0);
    exprs[1]    = init_nums;     
        
    for (int i = 2; i <= n; i++) {
        numbers[i] = update_numbers(numbers, i, digits, m);
            
        bracks[i] = update_bracks(exprs, i, flags, m);
        mults[i] = update_mults(bracks, mults, numbers, i, flags, m);
        
        exprs[i] = get_next_result(i, exprs, bracks, mults, numbers, flags, m);
    }
    
    cout << exprs[n][k] << endl;
    
    return 0;
}
