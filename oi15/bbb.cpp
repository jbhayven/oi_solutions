#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 100;

int seq[MAX_N];
int lowest[MAX_N];
int diff;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, p, q, x, y;
    cin >> n >> p >> q >> x >> y;
    
    string s; cin >> s;
    for (int i = 1; i <= n; i++) {
        seq[i] = (s[i - 1] == '+' ? 1 : -1);
    }
        
    lowest[0] = p;
    for (int i = 1; i <= n; i++)
        lowest[i] = lowest[i - 1] + seq[i];
    diff = q - lowest[n];
    for (int i = 1; i <= n; i++)
        lowest[i] = min(lowest[i], lowest[i - 1]);
    
    long long result = 1e17;
    int sum_right = 0;
    int lowest_right = 0;
    for (long long j = 0; j < n; j++) {
        long long moving = j * y; 
        long long needed_upgr = 
            (max(-min(sum_right + lowest[n - j], p + lowest_right), 0) + 1) / 2;
        
        long long switches = needed_upgr + abs(diff / 2 - needed_upgr);
        long long new_result = moving + switches * x;
        
        result = min(result, new_result);
        
        sum_right += seq[n - j];
        lowest_right = min(0, lowest_right + seq[n - j]);
    }
    
    cout << result << endl;
    
    return 0;
}
