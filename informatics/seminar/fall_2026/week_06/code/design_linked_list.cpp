struct ListNode {
    int val;

    ListNode* next;

    ListNode(int data, ListNode* next = nullptr)
        : val(data), next(next) {
    }
};

class MyLinkedList {
public:
    MyLinkedList()
        : head(nullptr), tail(nullptr), size(0) {
    }

    ~MyLinkedList() {
        while (head) {
            ListNode* toDel = head;
            head = head->next;

            delete toDel;
        }
    }

    int get(int index) {
        if (index < 0 || index >= size) {
            return -1;
        }

        if (index == 0) {
            return head->val;
        }
        else if (index == size - 1) {
            return tail->val;
        }
        else {
            const ListNode* it = head;

            for (int i = 0; i < index; ++i) {
                it = it->next;
            }

            return it->val;
        }
    }

    void addAtIndex(int index, int val) {
        if (index < 0) {
            index = 0;
        }

        if (index > size) {
            return;
        }

        if (index == 0) {
            head = new ListNode(val, head);

            if (size == 0) {
                tail = head;
            }
        }
        else if (index == size) {
            tail->next = new ListNode(val);

            tail = tail->next;
        }
        else {
            ListNode* it = head;

            for (int i = 0; i < index - 1; ++i) {
                it = it->next;
            }

            it->next = new ListNode(val, it->next);
        }

        ++size;
    }

    void addHead(int val) {
        addAtIndex(0, val);
    }

    void addTail(int val) {
        addAtIndex(size, val);
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }

        ListNode* toDel = head;

        if (index == 0) {
            head = head->next;

            if (!head) {
                tail = nullptr;
            }
        }
        else {
            ListNode* it = head;

            for (int i = 0; i < index - 1; ++i) {
                it = it->next;
            }

            toDel = it->next;

            it->next = toDel->next;

            if (tail == toDel) {
                tail = it;
            }
        }

        --size;
    }

private:
    ListNode* head;
    ListNode* tail;
    int size;
};