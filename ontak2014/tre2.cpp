#include <bits/stdc++.h>
using namespace std;

#define MAX_N 3001
#define HALF 16
#define hash(i, j) (((i) << HALF) | (j))
#define big(x) (((x) >> HALF) & 0x0000ffff)
#define small(x) ((x) & 0x0000ffff)
#define HALF_MEM 5

int right_cell[MAX_N][MAX_N];
int down_cell[MAX_N][MAX_N];
    
int in_log[HALF_MEM][MAX_N][MAX_N][2];
int m, r; 
vector<string> types;
    
void reset() {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < m; j++) {
            if (types[i][j] == 'O') {
                in_log[0][i][j][0] = hash(i, j+1);
                in_log[0][i][j][1] = hash(i+1, j);
            } else if (types[i][j] == 'M') {
                in_log[0][i][j][0] = hash(i, j+1);
                in_log[0][i][j][1] = hash(i, j+1);
            } else if (types[i][j] == 'R') {
                in_log[0][i][j][0] = hash(i+1, j);
                in_log[0][i][j][1] = hash(i+1, j);
            } else {
                in_log[0][i][j][0] = hash(i, j);
                in_log[0][i][j][1] = hash(i, j);
            }
        }
}

void update_all(int from, int to) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < m; j++) {
            int right = in_log[from][i][j][0];
            int down = in_log[from][i][j][1];
            in_log[to][i][j][0] = in_log[from][big(right)][small(right)][0];
            in_log[to][i][j][1] = in_log[from][big(down)][small(down)][1];
        }
    }
}

void fix_dists() {
    for (int l = HALF_MEM - 1; l >= 0; l--) 
        for (int i = 0; i < r; i++)
            for (int j = 0; j < m; j++) {
                if (types[i][j] != 'O') continue;
                    
                if (in_log[l][big(right_cell[i][j])][small(right_cell[i][j])][1] < 
                    in_log[l][big(down_cell[i][j])][small(down_cell[i][j])][0]) {
                        right_cell[i][j] = in_log[l][big(right_cell[i][j])][small(right_cell[i][j])][1];
                        down_cell[i][j] = in_log[l][big(down_cell[i][j])][small(down_cell[i][j])][0];
                } 
            }
}
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> m >> r;
    types.resize(r);
    for (auto &s : types) cin >> s;
    
    for (int i = 0; i < r; i++)
        for (int j = 0; j < m; j++) {
            right_cell[i][j] = hash(i, j+1);
            down_cell[i][j] = hash(i+1, j);
        }
        
    reset();
    for (int l = 1; l <= 2*HALF_MEM; l++)
        update_all(0, 0);
    for (int l = 1; l < HALF_MEM; l++)
        update_all(l-1, l);
    fix_dists();
            
    reset();
    for (int l = 1; l <= HALF_MEM; l++)
        update_all(0, 0);
    for (int l = 1; l < HALF_MEM; l++)
        update_all(l-1, l);
    fix_dists();
    
    reset();
    for (int l = 1; l < HALF_MEM; l++)
        update_all(l-1, l);
    fix_dists();
    
    for (int i = r-1; i >= 0; i--) {
        for (int j = m-1; j >= 0; j--) {
            in_log[0][i][j][0] = 1;
            
            if (types[i][j] == 'O')
                in_log[0][i][j][0] += (in_log[0][i+1][j][0] + in_log[0][i][j+1][0] - in_log[0][big(right_cell[i][j]) + 1][small(right_cell[i][j])][0]);
            else if (types[i][j] == 'M') 
                in_log[0][i][j][0] += in_log[0][i][j+1][0];
            else if (types[i][j] == 'R')
                in_log[0][i][j][0] += in_log[0][i+1][j][0];
        }
    }
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < m; j++) 
            cout << in_log[0][i][j][0] << " ";
        cout << endl;
    }
    
    return 0;
}
