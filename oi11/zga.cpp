#include <bits/stdc++.h>
#include "zga.h"
using namespace std;

set< pair<double, int> > cands;
int game = 0;
int symbol[10][10];

/* Actually, this could probably be computed on runtime, 
 * but I tested each value by hand. 
 */
double win[] {
    1, 
    1, 
    0.750893, 
    0.518933, 
    0.343878, 
    0.221213, 
    0.140624, 
    0.087810, 
    0.054605, 
    0.033573,
};

void inicjalizuj() {
    double fact[10] = {1};
    for (int i = 1; i < 10; i++)
        fact[i] = fact[i-1] * i;
    
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            if (i > j) continue;
            symbol[i][j] = fact[j] / (fact[i] * fact[j-i]);
        }
}

void nowa_rozgrywka() {
    game++;
    cands = set<pair<double, int>>{{0.0, 0}, {1.0, ILE_LICZB + 1}};
}

int kolejna_liczba(double x) {
    auto nxt = cands.lower_bound({x, 0});
    auto prev = nxt; prev--;
    
    pair<double, int> max_prob = {0, 0};
    
    int cnt = nxt->second - prev->second - 2;
    if (cnt < 0) return 1;
    
    double len = nxt->first - prev->first;
    double left = (x - prev->first) / len;
    double right = (nxt->first - x) / len;
    
    double prob_left = 1;
    double prob_right = 1;
    for (int i = 0; i < cnt; i++)
        prob_right *= right;
        
    for (int i = 0; i <= cnt; i++) {
        max_prob = max(max_prob, 
                       { symbol[i][cnt] * prob_left * prob_right * win[i] * win[cnt - i], i });
        
        prob_left *= left;
        prob_right /= right;
    }
    
    int which = prev->second + 1 + max_prob.second;
    
    cands.insert({x, which});
    
    return which;
}
