#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 10;

int from_start[MAX_N];
int sum_right[MAX_N];
int sum_left[MAX_N];
int a[MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    a[n+1] = 1;
    
    sum_right[n+1] = sum_left[0] = 0;
    
    for (int i = n; i >= 1; i--) 
        sum_right[i] = sum_right[i+1] + (1 - a[i]);
    for (int i = 1; i <= n; i++) 
        sum_left[i] = sum_left[i-1] + (a[i] - (-1));
    
    int result = 1e7;
    from_start[0] = 0;
    for (int i = 1; i <= n + 1; i++) {
        if (a[i] == 1) 
            result = min(result, sum_right[i] + from_start[i-1]);
        
        if (a[i] == -1) {
            if (a[1] != -1) {
                from_start[i] = 1e7;
            } else {
                from_start[i] = sum_left[i];
            }
        } else if (a[i] == 0) {
            from_start[i] = from_start[i-1];
        } else {
            if (a[1] != -1) {
                from_start[i] = 1e7;
            } else {
                from_start[i] = sum_left[i] - 1;
            }
        }
    }
    
    if (result >= 1e7) {
        cout << "BRAK" << endl;
    } else {
        cout << result << endl;
    }
    
    return 0;
}
