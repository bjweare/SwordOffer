#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

int *reversePrint(struct ListNode *head, int *returnSize) {
    if (!head) {
        return NULL;
    }

    int size = 0;
    int *array = reversePrint(head->next, &size);

    int newSize = size + 1;
    int *newArray = (int *)malloc(newSize * sizeof(int));
    if (!newArray) {
        return NULL;
    }
    memset(newArray, 0x00, newSize*sizeof(int));

    newArray[size] = head->val;
    if (array) {
        memcpy(newArray, array, size*sizeof(int));
        free(array);
        array = NULL;
    }
    *returnSize = newSize;

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
