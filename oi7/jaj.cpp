#include "jajmod.h"
#include <bits/stdc++.h>
using namespace std;

namespace jaj {
    pair<int, int> zakr;
    int pyt;
    int curr_jajka;
};

void nowy_eksperyment() {
    using namespace jaj;
    
    zakr = {1, wysokosc};
    curr_jajka = jajka;
    wiem = NIE;
}

void daj_pytanie() {
    using namespace jaj;
    
    if(zakr.second - zakr.first + 1 <= 2) // special case
        pyt = zakr.first;
    else if(curr_jajka == 1) // would take very long to compute the slow way
        pyt = zakr.first;
    else if(curr_jajka > 30)
        pyt = (zakr.first + zakr.second) / 2;
    else {
        /* granice_i[j] = {how many levels can we handle with i eggs and at most j queries}
         * granice_i[j] = granice_i-1[j-1] + 1 + granice_i[j-1] (we check one level
         *                and either lose an egg and go down or save it and go up
         */ 
        vector<int> granice({1});
        while(granice.back() + granice.size() < zakr.second - zakr.first) 
            granice.push_back(granice.back() + granice.size() + 1);
        
        for(int i = 3; i <= curr_jajka; i++) {
            vector<int> nowy({1});
            for(int prev : granice) {
                if(nowy.back() + prev >= zakr.second - zakr.first) break;
                nowy.push_back(nowy.back() + prev + 1);
            }
            granice = nowy;
        }
        
        pyt = zakr.second - granice.back();
    }
    
    pietro = pyt;
}

void analizuj_odpowiedz() {
    using namespace jaj;
    
    if(odpowiedz == TAK) 
        zakr.first = pyt + 1;
    else {
        curr_jajka--;
        zakr.second = pyt - 1;
    }
    
    if(zakr.first > zakr.second) {
        wiem = TAK;
        x = zakr.second;
    }
}
