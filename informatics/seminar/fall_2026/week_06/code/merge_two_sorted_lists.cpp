struct ListNode {
    int val;

    ListNode* next;

    ListNode(int data, ListNode* next = nullptr)
        : val(data), next(next) {
    }
};

class Solution {
public:
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