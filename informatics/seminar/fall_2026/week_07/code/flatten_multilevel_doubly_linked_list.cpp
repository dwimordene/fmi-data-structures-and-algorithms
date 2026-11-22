struct Node {
    int data;

    Node* prev;

    Node* next;

    Node* child;

    Node(int data, Node* prev = nullptr, Node* next = nullptr, Node* child = nullptr)
        : data(data), prev(prev), next(next), child(child) {
    }
};

class Solution {
public:
    Node* flatten(Node* head) {
        if (!head) {
            return nullptr;
        }

        Node* it = head;

        while (it) {
            if (it->child) {
                Node* childTail = it->child;
                Node* next = it->next;

                while (childTail->next) {
                    childTail = childTail->next;
                }

                it->child->prev = it;
                it->next = it->child;

                it->child = nullptr;

                childTail->next = next;

                if (next) {
                    next->prev = childTail;
                }
            }

            it = it->next;
        }

        return head;
    }
};