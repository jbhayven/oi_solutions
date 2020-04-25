#include <bits/stdc++.h>
using namespace std;

int result = 0;
int n; 

inline int dist(int i, int j) {
    if(i < j) return min(j - i, n + i - j);
    else return min(i - j, n + j - i);
}

int find_penalty(int dir, int pos, vector<int> &origin, bool modify) {
    int i = 0;
    while(origin[i] != pos) i++;
        
    int penal_temp = dist(pos, i);
    int curr_origin = origin[i];
        
    do{
        penal_temp -= dist(curr_origin, i);
        int new_i = (i + dir + n) % n;
        
        penal_temp += dist(curr_origin, new_i);
        i = new_i;
        
        if(modify == true)
            swap(curr_origin, origin[i]);
        else
            curr_origin = origin[i];
    } while(curr_origin != -1);
    
    return penal_temp;
}

void add(int pos, vector<int> &origin) {
    vector<int> penalty;
    
    for(int dir : {-1, 1})
        penalty.push_back(find_penalty(dir, pos, origin, false));
    int dir = penalty[0] < penalty[1] ? -1 : 1;
    
    result += find_penalty(dir, pos, origin, true);
}
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    
    vector<int> origin(n, -1);
    
    vector<int> boxes(n);
    for(auto &box : boxes)
        cin >> box;
    
    for(int i = 0; i < n; i++)
        if(boxes[i] > 0) {
            boxes[i]--;
            origin[i] = i;
        }
        
    for(int i = 0; i < n; i++)
        while(boxes[i]--)
            add(i, origin);
    
    cout << result << endl;
    
    return 0;
}
