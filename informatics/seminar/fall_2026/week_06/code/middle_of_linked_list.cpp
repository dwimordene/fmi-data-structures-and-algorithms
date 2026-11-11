class Solution {
    struct ListNode {
        int val;

        ListNode* next;

        ListNode(int data, ListNode* next = nullptr)
            : val(data), next(next) {
        }
    };

public:
    ListNode* middleNode(ListNode* head) {
        if (!head) {
            return nullptr;
        }

        ListNode* fast = head;
        ListNode* slow = head;

        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }

        return slow;
    }
};