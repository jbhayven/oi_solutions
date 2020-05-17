#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1010;

class bigint {
private:
    static const int LIMIT = 1e9;
    vector<int> digits;
    
public:
    bigint() : digits({0}) {}
    bigint(int a) : digits({a}) {}

    bigint& operator+=(const bigint& other) {
        for(size_t i = 0; i < other.digits.size(); i++)
            if(i < digits.size())
                digits[i] += other.digits[i];
            else
                digits.push_back(other.digits[i]);
                
        for(size_t i = 0; i < digits.size(); i++) 
            if(digits[i] > LIMIT) {
                if(i + 1 < digits.size())
                    digits[i+1]++;
                else
                    digits.push_back(1);
                digits[i] -= LIMIT;
            }
        return *this;
    }
    
    bigint operator+(const bigint& other) {
        bigint result;
        result += *this;
        result += other;
        return result;
    }
    
    friend ostream& operator<<(ostream& os, const bigint& num) {
        for(auto it = num.digits.rbegin(); it != num.digits.rend(); it++)
            os << (*it) << setw(9) << setfill('0');
        os << setw(0);
        
        return os;
    }
};

int n;
bigint times[MAX_N][2];
bigint clean[MAX_N]; // moves needed to change the type of a certain chain link
bool type[MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    
    for(int i = 1; i <= n; i++)
        cin >> type[i];
        
    for(int i = 1; i <= n; i++) 
        clean[i] = clean[i-1] + 1 + clean[i-1];
        
    for(int i = 1; i <= n; i++) {
        times[i][type[i]] = times[i-1][0];
        times[i][!type[i]] = times[i-1][1] + 1 + clean[i-1];
    }
    
    cout << times[n][0] << endl;
    
    return 0;
}
