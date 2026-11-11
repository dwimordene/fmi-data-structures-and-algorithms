struct ListNode {
    int val;

    ListNode* next;

    ListNode(int data, ListNode* next = nullptr)
        : val(data), next(next) {
    }
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head) {
            return nullptr;
        }

        ListNode dummy(0, head);
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        for (int i = 0; fast && i <= n; ++i) {
            fast = fast->next;
        }

        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        ListNode* toDel = slow->next;
        slow->next = toDel->next;

        delete toDel;

        return dummy.next;
    }
};