#include <string>

using namespace std;

class BrowserHistory {
    struct Node {
        string url;

        Node* prev;

        Node* next;

        Node(const string& url, Node* prev = nullptr, Node* next = nullptr)
            : url(url), prev(prev), next(next) {
        }
    };

public:
    BrowserHistory(const string& homepage)
        : sentinel({ "", &sentinel, &sentinel }), current(&sentinel) {
        Node* newNode = new Node(homepage, &sentinel, &sentinel);
        sentinel.next = newNode;
        sentinel.prev = newNode;

        current = newNode;
    }

    ~BrowserHistory() {
        while (&sentinel != sentinel.next) {
            Node* toDel = sentinel.next;
            sentinel.next = toDel->next;

            delete toDel;
        }
    }

    string back(int steps) {
        while (&sentinel != current->prev && steps > 0) {
            current = current->prev;

            --steps;
        }

        return current->url;
    }

    string forward(int steps) {
        while (&sentinel != current->next && steps > 0) {
            current = current->next;

            --steps;
        }

        return current->url;
    }

    void visit(const string& url) {
        while (&sentinel != current->next) {
            Node* toDel = current->next;
            current->next = toDel->next;
            toDel->next->prev = current;

            delete toDel;
        }

        current->next = new Node(url, current, current->next);
        sentinel.prev = current->next;

        current = current->next;
    }

private:
    Node sentinel;
    Node* current;
};