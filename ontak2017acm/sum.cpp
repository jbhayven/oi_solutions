#include <bits/stdc++.h>
using namespace std;

int get_cnt(int sum, int top) {
    int all[20][100];
    int spec[20][100];
    
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 100; j++)
            all[i][j] = spec[i][j] = 0;
    all[0][0] = spec[0][0] = 1;

    int dig = 0;
    while (top) {
        dig++;
        for (int i = 0; i < 90; i++)
            for (int j = 0; j <= 9; j++) {
                all[dig][i + j] += all[dig - 1][i];
                spec[dig][i + j] += (j < top % 10) ? all[dig - 1][i] 
                                    : (j == top % 10) ? spec[dig - 1][i] 
                                    : 0;
            }
        top /= 10;
    }
    
    return spec[dig][sum];
}

int dig_sum(int n) {
    int result = 0;
    while (n) {
        result += n % 10;
        n /= 10;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    cin >> n;
    
    int result = 0;
    
    int pos = 0;
    for (int sum = 1; sum <= 9 * 9; sum++) {
        int l = sum, r = n;
        while (l < r) {
            int s = (l + r) / 2;
            int cnt = get_cnt(sum, s);
            
            if (pos + cnt < s || (pos + cnt == s && dig_sum(pos + cnt) == sum))
                r = s;
            else
                l = s + 1;
        }
        
        if (l == r && dig_sum(l) == sum && pos + get_cnt(sum, l) == l) 
            result++;
        
        pos += get_cnt(sum, n);
    }
    
    cout << result << endl;
    
    return 0;
}
