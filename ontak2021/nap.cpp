#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 500100;

struct {
    int px, py, vx, vy;
} info[MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, r;
    cin >> n >> r;
    
    for (int i = 0; i <= n; i++)
        cin >> info[i];
    
    for (int i = 1; i <= n; i++) {
        info[i].px -= info[0].px;
        info[i].py -= info[0].py;
        info[i].vx -= info[0].vx;
        info[i].vy -= info[0].vy;
    }
    
    vector<long double, char> event;
    
    for (int i = 1; i <= n; i++) {
        long double pnt1 =
    } 
    
    return 0;
}
