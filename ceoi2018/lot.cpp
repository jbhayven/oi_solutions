#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10010;
const int MAX_Q = 110;

int q;
vector<int> queries;

vector<int> ans[MAX_Q];

int cnt[MAX_N];
int sum[MAX_N];

int sim[MAX_N];
int a[MAX_N];

int n, l;

void push_ans() {
    sum[0] = cnt[l] - 1;
    for (int i = 1; i <= l; i++) 
        sum[i] = sum[i-1] + cnt[l-i];
        
    for (int i = 0; i < q; i++) 
        ans[i].push_back(sum[queries[i]]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> l;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    
    cin >> q;
    for (int i = 0; i < q; i++) {
        int k; cin >> k;
        queries.push_back(k);
    }
    
    for (int i = 1; i <= n - l + 1; i++) {
        for (int j = 0; j < l; j++)
            sim[i] += (a[1 + j] == a[i + j]);
        
        cnt[sim[i]]++;
    }
    
    push_ans();
    
    for (int i = 2; i <= n - l + 1; i++) {
        for (int j = 1; j <= n - l; j++) {
            cnt[sim[j]]--;
            sim[j] -= (a[j] == a[i-1]);
            sim[j] += (a[j+l] == a[i-1+l]);
            cnt[sim[j]]++;
        }
        
        cnt[sim[n-l+1]]--;
        for (int j = n-l+1; j > 0; j--)
            sim[j] = sim[j-1];
        
        for (int j = 0; j < l; j++)
            sim[1] += (a[1 + j] == a[i + j]);
        cnt[sim[1]]++;
        
        push_ans();
    }
    
    for (int i = 0; i < q; i++) { 
        for (int a : ans[i])
            cout << a << " ";
        cout << endl;
    }
    
    return 0;
}
