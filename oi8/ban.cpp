#include <bits/stdc++.h>
using namespace std;

vector< array<int, 4> > curr_credit;
vector< array<int, 4> > left_credit;

array<int, 4> result = {0, 0, 0, 0};
int n;

void adjust(int top_col) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cand[4];
    vector<int> rdy;
    array<int, 4> curr = result;
    
    for(int i = 0; i < n; i++) 
        cand[0].push(make_pair(left_credit[i][0], i));
    
    int handled = 0;
    while(handled < n) {
        for(int i = 0; i <= top_col; i++) {
            while(!cand[i].empty() && left_credit[cand[i].top().second][i] <= curr[i]) {
                int top = cand[i].top().second;
                cand[i].pop();
                
                if(i+1 <= top_col)
                    cand[i+1].push(make_pair(left_credit[top][i+1], top));
                else
                    rdy.push_back(top);
            }
        }
        
        if(rdy.empty()) {
            int top = cand[top_col].top().second;
            int missing = left_credit[top][top_col] - curr[top_col];
            result[top_col] += missing;
            curr[top_col] += missing;
        }
        else {
            while(!rdy.empty()) {
                int top = rdy.back();
                rdy.pop_back();
                for(int j = 0; j < 4; j++)
                    curr[j] += curr_credit[top][j];
                handled++;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    for(int i = 0; i < n; i++) {
        array<int, 4> m, w;
        
        for(int &num : m) cin >> num;
        for(int &num : w) cin >> num;
        
        curr_credit.push_back(w);

        for(int j = 0; j < 4; j++)
            w[j] = m[j] - w[j];
            
        left_credit.push_back(w);
    }
    
    for(int i = 0; i < 4; i++) 
        adjust(i);
    
    for(int i = 0; i < 4; i++)
        cout << result[i] << " ";
    cout << endl;
    
    return 0;
}
