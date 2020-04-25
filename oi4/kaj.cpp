#include <bits/stdc++.h>
using namespace std;

int main() {
    int w, n;
    cin >> w >> n;
    
    vector<int> uczestnicy(n);
    for(int &uczestnik : uczestnicy)
        cin >> uczestnik;

    sort(uczestnicy.begin(), uczestnicy.end());
    list<int> sorted(uczestnicy.begin(), uczestnicy.end());

    int wynik = 0;
    while(!sorted.empty()) {
        if(sorted.back() + sorted.front() <= w)
            sorted.pop_front();
        
        if(!sorted.empty())
            sorted.pop_back();
        
        wynik++;
    }
    cout << wynik << endl;
    
    return 0;
}
