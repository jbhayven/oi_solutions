#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 51000;
const char MAX_CHAR = 122;
const char MIN_CHAR = 48;
const size_t W_LEN = 5;
const size_t MASK_WIDTH = 64;
const size_t MAX_ANS = 1e5;                                              
const uint64_t FULL_MASK = -1;    

int n;
uint64_t mask[MAX_N / MASK_WIDTH][MAX_CHAR - MIN_CHAR + 1][W_LEN];
string word[MAX_N];

vector<pair<int, int>> ans;

#define remap(x) (x - MIN_CHAR)

inline void try_pair(int i, int j) {
    if (i >= n || j >= n) return;
    
    for (int k = 0; k < W_LEN; k++)
        if (word[i][k] == word[j][k]) return;
        
    ans.emplace_back(i + 1, j + 1);
}

unordered_map<uint64_t, int> mapped;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> word[i];
        
    for (uint i = 0; i < MASK_WIDTH; i++) {
        mapped[(1LLU << i)] = i;
    }
        
    for (int i = 0; i < n; i++)
        for (uint j = 0; j < W_LEN; j++)
            mask[i / MASK_WIDTH][remap(word[i][j])][j] |= (1LLU << (i % MASK_WIDTH));
            
    for (int i = 0; i < n && ans.size() < MAX_ANS; i++) {
        for (uint j = i + 1; j < n && j % MASK_WIDTH != 0; j++)
            try_pair(i, j); 
        
        int group = i / MASK_WIDTH;
        for (uint j = group + 1; j <= n / MASK_WIDTH; j++) {
            uint64_t temp = 0;
            for (uint k = 0; k < W_LEN; k++)
                temp |= mask[j][remap(word[i][k])][k];
                          
            temp = ~temp;  
            
            while (temp) {
                uint64_t first = temp & (~temp + 1);
                int k = mapped[first];
                temp -= first;
                
                if (j * MASK_WIDTH + k >= n) break;
                ans.emplace_back(i + 1, j * MASK_WIDTH + k + 1);
            }
        }
    }
    
    size_t ans_size = min(MAX_ANS, ans.size());
    cout << ans_size << endl;
    for (uint i = 0; i < ans_size; i++)
        cout << ans[i].first << " " << ans[i].second << endl;
    
    return 0;
}
