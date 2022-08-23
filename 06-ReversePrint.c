#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   剑指 Offer 06. 从尾到头打印链表
https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/
*/

struct ListNode {
    int val;
    struct ListNode *next;
};

int *reversePrint(struct ListNode *head, int *returnSize) {
    *returnSize = 0;

    if (!head) {
        return NULL;
    }

    struct ListNode *p = head;
    int listSize = 0;
    while (NULL != p) {
        listSize++;
        p = p->next;
    }

    int *newArray = (int *)malloc(listSize * sizeof(int));
    if (!newArray) {
        return NULL;
    }
    memset(newArray, 0x00, listSize*sizeof(int));

    int idx = listSize;
    p = head;
    while (NULL != p) {
        newArray[--idx] = p->val;
        p = p->next;
    }
    *returnSize = listSize;

    return newArray;
}

struct ListNode *createLinkedList(int size) {
    struct ListNode *head = NULL, *last = NULL;
    for (int i = 0; i < size; i++) {
        struct ListNode *current = (struct ListNode *)malloc(sizeof(struct ListNode));

        memset(current, 0x00, sizeof(struct ListNode));
        current->val = i;
        current->next = NULL;

        if (NULL == head) {
            head = current;
        }
        if (NULL != last) {
            last->next = current;
        }
        last = current;
    }
    return head;
}

int main(void) {
    int arraySize = 0;

    struct ListNode *head = createLinkedList(8);

    int *array = reversePrint(head, &arraySize);
    printf("arraySize: %d\n", arraySize);
    for (int i = 0; i < arraySize; i++) {
        printf("%d", array[i]);
        if (i != (arraySize-1)) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
}
