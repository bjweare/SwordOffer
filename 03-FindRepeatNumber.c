#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   剑指 Offer 03. 数组中重复的数字
   https://leetcode.cn/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/
 */

int findRepeatNumber(int *nums, int numsSize) {
    if (!nums || numsSize < 2) {
        return -1;
    }

    size_t bitMapSize = (numsSize + 7) / 8;
    uint8_t *bitMap = malloc(bitMapSize);
    if (!bitMap) {
        return -1;
    }
    memset(bitMap, 0x00, bitMapSize);

    int byteOffset = 0, bitOffset = 0;
    uint8_t bitMask = 0;
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        byteOffset = num / 8;
        bitOffset = num % 8;
        bitMask = (1 << bitOffset);
        //printf("byteOffset: %d, bitOffset: %d, bitMask: %#02x\n", byteOffset, bitOffset, bitMask);

        if (bitMap[byteOffset] & bitMask) {
            return num;
        } else {
            bitMap[byteOffset] |= bitMask;
        }
    }
    return -1;
}

int main(void) {
    int nums[] = {2, 3, 1, 0, 2, 5, 3};
    int repeatNum = findRepeatNumber(nums, sizeof(nums) / sizeof(int));
    printf("repeatNum: %d\n", repeatNum);
}
