#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 110;

// min_moves[a][b][i][j] -- min_moves to reach a state
// where the worker is at {a, b} and the box at {i, j}
int min_moves[MAX_N][MAX_N][4];
bool passable[MAX_N][MAX_N];
bool discovered[MAX_N][MAX_N][4];

vector< pair<int, int> > move_vec = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};
    
int n, m;

pair<int, int> M, P, K;

inline bool is_passable(int i, int j) {
    if(i < 0 || i >= n) return false;
    if(j < 0 || j >= m) return false;
        
    return passable[i][j];
}

void discover(int i, int j, auto start_mag, auto &queue, int moves) {
    static int era = 1;
    static auto last_visit = vector(n, vector(m, 0));
    
    era++;
    last_visit[start_mag.first][start_mag.second] = era;
    stack< pair<int, int> > positions({start_mag});

    while(!positions.empty()) {
        auto curr_pos = positions.top();
        positions.pop();
        
        int move_no = -1;
        for(auto move : move_vec) {
            ++move_no;
            
            int new_x = curr_pos.first + move.first;
            int new_y = curr_pos.second + move.second;
            
            if(is_passable(new_x, new_y) == false) continue;
            
            if(new_x == i && new_y == j) {
                discovered[i][j][move_no] = true;
                
                int new_i = i + move.first;
                int new_j = j + move.second;
                
                if(is_passable(new_i, new_j) == false) continue;
                if(min_moves[new_i][new_j][move_no] != INT_MAX) continue;
                
                min_moves[new_i][new_j][move_no] = moves + 1;
                queue.push(make_tuple(new_i, new_j, move_no));
            }
            else {
                if(last_visit[new_x][new_y] == era) continue;
                    
                last_visit[new_x][new_y] = era;
                positions.push({new_x, new_y});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
        
    cin >> n >> m;
                    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            passable[i][j] = true;
            for(int k = 0; k < 4; k++)
                min_moves[i][j][k] = INT_MAX;
        }
                
    for(int i = 0; i < n; i++) {
        string word;
        cin >> word;
        for(int j = 0; j < m; j++) {
            switch(word[j]) {
            case 'W':
                break;
            case 'S':
                passable[i][j] = false;
                break;
            case 'M':
                M = {i, j};
                break;
            case 'P':
                P = {i, j};
                break;
            case 'K':
                K = {i, j};
                break;
            }
        }
    }
    
    queue< tuple<int, int, int> > states; 
    discover(P.first, P.second, M, states, 0);
    
    while(!states.empty()) {
        int i, j, move_no;
        tie(i, j, move_no) = states.front();
        states.pop();
    
        int moves = min_moves[i][j][move_no];
        pair<int, int> mag_pos = {i - move_vec[move_no].first, j - move_vec[move_no].second};
        if(discovered[i][j][move_no] == false) 
            discover(i, j, mag_pos, states, moves);
    }
                
    int result = INT_MAX;
    for(int k = 0; k < 4; k++)
        result = min(result, min_moves[K.first][K.second][k]);
                
    if(result == INT_MAX)  
        cout << "NIE" << endl;
    else 
        cout << result << endl;
    
    return 0;
}
