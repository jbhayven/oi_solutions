#include <bits/stdc++.h>
using namespace std;

const int MAX_LEN = 250;

int ans[MAX_LEN];
int start = MAX_LEN / 2;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    cin >> n;
    
    while (n--) {
        string num; cin >> num;
        
        int s = 0;
        int sgn = 1;
        
        if (num[0] == '-') sgn = -1;
        if (num[0] == '-' || num[0] == '+') s = 1;
        
        int i = s;
        while(i < num.size() && num[i] != ',') i++;
        
        for (int j = 1; i - j >= s; j++) {
            ans[start - j] += sgn * (num[i - j] - '0');
        }
        
        i++;
        for (int j = 0; i + j < num.size(); j++) {
            ans[start + j] += sgn * (num[i + j] - '0');
        }
    }
    
    for (int i = MAX_LEN - 1; i > 0; i--) {
        ans[i-1] += ans[i] / 10;
        ans[i] -= 10 * (ans[i] / 10);
        
        if (ans[i] < 0) {
            ans[i-1]--;
            ans[i] += 10;
        }
    }
    
    if (ans[0] == -1) {
        cout << "-";
        for (int i = 0; i < MAX_LEN - 1; i++)
            if (ans[i] < 0) {
                ans[i] = -ans[i];
                ans[i] -= 1;
                ans[i+1] -= 10;
            }
        ans[MAX_LEN - 1] = 10;
        for (int k = MAX_LEN - 1; ans[k] == 10; k--) {
            ans[k] = 0;
            ans[k-1]++;
        }
    }
    
    int j = 0;
    while (j < start - 1 && ans[j] == 0) j++;
    
    while (j < start) {
        cout << ans[j++];
    }
    
    int k = MAX_LEN - 1;
    while (k >= start && ans[k] == 0) k--;
    
    if (k >= start) {
        cout << ",";
        while (j <= k) cout << ans[j++];
    }
    
    cout << endl;
    return 0;
}
