class Solution {
    struct ListNode {
        int val;

        ListNode* next;

        ListNode(int data, ListNode* next = nullptr)
            : val(data), next(next) {
        }
    };

public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || left == right) {
            return head;
        }

        ListNode dummy(0, head);
        ListNode* before = &dummy;

        for (int i = 0; i < left - 1; ++i) {
            before = before->next;
        }

        ListNode* begin = before->next;
        ListNode* it = begin;

        for (int i = 0; i < right - left; ++i) {
            it = it->next;
        }

        ListNode* after = it->next;
        it->next = nullptr;

        before->next = reverseList(begin);
        begin->next = after;

        return dummy.next;
    }

private:
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