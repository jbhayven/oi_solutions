#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1010;

vector<int> graph[MAX_N];
int deg[MAX_N];
int result = 0;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    while(n--) {
        int l, r; 
        cin >> l >> r;
        graph[l].push_back(r);
        deg[l]--;
        deg[r]++;
    }
    
    vector<bool> adventurous(1001, false);
    for(int i = 1; i <= 1000; i++)
        while(deg[i] < 0) {
            adventurous[i] = true;
            deg[i]++;
            int curr = i;
            result++;
            
            while(!graph[curr].empty()) {
                int next = graph[curr].back();
                graph[curr].pop_back();
                
                curr = next;
                result++;
            }
            
            deg[curr]--;
        }
    
    for(int i = 1; i <= 1000; i++)
        while(!graph[i].empty()) {
            int curr = i;
            if(adventurous[i] == false)
                result++;
            
            while(!graph[curr].empty()) {
                int next = graph[curr].back();
                graph[curr].pop_back();
                
                curr = next;
                result++;
            }
        }
    
    cout << result << endl;
    
    return 0;
}
