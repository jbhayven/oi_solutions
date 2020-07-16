#include "csonlib.h"
#include <bits/stdc++.h>
using namespace std;

#define MAX_K 505
#define MAX_Q 505

long long ile_mozna[MAX_K][MAX_Q];

int main(){
    long long n = dajDlugosc();
    int k = dajLiczbeSond();
    int q = dajLimitCzasowy();
    
    for (int j = 0; j <= q; j++)
        ile_mozna[0][j] = 1;
        
    for (int i = 1; i <= k; i++) {
        ile_mozna[i][0] = 1;
        for(int j = 1; j <= q; j++) 
            ile_mozna[i][j] = min(ile_mozna[i-1][j-1] + ile_mozna[i][j-1], n);
    }
        
    long long left = 0;
    while (n > 1) {
        long long pos = min(ile_mozna[k-1][q-1], n);
        if (sprawdz(left + pos)) {
            n = pos;
            k--;
        }
        else {
            left += pos;
            n -= pos;
        }
        q--;
    }
    
    odpowiedz(left + 1);
        
    return 0;
}
