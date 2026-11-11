struct ListNode {
    int val;

    ListNode* next;

    ListNode(int data, ListNode* next = nullptr)
        : val(data), next(next) {
    }
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) {
            return true;
        }

        ListNode* prev = beforeMiddle(head);

        ListNode* other = prev->next;
        prev->next = nullptr;

        other = reverseList(other);

        while (head && other) {
            if (head->val != other->val) {
                return false;
            }

            head = head->next;
            other = other->next;
        }

        return true;
    }

private:
    ListNode* beforeMiddle(ListNode* head) {
        if (!head) {
            return nullptr;
        }

        ListNode* fast = head->next;
        ListNode* slow = head;

        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }

        return slow;
    }

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