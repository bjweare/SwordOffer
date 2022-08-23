#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(int a, int b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    }
    return 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quickSort(int *nums, int numsSize) {
    if (NULL == nums || numsSize < 2) {
        return;
    }

    int left = 0, right = numsSize-1;
    while (left < right) {
        while (left < right && compare(nums[left], nums[right]) < 0) {
            right--;
        }
        if (left >= right) {
            break;
        }
        swap(&nums[left], &nums[right]);
        left++;

        while (left < right && compare(nums[right], nums[left]) > 0) {
            left++;
        }
        if (left >= right) {
            break;
        }
        swap(&nums[right], &nums[left]);
        right--;
    }
    quickSort(&nums[0], left);
    quickSort(&nums[left+1], numsSize-left-1);
}

int majorityElement(int *nums, int numsSize) {
    quickSort(nums, numsSize);
    return nums[numsSize/2];
}

int main(void) {
    int nums[100] = {0};
    srand(time(NULL));
    int targetMajorityElement = rand() % 20;
    for (int i = 0; i < sizeof(nums)/sizeof(int); i++) {
        if (0 == (i % 2) || 1 == i) {
            nums[i] = targetMajorityElement;
            continue;
        }
        nums[i] = rand() % 100;
    }
    int foundMajorityElement = majorityElement(nums, sizeof(nums)/sizeof(int));
    fprintf(stdout, "targetMajorityElement: %d, foundMajorityElement: %d\n",
            targetMajorityElement, foundMajorityElement);
    return 0;
}
