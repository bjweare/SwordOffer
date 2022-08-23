#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* deleteNode(struct ListNode* head, int val){
    struct ListNode *curr = head;
    struct ListNode *last = NULL;
    while (curr) {
        if (curr->val == val) {
            if (NULL == last) {
                head = curr->next;
            } else {
                last->next = curr->next;
            }
            break;
        }
        last = curr;
        curr = curr->next;
    }
    return head;
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

int main(void)
{
    struct ListNode *head = createLinkedList(8);
    head = deleteNode(head, 2);
    head = deleteNode(head, 0);
    head = deleteNode(head, 3);
    head = deleteNode(head, 7);
    return 0;
}
