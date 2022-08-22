#include <stdio.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


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

int main(void)
{
    return 0;
}
