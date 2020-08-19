#include <bits/stdc++.h>
using namespace std;

void fix(array<int, 3> &a, array<int, 3> b) {
    int tab[6];
    for (int i = 0; i < 3; i++)
        tab[i] = a[i];
    for (int  i = 0; i < 3; i++)
        tab[3 + i] = b[i];
    sort(tab, tab + 6);
    for (int i = 0; i < 3; i++)
        a[i] = tab[5 - i];
}

int k;
void add(vector<array<int, 3>> &v, int a, int b, int val, int i = 1, int p = 1, int q = k) {
    if (a <= p && q <= b) {
        if (val < v[i][2]) return;
        v[i][2] = val;
        for (int j = 2; j > 0; j--) {
            if (v[i][j] > v[i][j-1])
                swap(v[i][j], v[i][j-1]);
        }
        return;
    }
    
    int s = (p + q) / 2;
    if (a <= s) {
        add(v, a, b, val, 2*i, p, s);
    }
    if (b > s) {
        add(v, a, b, val, 2*i+1, s+1, q);
    }
}

array<int, 3> get(vector<array<int, 3>> &v, int pos, int i = 1, int p = 1, int q = k) {
    if (p == q) return v[i];
    
    auto result = v[i];
    int s = (p + q) / 2;
    
    if (pos <= s) fix(result, get(v, pos, 2*i, p, s));
    else fix(result, get(v, pos, 2*i+1, s+1, q));
    
    return result;
}

void solve() {
    int n; cin >> n;
    k = 1; while (k < n) k <<= 1;
    vector< array<int, 3> > max_score(2 * k, {0, 0, 0});

    vector< pair<int, int> > fro(n);
    for (auto &f : fro)
        cin >> f.first >> f.second;
    
    for (int i = 1; i <= n; i++) 
        add(max_score, i - fro[i-1].first, i + fro[i-1].first, fro[i-1].second);
    
    int final_result = 0;
    for (int i = 1; i <= n; i++) {
        auto result = get(max_score, i);
        int temp = 0;
        for (int j = 0; j < 3; j++) {
            temp  += result[j];
        }
        final_result = max(final_result, temp);
    }
    
    cout << final_result << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int z; cin >> z; while(z--) {
        solve();
    }
    
    return 0;
}
