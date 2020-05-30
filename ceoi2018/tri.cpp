#include <bits/stdc++.h>
#include "trilib.h"
using namespace std;

bool start_bad(const list<int> &hull_1, const list<int> &hull_2) {
    if(hull_1.size() < 2) return false;
    
    return !is_clockwise(hull_2.back(), hull_1.front(), *++hull_1.begin());
}

bool end_bad(const list<int> &hull_1, const list<int> &hull_2) {
    if(hull_1.size() < 2) return false;
    
    return !is_clockwise(*++hull_1.rbegin(), hull_1.back(), hull_2.front());
}

bool can_fix(const list<int> &hull_1, const list<int> &hull_2) {
    if(start_bad(hull_1, hull_2)) return true;
    if(start_bad(hull_2, hull_1)) return true;
    if(end_bad(hull_1, hull_2)) return true;
    if(end_bad(hull_2, hull_1)) return true;
    
    return false;
}

int main() {
    int n = get_n();
    
    vector<int> pts[2];
    
    for(int i = 3; i <= n; i++)
        pts[!is_clockwise(1, 2, i)].push_back(i);
    
    for(int i = 0; i <= 1; i++)
        sort(pts[i].begin(), pts[i].end(), 
             [=](int a, int b){ return is_clockwise((i+1), a, b); });
    
    list<int> hull[2];
    for(int i = 0; i <= 1; i++) {
        hull[i] = list({(i + 1), (2 - i)});
        for(int pt : pts[i]) {
            while(!is_clockwise(*++hull[i].rbegin(), hull[i].back(), pt))
                hull[i].pop_back();
            hull[i].push_back(pt);
        }
        hull[i].pop_front();
    }
    while(can_fix(hull[0], hull[1])) {
        if(start_bad(hull[0], hull[1]))   
            hull[0].pop_front();
        if(start_bad(hull[1], hull[0]))
            hull[1].pop_front();
        if(end_bad(hull[0], hull[1])) 
            hull[0].pop_back();
        if(end_bad(hull[1], hull[0])) 
            hull[1].pop_back();
    }
    
    give_answer(hull[0].size() + hull[1].size());
    return 0;
}
