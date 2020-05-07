#include <bits/stdc++.h>
using namespace std;

class int128_t {
private:
    const int64_t MAX_RANGE = (1LL << 50);
    pair<int64_t, int64_t> liczba;
    
    void normalize() {
        if(liczba.second >= MAX_RANGE) {
            liczba.first += liczba.second / MAX_RANGE;
            liczba.second %= MAX_RANGE;
        }
        if(liczba.second < 0) {
            liczba.first--;
            liczba.second += MAX_RANGE;
        }
    }

public:    
    int128_t() : liczba({0, 0}) { }
    int128_t(int pow) {
        if(pow < 50) liczba = {0, (1LL << pow)};
        else liczba = {(1LL << (pow - 50)), 0};
    }
    
    int128_t operator+=(const int128_t &other) {
        liczba.first += other.liczba.first;
        liczba.second += other.liczba.second;
        normalize();
        
        return *this;
    }
    
    int128_t operator-=(const int128_t &other) {
        liczba.first -= other.liczba.first;
        liczba.second -= other.liczba.second;
        normalize();
        
        return *this;
    }
    
    bool operator==(const int128_t &other) {
        return (liczba.first  == other.liczba.first && 
                liczba.second == other.liczba.second);
    }
    
    bool operator<=(const int128_t &other) {
        return (liczba.first  < other.liczba.first ||
                (liczba.first == other.liczba.first &&
                liczba.second <= other.liczba.second));
    }
    
    void invert() {
        liczba.first = -liczba.first;
        liczba.second = -liczba.second;
        normalize();
    }
    
    friend istream& operator>>(istream &is, int128_t &num) {
        string num_str;
        is >> num_str;
        
        for(int digit : num_str) {
            num.liczba.first *= 10;
            num.liczba.second *= 10;
            num.liczba.second += digit - '0';
            num.normalize();
        }
        
        return is;
    }
    
    friend ostream& operator<<(ostream &os, int128_t num) {
        os << num.liczba.first << " " << num.liczba.second;
        return os;
    }
};

vector< pair<int128_t, int128_t> > ranges;
    
void obtain(int128_t loan) {
    int i = 100;
    while(i > 0) {
        i--;
        if(ranges[i].first <= loan && loan <= ranges[i].second) continue;
                
        cout << i << " ";
        if(i % 2 == 1)
            loan += int128_t(i);
        else
            loan -= int128_t(i);
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    pair<int128_t, int128_t> rng = make_pair(int128_t(), int128_t());
    
    for(int i = 0; i <= 100; i++){
        ranges.push_back(rng);
        if(i % 2 == 1) 
            rng.first -= int128_t(i);
        else 
            rng.second += int128_t(i);
    }
    
    int n; cin >> n; while(n--) {
        int128_t loan; cin >> loan;
        
        if(loan <= ranges.back().second)
            obtain(loan);
        else 
            cout << "NIE" << endl;
            
        loan.invert();
        
        if(ranges.back().first <= loan) 
            obtain(loan);
        else 
            cout << "NIE" << endl;
    }
    
    return 0;
}
