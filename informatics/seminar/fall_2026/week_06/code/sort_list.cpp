class Solution {
    struct ListNode {
        int val;

        ListNode* next;

        ListNode(int data, ListNode* next = nullptr)
            : val(data), next(next) {
        }
    };

public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode* splitPoint = beforeMiddle(head);

        ListNode* left = head;
        ListNode* right = splitPoint->next;
        splitPoint->next = nullptr;

        return mergeTwoLists(sortList(left), sortList(right));
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

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* it = &dummy;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                it->next = list1;
                list1 = list1->next;
            }
            else {
                it->next = list2;
                list2 = list2->next;
            }

            it = it->next;
        }

        it->next = list1 ? list1 : list2;

        return dummy.next;
    }
};