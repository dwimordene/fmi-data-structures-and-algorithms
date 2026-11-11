struct ListNode {
    int val;

    ListNode* next;

    ListNode(int data, ListNode* next = nullptr)
        : val(data), next(next) {
    }
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) {
            return nullptr;
        }

        ListNode* prev = nullptr;

        while (head) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;

            head = next;
        }

        return prev;
    }
};