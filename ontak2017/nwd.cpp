#include <bits/stdc++.h>
using namespace std;

struct Breaker {    
    long long val;
    long long other_gcd;
};

struct Info {
    vector<Breaker> breakers;
    vector<long long> big_gcds;
};

Info get_breaker_info(const vector<long long> &big_group) {
    Info result = {
        .breakers = vector<Breaker>(),
        .big_gcds = vector<long long>({0})
    };
    
    long long score = 0;
    long long other_score = 0;
    for (long long val : big_group) {
        long long gcd = __gcd(val, score);
        if (gcd != score) {
            score = gcd;
            result.breakers.push_back({ .val = val, .other_gcd = 0 });
        } else {
            other_score = __gcd(val, other_score);
        }
        
        result.big_gcds.push_back(other_score);
    }
    
    for (size_t i = 0; i < result.breakers.size(); i++) {
        for (size_t j = 0; j < result.breakers.size(); j++) {
            if (i == j) continue;
            
            result.breakers[i].other_gcd = 
                __gcd(result.breakers[i].other_gcd, 
                      result.breakers[j].val);
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    size_t n;
    unordered_map<long long, int> nums;
    
    cin >> n;
    for (size_t i = 0; i < n; i++) {
        long long a; cin >> a;
        nums[a]++;
    }
    
    vector<long long> big_group;
    for (auto pair : nums)
        big_group.push_back(pair.first);
    sort(big_group.begin(), big_group.end());
    
    vector<long long> small_groups({0});
    for (auto it = big_group.rbegin(); it < big_group.rend(); it++)
        for (int i = 1; i < nums[*it]; i++)
            small_groups.push_back(small_groups.back() + *it);
    
    long long big_gcd = 0;
    long long score = 0;
    for (long long num : big_group)
        big_gcd = __gcd(big_gcd, num);
    score = big_gcd;
    
    Info inf = get_breaker_info(big_group);
    vector<long long> part_ans({score});
    vector<size_t> break_pos;
    
    while(!big_group.empty()) {
        long long bonus = 0;
        int flag = -1;
        
        if (big_group.size() > 1) {
            bonus = big_group.back();
            flag = -1;
            for (size_t i = 0; i < inf.breakers.size(); i++) {
                long long change_result = inf.breakers[i].val + __gcd(inf.big_gcds.back(), inf.breakers[i].other_gcd) - big_gcd;
                if (change_result >= bonus) {
                    bonus = change_result;
                    flag = i;
                }
            }
        }
        
        if (flag == -1) {
            big_group.pop_back();
            inf.big_gcds.pop_back();
        } else {
            big_gcd += bonus - inf.breakers[flag].val;
            big_group.erase(std::remove(big_group.begin(), big_group.end(), inf.breakers[flag].val));
            inf = get_breaker_info(big_group);
            break_pos.push_back(part_ans.size());
        }
        
        score += bonus;
        
        // a very special case
        if (big_group.size() == 2 && 2 * big_group[0] > big_group[1] && nums[2 * big_group[0]] > 0) {
            score += big_group[1] - big_group[0] - big_gcd;
            
            big_gcd = big_group[0];
            big_group[1] = 2 * big_group[0];
            inf = get_breaker_info(big_group);
        }
        
        part_ans.push_back(score);
    }
    
    size_t popped = 0;
    for (size_t i = 0; i < n; i++) {
        while (i - popped >= small_groups.size()) popped++;
        
        while(popped + 1 < part_ans.size() && popped < i && 
            part_ans[popped + 1] + small_groups[i - (popped + 1)] > 
                part_ans[popped] + small_groups[i - popped]) {
            popped++;
        }
        
        for (size_t pos : break_pos) {
            if (pos <= popped) continue;
            if (pos > i) break;
            
            if (part_ans[pos] + small_groups[i - pos] > 
                part_ans[popped] + small_groups[i - popped])
                popped = pos;
        }
        
        cout << part_ans[popped] + small_groups[i - popped] << endl;
    }
    
    return 0;
}
