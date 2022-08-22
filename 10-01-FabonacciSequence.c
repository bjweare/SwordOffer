#include <stdio.h>

int fab(int n) {
    if (n < 0) {
        return -1;
    }

    if (0 == n || 1 == n) {
        return n;
    }

    int prev = 0, curr = 1, sum = 0;
    for (int i = 0; i < (n - 1); i++) {
        sum = (prev + curr) % 1000000007;
        prev = curr;
        curr = sum;
    }

    return sum;
}

int main(void) {
    fprintf(stdout, "fab(0): %d\n", fab(0));
    fprintf(stdout, "fab(1): %d\n", fab(1));
    fprintf(stdout, "fab(2): %d\n", fab(2));
    fprintf(stdout, "fab(3): %d\n", fab(3));
    fprintf(stdout, "fab(4): %d\n", fab(4));
    fprintf(stdout, "fab(5): %d\n", fab(5));
    fprintf(stdout, "fab(6): %d\n", fab(6));
    fprintf(stdout, "fab(7): %d\n", fab(7));
}
