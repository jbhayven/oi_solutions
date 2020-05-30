#include <bits/stdc++.h>
using namespace std;

vector<int> generate_primes(int B) {
    vector<bool> is_prime(B + 1, true);
    vector<int> primes;
    
    for(int i = 2; i <= B; i++)
        if(is_prime[i]) {
            primes.push_back(i);
            for(int j = i; j <= B; j += i)
                is_prime[j] = false;
        }
    return primes;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m, B;
    cin >> n >> m >> B;
    
    vector<int> primes;
    primes = generate_primes(B);
    
    int result = 0;
    int limit = n + m + 1;
    while(n < limit) { 
        vector<int> nums(min(B, limit - n));
        std::generate(nums.begin(), nums.end(), 
                [num = n] () mutable { return num++; });
        
        for(int p : primes)
            for(size_t i = (p - (n % p)) % p; i < nums.size(); i += p)
                while(nums[i] % p == 0)
                    nums[i] /= p;
        
        for(int n : nums)
            if(n == 1) result++;
        
        n += B;
    }
    cout << result << endl;
    
    return 0;
}
