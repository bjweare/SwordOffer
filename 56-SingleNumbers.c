#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   剑指 Offer 56 - I. 数组中数字出现的次数
   https://leetcode.cn/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/
 */
int *singleNumbers(int *nums, int numsSize, int *returnSize) {
    *returnSize = 0;
    if (!nums || numsSize == 0) {
        return NULL;
    }

    int xor = 0;
    for (int i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }

    uint32_t bitMask = 0;
    for (int i = 0; i < 32; i++) {
        bitMask = 1 << i;
        if (bitMask & xor) {
            break;
        }
    }

    if (0 == (bitMask & xor)) {
        return NULL;
    }

    int *newArray = malloc(numsSize * sizeof(int));
    if (!newArray) {
        return NULL;
    }
    memset(newArray, 0x00, numsSize * sizeof(int));

    int size1 = 0, size2 = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] & bitMask) {
            newArray[size1] = nums[i];
            size1++;
        } else {
            newArray[numsSize-1-size2] = nums[i];
            size2++;
        }
    }

    int *newNums = malloc(2 * sizeof(int));
    if (!newNums) {
        return NULL;
    }
    memset(newNums, 0x00, 2*sizeof(int));
    for (int i = 0; i < size1; i++) {
        newNums[0] ^= newArray[i];
    }

    for (int i = size1; i < numsSize; i++) {
        newNums[1] ^= newArray[i];
    }

    free(newArray);
    newArray = NULL;

    *returnSize = 2;
    return newNums;
}

int main(void) {
    int array[] = {6, 4, 1, 4};

    int newNumsSize = 0;
    int *newNums = singleNumbers(array, sizeof(array) / sizeof(int), &newNumsSize);
    printf("newNumsSize: %d\n", newNumsSize);
    for (int i = 0; i < newNumsSize; i++) {
        printf("%d", newNums[i]);
        if (i == (newNumsSize-1)) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
}
