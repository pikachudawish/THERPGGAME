#include <stdio.h>
#include <stdlib.h>

int findnextprime(int table_size) {
    int curr_num = table_size + 1;

    while (1) {
        int x = curr_num;
        int isPrime = 1;

        if (x < 2) isPrime = 0;
        else if (x == 2) isPrime = 1;
        else if (x % 2 == 0) isPrime = 0;
        else {
            for (int i = 3; i * i <= x; i += 2) {
                if (x % i == 0) {
                    isPrime = 0;
                    break;
                }
            }
        }

        if (isPrime) return curr_num;

        curr_num++;
    }
}