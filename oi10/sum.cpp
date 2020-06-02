#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    vector<int> liczby(n);
    for(int &liczba : liczby)
        cin >> liczba;
        
    sort(liczby.begin(), liczby.end());
    
    int przedz = liczby[0];
    
    vector<bool> zajeta_reszta(przedz, false);
    zajeta_reszta[0] = true;
    
    vector<int> uzyteczne;
    
    for(int liczba : liczby) 
        if(!zajeta_reszta[liczba % przedz]) {
            zajeta_reszta[liczba % przedz] = true;
            uzyteczne.push_back(liczba);
        }
        
    vector<int> kiedy_wchodzi(przedz, INT_MAX);
    kiedy_wchodzi[0] = 0;
    
    using pi = pair<int, int>;
    priority_queue< pi, vector<pi>, greater<pi> > kolejnosc;
    kolejnosc.push({0, 0});
    
    vector< bool > przetw(przedz, false);
            
    while(!kolejnosc.empty()) {
        int reszta = kolejnosc.top().second; kolejnosc.pop();
        
        if(przetw[reszta]) continue;
        
        przetw[reszta] = true;
        
        for(int n : uzyteczne) {
            int nowa = reszta + n;
            int czas = kiedy_wchodzi[reszta] + nowa / przedz;
            int nowa_reszta = nowa % przedz;
            if(kiedy_wchodzi[nowa_reszta] > czas) {
                kiedy_wchodzi[nowa_reszta] = czas;
                kolejnosc.push({czas, nowa_reszta});
            }
        }
    }
        
    int k; cin >> k;
    while(k--) {
        int b; cin >> b;
        if(kiedy_wchodzi[b % przedz] <= b / przedz)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
        
    return 0;
}
