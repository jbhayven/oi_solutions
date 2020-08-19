#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1001000;
const int MIN_VAL = 1;
const int MAX_VAL = 1000000;

int app[MAX_VAL + 5];
int num_sum[MAX_N][2];
long long result[MAX_N + 15];
long long nums[MAX_N];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++) {
        int num = 0; 
        char c; while (c < '0' || '9' < c) c = getc_unlocked(stdin);
        while ('0' <= c && c <= '9') {
            num *= 10;
            num += (c - '0');
            c = getc_unlocked(stdin);
        }
        app[num]++;
    }
    
    int j = 1;
    for (int i = MIN_VAL; i <= MAX_VAL; i++) {
        while (app[i] > 0) {
            nums[j++] = i;
            app[i]--;
        }
    }
    for (int i = 1; i < 15; i++)
        nums[n + i] = nums[n];
    
    if (n <= k) {
        cout << nums[n] << endl;
        exit(0);
    }
    
    if (k == 2) {
        for (int i = 0; i <= n; i++)
            result[i] = LONG_LONG_MAX / 2;
            
        for (int i = n+2; i >= 1; i--) {
            num_sum[i][0] = nums[i];
            num_sum[i][1] = nums[i] + nums[i + k];
        }
        
        int tot_sum[4] = {0};
        for (int i = 1; i <= k; i++)
            tot_sum[i] = tot_sum[i-1] + nums[i];
            
        for (int i = n; i >= 1; i--) {
            result[i] = min(result[i], result[i + 2] + num_sum[i + 1][0] + tot_sum[2] + nums[2]);
            result[i] = min(result[i], result[i + 1] + num_sum[i][0] + tot_sum[1]);
        }
        for (int i = 1; i <= k; i++)
            result[1] = min(result[1], result[i + 1] + nums[i]);
        
        cout << result[1] << endl;
    } else {
        vector<long long> by_2(n+15, 0);
        for (int i = 1; i <= n; i++) {
            by_2[i] = nums[i];
            if (i > 1) by_2[i] += by_2[i-2];
        }
        
        vector<long long> by_3(n+15, 0);
        for (int i = 1; i <= n; i++) {
            by_3[i] = nums[i];
            if (i > 2) by_3[i] += by_3[i-3];
        }
        
        int brk = n;
        while (brk >= 6 && min(
                nums[3] + nums[1] + 
                nums[brk] + nums[2] + 
                nums[brk - 3] + nums[3], 
                nums[2] + nums[1] + nums[brk] + nums[2] +
                nums[2] + nums[1] + nums[brk - 3] + nums[2])
                < 3 * nums[1] + nums[brk] + nums[brk - 2] + nums[brk - 4]) 
                    brk -= 3;
        
        long long final_result = LONG_LONG_MAX / 2;
        long long curr = 0;
        
        int a = 3;
        int b = n;
        
        while (a <= b) {
            long long temp = curr;
            if (a + 5 > brk) {
                int len_6 = (b - a + 1) / 6;
                temp += by_3[b] - by_3[b - len_6 * 6];
                temp += len_6 * min(2 * nums[3] + nums[2] + nums[1], 2 * (2 * nums[2] + nums[1]));
                
                if ((b - a + 1) % 6 == 0) temp += nums[2];
                else if ((b - a + 1) % 6 == 1) temp += nums[a];
                else if ((b - a + 1) % 6 == 2) temp += nums[a + 1] + nums[1] + nums[2];
                else if ((b - a + 1) % 6 == 3) temp += 
                    min(nums[a + 2] + nums[1] + nums[a],
                        nums[2] + nums[1] + nums[a + 2] + nums[2] + nums[2]);
                else if ((b - a + 1) % 6 == 4) temp += 
                    min(nums[a + 3] + nums[1] + nums[a + 1] + nums[1] + nums[2], 
                        nums[a] + nums[1] + nums[a + 3] + nums[2] + nums[2]);
                else temp += 
                    min(nums[2] + nums[1] + nums[a + 4] + nums[2] + nums[a + 1] + nums[1] + nums[2],
                min(nums[a + 4] + nums[1] + nums[a + 2] + nums[1] + nums[a],
                    nums[a] + nums[1] + nums[a + 4] + nums[2] + nums[a + 1]));
            } else {
                int len_6 = max((b - brk + 3) / 6, 0);
                temp += by_3[b] - by_3[b - len_6 * 6];
                temp += len_6 * min(2 * nums[3] + nums[2] + nums[1], 2 * (2 * nums[2] + nums[1]));
                
                temp += by_2[b - 6 * len_6];
                temp += ((b - 6 * len_6 - a + 1) / 2) * nums[1];
                if (b % 2 == a % 2) {
                    temp -= by_2[a - 2];
                } else {
                    temp -= by_2[a-1];
                    temp += nums[2];
                }
            }
            
            final_result = min(final_result, temp);
            
            curr += nums[a];
            curr += nums[b];
            curr += nums[1] + nums[2];
            a++;
            b -= 3;
        }
        cout << final_result << endl;
    }
    return 0;
}
