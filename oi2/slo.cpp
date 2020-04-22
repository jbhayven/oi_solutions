#include <bits/stdc++.h>
using namespace std;

#define MILLION 1000000

const int MAX_N = 210;

vector<bool> kmp(string model, string source) {
    string test = "#" + model + "%" + source;
    
    vector<size_t> temp_result(test.size(), 0);
    temp_result[0] = -1;
    
    size_t i = 1, k = 0;
    
    while(i < test.size()) {
        while(k && test[i] != test[k]) k = temp_result[k - 1] + 1;
        temp_result[i] = k;
        
        i++; k++;
    }
    
    vector<bool> result;
    for(size_t i = model.size() + 2; i < temp_result.size(); i++)
        result.push_back(temp_result[i] == model.size());
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    string w;
    int k;
    
    cin >> w;
    
    vector<int> result(w.size() + 1, 0);
    result[0] = 1;
    
    vector< pair<int, int> > last_elem(w.size() + 1, {-1, -1});

    cin >> k;
    for(int cand = 1; cand <= k; cand++) {
        string candidate;
        cin >> candidate;
        auto appearances = kmp(candidate, w);        

        for(int i = w.size(); i > 0; i--) {
            if(appearances[i-1] && result[i - candidate.size()] > 0) {
                result[i] += result[i - candidate.size()]; 
                if(result[i] > MILLION)
                    result[i] = MILLION;
                
                if(last_elem[i].first == -1)
                    last_elem[i] = make_pair(cand, candidate.size());
            }
        }
    }
    
    if(result[w.size()] == 0)
        cout << "NIE" << endl;
    else {
        cout << result[w.size()] << endl;
        vector<int> answer;
        int i = w.size();
        while(i) {
            answer.push_back(last_elem[i].first);
            i -= last_elem[i].second;
        }
        reverse(answer.begin(), answer.end());
        for(int index : answer)
            cout << index << endl;
    }
    
    return 0;
}
