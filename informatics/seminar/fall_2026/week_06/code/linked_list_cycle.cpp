class Solution {
    struct ListNode {
        int val;

        ListNode* next;

        ListNode(int data, ListNode* next = nullptr)
            : val(data), next(next) {
        }
    };

public:
    bool hasCycle(ListNode* head) {
        if (!head) {
            return false;
        }

        ListNode* fast = head;
        ListNode* slow = head;

        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow) {
                return true;
            }
        }

        return false;
    }
};