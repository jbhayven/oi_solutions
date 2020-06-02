#include <bits/stdc++.h>
using namespace std;

const int SMOL_P = 131;
const int BIG_P = 1e9 + 7;

int n; 
vector<string> slowa;
vector< vector<int> > pref_hasz;
vector<int> pows;
    
inline int wez_hasz(const vector<int> &pref_hasz, int koniec, int poczatek) {
    int zbedne = (long long) pows[koniec - poczatek] * pref_hasz[poczatek] % BIG_P;
    return (pref_hasz[koniec] - zbedne + BIG_P) % BIG_P;
}

bool try_len(size_t len) {
    unordered_map<int, int> wyst;
    for(int s = 0; s < n; s++) {
        if (len > slowa[s].size()) return false;
        
        unordered_set<int> jakie_ma;
        
        for(size_t j = len; j <= slowa[s].size(); j++)
            jakie_ma.insert(wez_hasz(pref_hasz[s], j, j-len));
        
        for(int hasz: jakie_ma) {
            wyst[hasz]++;
            if (wyst[hasz] == n) 
                return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    
    slowa.resize(n);
    for(string &s : slowa)
        cin >> s;
    
    /* Generate prefix hashes */
    for(const string &s : slowa) {
        long long num = 0;
        vector<int> hasze(1, 0);
        for(char c : s) {
            num *= SMOL_P;
            num %= BIG_P;
            num += c;
            hasze.push_back(num);
        }
        pref_hasz.push_back(hasze);
    }
    
    /* Generate pows */
    long long pow = 1;
    for(int i = 0; i <= 2000; i++) {
        pows.push_back(pow);
        pow *= SMOL_P;
        pow %= BIG_P;
    }
    
    /* Binary search by result */
    int p = 0, q = 2000;
    while(p != q) {
        int len = (p + q + 1) / 2;
        
        if (try_len(len)) p = len;
        else q = len - 1;
    }
    
    cout << p << endl;
    return 0;
}
