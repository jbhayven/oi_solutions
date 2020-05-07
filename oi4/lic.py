#!/usr/bin/env python3

def main():
    n, k = (int(num) for num in input().split())

    result = [[0 for j in range(k + 1)] for i in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(k + 1):
            result[i][j] = result[i-1][j]
            if i > 2:
                result[i][j] += result[i-2][max(j - i, 0)];
            if j < i:
                result[i][j] += 1
        
    print(result[i][j])

if __name__ == "__main__":
    main()
