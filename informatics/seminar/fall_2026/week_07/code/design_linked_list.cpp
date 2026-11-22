class MyLinkedList {
    struct Node {
        int data;

        Node* prev;

        Node* next;

        Node(int data, Node* prev = nullptr, Node* next = nullptr)
            : data(data), prev(prev), next(next) {
        }
    };

public:
    MyLinkedList()
        : sentinel({ 0, &sentinel, &sentinel }), size(0) {
    }

    ~MyLinkedList() {
        while (&sentinel != sentinel.next) {
            Node* toDel = sentinel.next;
            sentinel.next = toDel->next;

            delete toDel;
        }
    }

    int get(int index) {
        Node* node = getNodeAt(index);

        return node ? node->data : -1;
    }

    void addAtIndex(int index, int val) {
        if (index < 0) {
            index = 0;
        }

        if (index > size) {
            return;
        }

        if (index == 0) {
            addHead(val);
        }
        else if (index == size) {
            addTail(val);
        }
        else {
            Node* node = getNodeAt(index);
            Node* prev = node->prev;
            prev->next = new Node(val, prev, node);

            node->prev = prev->next;

            ++size;
        }
    }

    void addHead(int val) {
        Node* next = sentinel.next;
        sentinel.next = new Node(val, &sentinel, next);

        next->prev = sentinel.next;

        ++size;
    }

    void addTail(int val) {
        Node* prev = sentinel.prev;
        sentinel.prev = new Node(val, prev, &sentinel);

        prev->next = sentinel.prev;

        ++size;
    }

    void deleteAtIndex(int index) {
        Node* toDel = getNodeAt(index);

        if (!toDel) {
            return;
        }

        toDel->next->prev = toDel->prev;
        toDel->prev->next = toDel->next;

        delete toDel;

        --size;
    }

private:
    Node* getNodeAt(int index) {
        if (index < 0 || index >= size) {
            return nullptr;
        }

        Node* it = &sentinel;

        if (index < size / 2) {
            for (int i = 0; i <= index; ++i) {
                it = it->next;
            }
        }
        else {
            for (int i = size - 1; i >= index; --i) {
                it = it->prev;
            }
        }

        return it;
    }

    Node sentinel;
    int size;
};