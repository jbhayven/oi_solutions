#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 7;

class holder : public multiset<int> {
    long long sum;
    
public:
    void insert(int a) {
        sum += a;
        multiset<int>::insert(a);
    }
    
    void erase(const_iterator a) {
        sum -= *a;
        multiset<int>::erase(a);
    }
    
    long long get_sum() { return sum; }
};

void even_out(holder &lower, holder &upper) {
    if (lower.size() > upper.size()) {
        upper.insert(*lower.rbegin());
        lower.erase(--lower.cend());
    }
    
    if (lower.size() + 1 < upper.size()) {
        lower.insert(*upper.begin());
        upper.erase(upper.cbegin());
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, k;
    set<int> less, more;
    
    cin >> n >> k;
    
    array<int, MAX_N> nums;
    
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    
    holder upper, lower;
    
    for (int i = 0; i < k-1; i++)
        lower.insert(nums[i]);
        
    while (lower.size() > upper.size()) {
        upper.insert(*lower.rbegin());
        lower.erase(--lower.cend());
    }
    
    long long best_result = 1e15;
    long long opt_val = -1;
    int best_pos = -1;
    for (int i = k - 1; i < n; i++) {
        if (upper.empty() || nums[i] < *upper.begin()) {
            lower.insert(nums[i]);
        } else {
            upper.insert(nums[i]);
        }
        
        even_out(lower, upper);
        
        long long val = *upper.begin();
        long long new_result = lower.size() * val - lower.get_sum() + upper.get_sum() - upper.size() * val;
        if (new_result < best_result) {
            best_result = new_result;
            best_pos = i - k + 1;
            opt_val = val;
        }
        
        if (nums[i - k + 1] < *upper.begin()) {
            lower.erase(lower.find(nums[i - k + 1]));
        } else {
            upper.erase(upper.find(nums[i - k + 1]));
        }
        
        even_out(lower, upper);
    }
    
    for (int i = best_pos; i < best_pos + k; i++)
        nums[i] = opt_val;
    
    cout << best_result << endl;
    for (int i = 0; i < n; i++)
        cout << nums[i] << "\n";
    
    return 0;
}

