struct ListNode {
    int val;

    ListNode* next;

    ListNode(int data, ListNode* next = nullptr)
        : val(data), next(next) {
    }
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (!head) {
            return nullptr;
        }

        ListNode dummy(0, head);
        ListNode* it = &dummy;

        while (it->next) {
            if (it->next->val == val) {
                ListNode* toDel = it->next;
                it->next = toDel->next;

                delete toDel;
            }
            else {
                it = it->next;
            }
        }

        return dummy.next;
    }
};