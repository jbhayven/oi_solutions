#include <bits/stdc++.h>
using namespace std;

int s, w;
int n;

struct change {
    int position;
    
    int location;
    int type;

    change(int position, int location, int type) :
        position(position),
        location(location),
        type(type)
    { }
    
    bool operator<(const change& other) {
        if(position != other.position) return position < other.position;
        return type > other.type;
    }
};

class tree {
private:
    tree* left;
    tree* right;
    
    int bonus;
    int max;
    pair<int, int> range;
    
    inline int middle() {
        return (range.first + range.second + 1) / 2 - 1;
    }
    
    inline void assert_children() {
        if(left != nullptr) return;
        
        int s = middle();
    
        left = new tree(range.first, s);
        right = new tree(s + 1, range.second);
    }
    
    inline int real_value() {
        return max + bonus;
    }
    
    inline void push_bonus() {
        left->bonus += bonus;
        right->bonus += bonus;
        max += bonus;
        
        bonus = 0;
    }
    
public:
    tree(int p, int q) :
        left(nullptr),
        right(nullptr),
        bonus(0),
        max(0),
        range({p, q})
    {}
    
    void update(int a, int b, int val) {
        if(a <= range.first && range.second <= b) {
            bonus += val;
            return;
        }
        
        assert_children();
        push_bonus();
        
        if(a <= left->range.second)
            left->update(a, b, val);
        if(right->range.first <= b)
            right->update(a, b, val);
        
        max = std::max(left->real_value(), right->real_value());
    }
    
    int get_max() {
        return real_value();
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> s >> w;
    cin >> n;
    
    vector<pair<int, int>> nuggets(n);
    for(auto &nugget : nuggets) 
        cin >> nugget.first >> nugget.second;
        
    vector<change> changes;
        
    for(auto nugget : nuggets) {
        changes.push_back(change(nugget.first, nugget.second, 1));
        changes.push_back(change(nugget.first + s, nugget.second, -1));
    }
    
    sort(changes.begin(), changes.end());
    int result = 0;
    tree* mine_data = new tree(-40000, 40000);
    
    for(change c : changes) {
        mine_data->update(c.location, c.location + w, c.type);
        result = max(result, mine_data->get_max());
    }
    
    cout << result << endl;
    
    return 0;
}
