#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 10;

int res_len;
int result[MAX_N];

void loop(int j) {
    while (j > 1) {        
        if (result[j] == 0) j--;
        else if (result[j-1] > 0) {
            result[j]--;
            result[j-1]--;
            result[j+1]++;
            
            res_len = max(res_len, j + 1 - 1);
            j += 2;
        } else if (result[j] == 2) {
            result[j] = 0;
            result[j+1]++;
            result[j-2]++;
            
            res_len = max(res_len, j + 1 - 1);
            j += 2;
        } else if (result[j] == 3 ) {
            result[j+2]++;
            result[j] = 0;
            result[j-2]++;
            
            res_len = max(res_len, j + 2 - 1);
            j += 3;
        } else j--;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    for (int i = 0; i < 2; i++) {
        int len; cin >> len;
        
        res_len = max(res_len, len);
        for (int j = 2; j < 2 + len; j++) {
            int val; cin >> val;
            result[j] += val;
        }
    }
    
    loop(2 + res_len);
    
    if (result[1]) {
        result[2] += result[1];
        result[1] = 0;
        
        loop(3);
    }
    
    cout << res_len << " ";
    for (int i = 2; i < 2 + res_len; i++) 
        cout << result[i] << " ";
    cout << endl;
}
