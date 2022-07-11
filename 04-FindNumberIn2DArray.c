#include <stdio.h>
#include <stdbool.h>

/*
   剑指 Offer 04. 二维数组中的查找
   https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/
 */

bool findNumberIn2DArray(int **matrix, int matrixSize, int *matrixColSize, int target) {
    if (!matrixColSize) {
        return false;
    }
    /* 遍历所有的一维数组, 在一维数组中使用二分查找法查找target值 */
    for (int i = 0; i < matrixSize; i++) {
        int *array = matrix[i];
        int arraySize = matrixColSize[i];
        if (!array || arraySize == 0) {
            return false;
        }

        if (target < array[0]) {
            return false;
        }

        int left = 0, right = arraySize-1;
        while (left <= right) {
            int mid = left + ((right - left) / 2);
            if (array[mid] == target) {
                return true;
            } else if (array[mid] < target) {
                left = mid + 1;
            } else if (array[mid] > target) {
                right = mid - 1;
            }
        }
    }
    return false;
}

int main(void)
{
    int array1[5] = {1,4,7,11,15};
    int array2[5] = {2,5,8,12,19};
    int array3[5] = {3,6,9,16,22};
    int array4[5] = {10,13,14,17,24};
    int array5[5] = {18,21,23,26,30};
    int *twoDimensionArray[] = {
        array1,
        array2,
        array3,
        array4,
        array5
    };
    int matrixSize = sizeof(twoDimensionArray) / sizeof(twoDimensionArray[0]);
    int matrixColSize[] = {
        sizeof(array1) / sizeof(int),
        sizeof(array2) / sizeof(int),
        sizeof(array3) / sizeof(int),
        sizeof(array4) / sizeof(int),
        sizeof(array5) / sizeof(int)
    };

    int target = 5;
    bool bFound = findNumberIn2DArray(twoDimensionArray, matrixSize, matrixColSize, target);
    printf("target[%d] is exists in 2D array: %d\n", target, bFound);
}
