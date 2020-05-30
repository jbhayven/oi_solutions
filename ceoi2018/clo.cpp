#include <bits/stdc++.h>
using namespace std;

struct desc {
    int cores;
    int rate;
    int prize;
};

const int MAX_N = 2010;
long long best_result[50 * MAX_N];
int n, m;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    vector<desc> comp(n);
    for(desc &computer : comp)
        cin >> computer.cores >> computer.rate >> computer.prize;
    
    cin >> m;
    vector<desc> orders(m);
    for(desc &o : orders)
        cin >> o.cores >> o.rate >> o.prize;
    
    auto by_rate = [](const desc &a, const desc &b){ return a.rate < b.rate; };
    sort(comp.begin(), comp.end(), by_rate);
    sort(orders.begin(), orders.end(), by_rate);
    
    auto accumulator = [](int sum, const desc& d){ return sum + d.cores; };
    int all_cores = accumulate(comp.begin(), comp.end(), 0, accumulator);
    
    const int TOP_LIMIT = all_cores;
    for(int i = 1; i <= TOP_LIMIT; i++)
        best_result[i] = LONG_LONG_MIN / 10;
    
    while(!orders.empty()) {
        if(!comp.empty() && comp.back().rate >= orders.back().rate) {
            desc c = comp.back(); comp.pop_back();
            for(int i = TOP_LIMIT; i >= c.cores; i--)
                best_result[i] = max(best_result[i], best_result[i - c.cores] - c.prize);
        }
        else {
            desc o = orders.back(); orders.pop_back();
            for(int i = 0; i <= TOP_LIMIT - o.cores; i++)
                best_result[i] = max(best_result[i], best_result[i + o.cores] + o.prize);
        }
    }
    
    long long result = INT_MIN;
    for(int i = 0; i <= TOP_LIMIT; i++)
        result = max(result, best_result[i]);
    
    cout << result << endl;
        
    return 0;
}
