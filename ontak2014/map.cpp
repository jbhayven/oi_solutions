#include <bits/stdc++.h>
using namespace std;

const int MAX_N  = 1010;
const int MOD = 1e9+33;
const int POW = 3;

int n, m;

char dents[2*MAX_N][2*MAX_N];
int max_good[2*MAX_N][2*MAX_N];
long long hashtab[4][2*MAX_N][2*MAX_N];
long long hash_pow[4*MAX_N*MAX_N];

void get_hash_pows() {
    hash_pow[0] = 1;
    for (int i = 1; i < 2 * (n + m); i++) {
        hash_pow[i] = hash_pow[i-1];
        hash_pow[i] *= POW;
        hash_pow[i] %= MOD;
    }
}

#define upd(col, num, i, j, sym1, sym2)                                        \
    col *= POW;                                                                \
    if (dents[i][j] == sym1) col += 2;                                         \
    else if (dents[i][j] == sym2) col += 1;                                    \
    col %= MOD;                                                                \
    hashtab[num][i][j] = col;                                                  \

void get_hashes() {
    get_hash_pows();
    
    for (int j = 0; j <= 2 * m; j++) {
        unsigned int col = 0; 
        for (int i = 0; i <= 2*n; i++) {
            upd(col, 0, i, j, '^', 'v');
        }
    }
    
    for (int j = 0; j <= 2 * m; j++) {
        unsigned int col = 0; 
        for (int i = 0; i <= 2*n; i++) {
            upd(col, 1, i, j, 'v', '^');
        }
    }

    for (int i = 0; i <= 2*n; i++) {
        unsigned int col = 0; 
        for (int j = 0; j <= 2 * m; j++) {
            upd(col, 2, i, j, '^', 'v');
        }
    }
    
    for (int i = 0; i <= 2*n; i++) {
        unsigned int col = 0; 
        for (int j = 0; j <= 2 * m; j++) {
            upd(col, 3, i, j, 'v', '^');
        }
    }
}

long long get_hash(int from, int cat, int min_pos, int max_pos) {
    long long result = -1;
    if (from < 2) {
        result = hashtab[from][max_pos][cat];
        if (min_pos > 0) 
            result -= (hashtab[from][min_pos - 1][cat] * hash_pow[max_pos - min_pos + 1] % MOD);
    } else {
        result = hashtab[from][cat][max_pos];
        if (min_pos > 0)
            result -= (hashtab[from][cat][min_pos - 1] * hash_pow[max_pos - min_pos + 1] % MOD);
    }
    result += MOD;
    result %= MOD;
    assert(result >= 0);
    return result;
}

bool process_cols(vector<pair<char, int>> &ans, char symb,
                  int &min_val, int &max_val, map<int, int> &things) {
    bool is_okay = true;
    while (is_okay) {
        is_okay = false;
        for (auto entr : things) {
            if (entr.first - min_val < max_val - entr.first && 
                entr.first - entr.second < min_val) {
                for (int i = min_val; i <= entr.first; i++)
                    things.erase(i);
                ans.push_back({symb, entr.first + 1});
                min_val = entr.first + 1;
                is_okay = true;
                break;
            }
            if (entr.first - min_val >= max_val - entr.first &&
                entr.first + entr.second >= max_val) {
                for (int i = max_val; i >= entr.first; i--)
                    things.erase(i);
                ans.push_back({symb, entr.first + 1});
                max_val = entr.first;
                is_okay = true;
                break;
            }
        }
    }
    
    return things.empty();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string row; cin >> row;
        for (int j = 0; j < m-1; j++)
            dents[2*i][2*j+1] = row[j];
    }
    for (int i = 0; i < n-1; i++) {
        string row; cin >> row;
        for (int j = 0; j < m; j++)
            dents[2*i+1][2*j] = row[j];
    }
    
    get_hashes();
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m-1; j++) {
            max_good[2*i][2*j+1] = 1;
            if (i > 0 && dents[2*(i-1)][2*j+1] == dents[2*i][2*j+1])
                max_good[2*i][2*j+1] += max_good[2*(i-1)][2*j+1];
        }
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < m; j++) {
            max_good[2*i+1][2*j] = 1;
            if (j > 0 && dents[2*i+1][2*(j-1)] == dents[2*i+1][2*j])
                max_good[2*i+1][2*j] += max_good[2*i+1][2*(j-1)];
        }
    }
    
    int x_min = 0;
    int x_max = m-1;
    int y_min = 0;
    int y_max = n-1;
    
    vector<pair<char, int>> ans;
    
    while (x_min < x_max || y_min < y_max) {
        vector<int> cols;
        for (int i = x_min; i < x_max; i++) {
            if (max_good[2*y_max][2*i+1] >= (y_max - y_min + 1))
                cols.push_back(i);
        }
        if (cols.size() > 0) {
            map<int, int> max_width;
            for (int i : cols) {
                int wid = 1;
                while (2*i+1 - wid >= 2*x_min && 2*i+1 + wid <= 2*x_max && 
                       get_hash(0, 2*i+1 - wid, 2 * y_min, 2 * y_max) ==
                       get_hash(1, 2*i+1 + wid, 2 * y_min, 2 * y_max))
                    wid++;
                max_width[i] = wid / 2;
            }
            
            if (!process_cols(ans, '|', x_min, x_max, max_width)) {
                cout << "NIE" << endl;
                exit(0);
            } else continue;
        } else {
            vector<int> rows;
            for (int i = y_min; i < y_max; i++) {
                if (max_good[2*i+1][2*x_max] >= (x_max - x_min + 1))
                    rows.push_back(i);
            }
            if (rows.size() > 0) {
                map<int, int> max_width;
                for (int i : rows) {
                    int wid = 1;
                    while (2*i+1 - wid >= 2*y_min && 2*i+1 + wid <= 2*y_max && 
                       get_hash(2, 2*i+1 - wid, 2 * x_min, 2 * x_max) ==
                       get_hash(3, 2*i+1 + wid, 2 * x_min, 2 * x_max))
                        wid++;
                    max_width[i] = wid / 2;
                }
                    
                if (!process_cols(ans, '-', y_min, y_max, max_width)) {
                    cout << "NIE" << endl;
                    exit(0);
                } else continue;
            }
        }
        
        cout << "NIE" << endl;
        exit(0);
    }
    
    cout << "TAK" << endl;
    cout << ans.size() << endl;
    for (auto pair : ans) 
        cout << pair.first << " " << pair.second << endl;
    
    return 0;
}
