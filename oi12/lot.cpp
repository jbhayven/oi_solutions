#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 10;

int n; 

bool is_ok[MAX_N];
int petrol[MAX_N];
int dist[MAX_N];

int64_t first[MAX_N];
int second[MAX_N];

int fr = 0;
int b = 0;

inline void emplace_back(int64_t f, int s) {
    first[b] = f;
    second[b] = s;
    b = (b + 1) % MAX_N;
}

inline void pop_front() {
    fr = (fr + 1) % MAX_N;
}

inline void pop_back() {
    b = (b + MAX_N - 1) % MAX_N;
}

void licz() {
    int j = 0;
    long long sum = 0;
    long long i_sum = 0;
    
    for (int i = 0; i < n; i++) {
        for (; j < i + n; j++) {
            sum += petrol[j % n] - dist[j % n];
            
            while (fr != b && first[b - 1] >= sum)
                pop_back();
                
            emplace_back(sum, j);
        }
        
        if (fr != b && second[fr] < i)
            pop_front();
        
        if (first[fr] >= i_sum)
            is_ok[i] = true;
            
        i_sum += petrol[i] - dist[i];
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++)
        scanf("%d %d", &petrol[i], &dist[i]);
    
    licz();
    
    fr = b = 0;
    
    for (int i = n; i > 0; i--)
        dist[i] = dist[i - 1];
    dist[0] = dist[n];
    
    for (int i = 0; i < n / 2; i++) {
        swap(dist[i], dist[n - 1 - i]);
        swap(petrol[i], petrol[n - 1 - i]);
        swap(is_ok[i], is_ok[n - 1 - i]);
    }
    
    licz();
    
    for (int i = n - 1; i >= 0; i--)
        printf("%s\n", is_ok[i] ? "TAK" : "NIE");
    
    return 0;
}
