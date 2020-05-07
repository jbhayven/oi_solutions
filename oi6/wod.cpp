#include <bits/stdc++.h>
using namespace std;

#define MAX_DIM 110

int wys[MAX_DIM][MAX_DIM];
bool odw[MAX_DIM][MAX_DIM];
int wynik;

inline int enhash(int i, int j) {
    return MAX_DIM * i + j;
}

pair<int, int> unenhash(int enhash) {
    return {enhash / MAX_DIM, enhash % MAX_DIM};
}
    
int main() {
    int n, m;
    cin >> n >> m;
    
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> wys[i][j];
    
    using PI = pair<int, int>;
    priority_queue< PI, vector<PI>, greater<PI> > cand;
    
    for(int i = 1; i <= n; i++) {
        cand.push({wys[i][1], enhash(i, 1)});
        cand.push({wys[i][m], enhash(i, m)});
    }
    
    for(int j = 1; j <= m; j++) {
        cand.push({wys[1][j], enhash(1, j)});
        cand.push({wys[n][j], enhash(n, j)});
    }
    
    while(!cand.empty()) {
        auto top = cand.top();
        cand.pop();
        
        auto coord = unenhash(top.second);
        int i = coord.first;
        int j = coord.second;
        
        if(odw[i][j]) continue;
        else {
            int h = wys[i][j];
            stack<PI> to_visit;
            to_visit.push(coord);
            
            while(!to_visit.empty()) {
                auto coord = to_visit.top();
                int i = coord.first;
                int j = coord.second;
                
                to_visit.pop();
                if(odw[i][j]) continue;
                else {
                    odw[i][j] = true;
                    wynik += (h - wys[i][j]);
                    for(auto neighbour : array<PI, 4>{{{i - 1, j}, {i + 1, j}, {i, j - 1}, {i, j + 1}}}) {
                        int new_i = neighbour.first;
                        int new_j = neighbour.second;
                        
                        if(new_i < 1 || new_j < 1 || new_i > n || new_j > m) continue;
                        
                        if(odw[new_i][new_j]) continue;
                        else {
                            if(wys[new_i][new_j] <= h)
                                to_visit.push(neighbour);
                            else 
                                cand.push({wys[new_i][new_j], enhash(new_i, new_j)});
                        }
                    }
                }
            }
        }
    }
    
    cout << wynik << endl;
    
    return 0;
}
