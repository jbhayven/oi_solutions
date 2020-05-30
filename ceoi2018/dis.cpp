#include "dislib.h"

int main() {
    long long q1 = query(-1e5, -1e5);
    long long q2 = query(1e5, -1e5);

    long long _4e5x = q1 - q2;
    long long x = _4e5x / 4e5;
    
    long long y_1e5_2 = q1 - (x + 1e5) * (x + 1e5); 
    
    for(int i = 0; i <= 200000; i++)
        if((long long) i * i == y_1e5_2)
            give_answer(x, i - 1e5);
            
    return 0;
}
