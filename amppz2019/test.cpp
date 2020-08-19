#include <bits/stdc++.h>
using namespace std;

bool prime(long long a) {
    for (long long i = 2; i * i <= a; i++)
        if (a % i == 0) return false;
    return true;
}

int main() {
    long long a = 1e18 - 5;
    
    while (! prime(a)) a-=2;
    cout <<a  << endl;
    return 0;
}
