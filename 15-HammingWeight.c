#include <stdio.h>
#include <stdint.h>

int hammingWeight(uint32_t n) {
    int bitCnt = 0;

    for (int i = 0; i < 32; i++) {
        if (n & 0x00000001) {
            bitCnt++;
        }
        n = n >> 1;
    }

    return bitCnt;
}

int main(void) {
    fprintf(stdout, "hammingWeight(0xf): %d\n", hammingWeight(0xf));
    fprintf(stdout, "hammingWeight(0xff): %d\n", hammingWeight(0xff));
    fprintf(stdout, "hammingWeight(0xfff): %d\n", hammingWeight(0xfff));
    fprintf(stdout, "hammingWeight(0xffff): %d\n", hammingWeight(0xffff));
    return 0;
}
