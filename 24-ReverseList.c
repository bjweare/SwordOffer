#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   剑指 Offer 24. 反转链表
https://leetcode.cn/problems/fan-zhuan-lian-biao-lcof/
*/

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head) {
    if (!head) {
        return NULL;
    }

    struct ListNode *prev = NULL, *cur = head;
    while (NULL != cur) {
        struct ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
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
    struct ListNode *head = createLinkedList(8);

    struct ListNode *rHead = reverseList(head);
    struct ListNode *current = rHead;
    while (current) {
        printf("%d", current->val);
        if (NULL != current->next) {
            printf(" ");
        } else {
            printf("\n");
        }
        current = current->next;
    }
}
