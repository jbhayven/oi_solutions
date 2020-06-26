#include <bits/stdc++.h>
using namespace std;

struct Gate {
    pair<int, int> pt[2];
};

long long prod( pair<int, int> a,
                pair<int, int> b,
                pair<int, int> c) {
                    
    return    (long long) (c.first - b.first) * (a.second - b.second) 
            - (long long) (a.first - b.first) * (c.second - b.second); 
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    list<Gate> gates;
    
    cin >> n;
    
    pair<int, int> start;
    cin >> start.first >> start.second;
    
    pair<int, int> end;
    cin >> end.first >> end.second;
    
    gates.resize(n);
    for(auto &gate : gates) {
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        
        gate.pt[0] = {x1, y};
        gate.pt[1] = {x2, y};
    }
    gates.push_back({ .pt = {end, end} }); // add end as a gate
    
    deque< pair<int, int> > hull[2] = {{start}, {start}};
    const int side_factor[2] = {-1, 1};
    vector< pair<int, int> > result = {start};
    
    for(const auto &gate : gates) {
        for(int i = 0; i <= 1; i++) {
            while(hull[i].size() > 1 
                    && prod(gate.pt[i], hull[i].end()[-1], hull[i].end()[-2])
                        * side_factor[i] >= 0 ) {
                hull[i].pop_back();
            }
            hull[i].push_back(gate.pt[i]);
        }
        for(int i = 0; i <= 1; i++) {
            while(hull[1 - i].size() > 2 
                    && prod(gate.pt[i], hull[1 - i][1], hull[1 - i][0])
                        * side_factor[i] >= 0 ) {
                hull[1 - i].pop_front();
                start = hull[1 - i].front();
                            
                while (hull[i].size() > 0 
                    && start.second <= hull[i].front().second)
                        hull[i].pop_front();
                        
                hull[i].push_front(start);
            
                while (result.size() > 1 
                    && prod(start, result.end()[-1], result.end()[-2]) == 0)
                        result.pop_back();
                    
                result.push_back(start);
            }
        }
    }
    
    for (const auto &pt : hull[0])
        if (pt.second < result.back().second)
            result.push_back(pt);
    
    cout << result.size() << "\n";
    for(const auto &pt : result) 
        cout << pt.first << " "<< pt.second << "\n";
    
    return 0;
}
