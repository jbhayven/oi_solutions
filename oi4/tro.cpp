#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1010

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    
    vector<int> redge(n, 0);

    int a, b;
    while(m--) {
        cin >> a >> b;
        redge[--a]++;
        redge[--b]++;
    }
    
    int bad = 0;
    for(int reds : redge) 
        bad += reds * (n - reds - 1);
    bad /= 2;
        
    const int all = n * (n-1) * (n-2) / 6;
        
    cout << all - bad << endl;
    
    return 0;
}
