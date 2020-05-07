#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 110;
const int MAX_K = 410;

class bigint {
private:
    const int MAX = 1e9;
    vector<int> digits;
public:
    bigint() :
        digits{0}
    {}
    
    bigint operator+=(int other) {
        for(int &digit : digits) {
            digit += other;
            if(digit > MAX) {
                digit -= MAX;
                other = 1;
            }
            else other = 0;
        }
        
        if(other > 0) digits.push_back(other);
        return *this;
    }
    
    bigint operator+=(const bigint &other) {
        if(digits.size() < other.digits.size()) 
            digits.resize(other.digits.size());
            
        int carry = 0;
        for(size_t i = 0; i < digits.size(); i++) {
            if(i < other.digits.size())
                digits[i] += other.digits[i];
            digits[i] += carry;
            if(digits[i] > MAX) {
                digits[i] -= MAX;
                carry = 1;
            }
            else carry = 0;
        }
        
        if(carry > 0) digits.push_back(carry);
        return *this;
    }
    
    const bigint operator=(const bigint &other) {
        digits = vector<int>(other.digits);
        return *this;
    }
    
    friend ostream& operator<<(ostream &os, const bigint &num) {
        bool leading_found = false;
        for(int digit : vector<int>(num.digits.rbegin(), num.digits.rend())) {
            if(digit > 0) leading_found = true;
            if(leading_found) 
                os << digit << setfill('0') << setw(9);
        }
        
        if(leading_found == false) os << '0';
        
        os << setw(0);
        return os;
    }
};


bigint result[MAX_N][MAX_K];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k;
    cin >> n >> k;
    
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= k; j++) {
            result[i][j] = result[i-1][j];
            if(i > 2)
                result[i][j] += result[i-2][max(j - i, 0)];
            if(j < i)
                result[i][j] += 1;
        }
    
    cout << result[n][k] << endl;
    
    return 0;
}
