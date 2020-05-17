#include <bits/stdc++.h>
using namespace std;

pair<int, int> get_result(string& desc, auto select) {
    int children = desc.back() - '0';
    desc.pop_back();
    
    if(children == 0) return {1, 0};
    if(children == 1) {
        auto from_child = get_result(desc, select);
        return {from_child.second + 1, select(from_child.first, from_child.second)};
    }
    else {
        auto from_left = get_result(desc, select);
        auto from_right = get_result(desc, select);
        
        return {from_left.second + from_right.second + 1, 
                select(from_left.first + from_right.second, 
                       from_right.first + from_left.second)
                };
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string desc; cin >> desc;
    reverse(desc.begin(), desc.end());
    
    string desc_cpy(desc);
    auto result_max = get_result(desc_cpy, [](int a, int b){ return max(a, b); });
    auto result_min = get_result(desc, [](int a, int b){ return min(a, b); });
    
    cout << max(result_max.first, result_max.second) << " "
         << min(result_min.first, result_min.second) << endl;
    
    return 0;
}
