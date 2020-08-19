#include <bits/stdc++.h>
using namespace std;

class bigint_t {
    static const int limit = 1e9;
    vector<int> nums;
    
public:
    bigint_t() : nums({0}) {}
    bigint_t(int a) : nums({a}) {}

    bigint_t operator+=(const bigint_t &other) {
        nums.resize(max(nums.size(), other.nums.size()));
        
        size_t i = 0;
        while (i < nums.size() && i < other.nums.size()) {
            nums[i] += other.nums[i];
            i++;
        }
        
        i = 0;
        while (i < nums.size()) {
            if (nums[i] >= limit) {
                nums[i] -= limit;
                if (i + 1 >= nums.size()) nums.emplace_back(1);
                else nums[i + 1]++;
            }
            i++;
        }
        
        return *this;
    }
    
    const bigint_t operator+(const bigint_t &other) const {
        return bigint_t(*this) += other;
    }
    
    friend ostream& operator<<(ostream &os, const bigint_t num) {
        os << num.nums.back();
        
        for (int i = (int) num.nums.size() - 2; i >= 0; i--)
            os << setw(9) << setfill('0') << num.nums[i];
        
        return os;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    vector<bool> taken(2*n+2, false);
    
    vector<int> nums[2] = {vector<int>(n+2, 0), vector<int>(n+2, 0)};
    for (int i = 0; i <= 1; i++)
        for (int j = 1; j <= n; j++) {
            cin >> nums[i][j];
            taken[nums[i][j]] = true; // if 0 then don't care
        }
    
    vector<bigint_t> result[2] = {vector<bigint_t>(n+2, 0), vector<bigint_t>(n+2, 0)};
    result[0][0] = 1;
    
    for (int i = 1; i <= 2*n; i++) {
        vector<bigint_t> new_result[2] = {vector<bigint_t>(n+2, 0), vector<bigint_t>(n+2, 0)};
        for (int j = 1; j <= n; j++) {
            if (taken[i] == false && nums[0][j] == 0 ||
                taken[i] == true && nums[0][j] == i ) {
                if (i - j >= 0 && i - j < j)
                    new_result[0][j] = result[0][j-1] + result[1][i - j];
            }
            if (taken[i] == false && nums[1][j] == 0 ||
                taken[i] == true && nums[1][j] == i ) {
                if (i - j >= j && i - j <= n) 
                    new_result[1][j] = result[1][j-1] + result[0][i - j];
            }
        }
        
        for (int j = 0; j <= 1; j++)
            result[j] = new_result[j];
    }
    
    cout << result[1][n] << endl;
    return 0;
}
