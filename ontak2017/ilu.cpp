#include <bits/stdc++.h>
using namespace std;

class mod_int {
    static const int MOD = 1e9 + 7;
    
    int value;
    
public:
    mod_int() : value(0) {}
    mod_int(int a) : value((a % MOD + MOD) % MOD) {}
    
    mod_int operator*=(const mod_int &other) {
        long long result = value;
        result *= other.value;
        result %= MOD;
        value = result;
        return (*this);
    }
    
    const mod_int operator*(const mod_int &other) const {
        return mod_int(*this) *= other;
    }
    
    mod_int operator+=(const mod_int &other) {
        value += other.value;
        value %= MOD;
        return (*this);
    }
    
    const mod_int operator+(const mod_int &other) const {
        return mod_int(*this) += other;
    }
    
    mod_int operator-=(const mod_int &other) {
        value += (MOD - other.value);
        value %= MOD;
        return (*this);
    }
    
    const mod_int operator-(const mod_int &other) const {
        return mod_int(*this) -= other;
    }
    
    friend istream& operator>>(istream &in, mod_int &n) {
        in >> n.value;
        n.value %= MOD;
        return in;
    }
    
    int to_int() {
        return value;
    }
};

class Result {
    static const int CATS = 12;
    bool is_small;
    mod_int result[CATS][CATS];
    mod_int vals[4];
    
    void flip() {
        mod_int temp_result[CATS][CATS];
        
        for (int i = 0; i < CATS; i++) {
            int a = get_x(i);
            int b = get_y(i);
            for (int j = 0; j < CATS; j++) {
                int x = get_x(j);
                int y = get_y(j);
                temp_result[get_coord(y, x)][get_coord(b, a)] = result[i][j];
            }
        }
        
        for (int i = 0; i < CATS; i++) 
            for (int j = 0; j < CATS; j++)
                result[i][j] = temp_result[i][j];
    }
    
    inline int get_coord(int i, int j) {
        return 3*i + j - (i < j);
    }
    
    inline int get_x(int i) {
        return i / 3;
    }
    
    inline int get_y(int i) {
        return i % 3 + (i / 3 <= i % 3);
    }
public:
    Result () : is_small(true) {}
    
    Result operator*=(const Result& other) {
        mod_int temp_result[CATS][CATS];
        
        if (is_small) {
            if (other.is_small) {
                for (int x = 0; x < 4; x++) {
                    for (int y = 0; y < 4; y++) {
                        if (y == x) continue;
                        
                        int coord = get_coord(x, y);
                        temp_result[coord][coord] = vals[x] * other.vals[y]; 
                    }
                }
            } else {
                Result temp(other);
                temp.flip();
                temp *= *this;
                temp.flip();
                for (int i = 0; i < CATS; i++)
                    for (int j = 0; j < CATS; j++)
                        temp_result[i][j] = temp.result[i][j];
            }
        } else if (other.is_small) {
            for (int i = 0; i < CATS; i++) {
                for (int j = 0; j < CATS; j++) {
                    int x = get_x(j);
                    int y = get_y(j);
                    
                    for (int z = 0; z < 4; z++) {
                        if (z == x) continue;
                        if (z == y) continue;
                        temp_result[i][get_coord(y, z)] += result[i][j] * other.vals[z];
                    }
                }
            }
        } else {
            for (int i = 0; i < CATS; i++) {
                mod_int multifactors[CATS];
                
                /* This part can be done faster with a preprocessed compatibility array */
                for (int k = 0; k < CATS; k++) {
                    int x = get_x(k);
                    int y = get_y(k);
                    
                    for (int l = 0; l < CATS; l++) {
                        int a = get_x(l);
                        if (a == x || a == y) continue;
                        
                        int b = get_y(l);
                        if (b == y) continue; 
                        
                        multifactors[l] += result[i][k];
                    }
                }
                
                for (int j = 0; j < CATS; j++) {
                    for (int l = 0; l < CATS; l++) {
                        temp_result[i][j] += multifactors[l] * other.result[l][j];
                    }
                }
            }
        }
        
        for (int i = 0; i < CATS; i++)
            for (int j = 0; j < CATS; j++)
                result[i][j] = temp_result[i][j];
        
        is_small = false;
        return *this;
    }
    
    const Result operator*(const Result& other) const {
        return Result(*this) *= other;
    }
    
    int get_result() const {
        mod_int ret;
        if (is_small) {
            for(int i = 0; i < 4; i++)
                ret += vals[i];
        } else {
            for (int i = 0; i < CATS; i++)
                for (int j = 0; j < CATS; j++) 
                    ret += result[i][j];
        }
                
        return ret.to_int();
    }
    
    int turbo_mult(const Result &other) const {
        if (!is_small) return -1;
        if (!other.is_small) return -1;
        
        mod_int result = 0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result += vals[i] * other.vals[j];
        
        return result.to_int();
    }
    
    friend istream &operator>>(istream &is, Result &r) {
        for (int i = 0; i < 4; i++)
            is >> r.vals[i];
        r.is_small = true;
            
        return is;
    }
};

int k = 1; 
Result gather_result(int x, int y, const vector<Result> &hats, 
                     int i = 1, int p = 1, int q = k) 
{
    if (x <= p && q <= y) return Result(hats[i]);
    
    int s = (p + q) / 2;
    
    if (y <= s) return gather_result(x, y, hats, 2*i, p, s);
    if (s < x) return gather_result(x, y, hats, 2*i+1, s+1, q);
    
    return gather_result(x, y, hats, 2*i, p, s) 
            * gather_result(x, y, hats, 2*i+1, s+1, q);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, q; cin >> n >> q;
    
    while(k < n) k <<= 1;
    vector<Result> hats(2*k);
    
    for (int i = k; i < k + n; i++)
        cin >> hats[i];
    for (int i = k-1; i > 0; i--)
        hats[i] = hats[2*i] * hats[2*i + 1];
    
    for (int i = 0; i < q; i++) {
        int type; cin >> type;
        if (type == 1) {
            int x; cin >> x;
            x += k - 1;
            cin >> hats[x];
            x /= 2;
            while(x > 0) {
                hats[x] = hats[2*x] * hats[2*x + 1];
                x /= 2;
            }
        } else {
            int x, y; 
            cin >> x >> y;
            if (y == x + 1) { // corner-case
                cout << hats[k + x - 1].turbo_mult(hats[k + y - 1]) << endl;
            } else {
                cout << gather_result(x, y, hats).get_result() << endl;
            }
        }
    }
    
    return 0;
}
