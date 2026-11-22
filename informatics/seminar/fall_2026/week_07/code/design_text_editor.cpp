#include <string>

using namespace std;

class TextEditor {
    struct Node {
        char data;

        Node* prev;

        Node* next;

        Node(char data, Node* prev = nullptr, Node* next = nullptr)
            : data(data), prev(prev), next(next) {
        }
    };

public:
    TextEditor()
        : sentinel({ '0', &sentinel, &sentinel }), cursor(&sentinel) {
    }

    ~TextEditor() {
        while (&sentinel != sentinel.next) {
            Node* toDel = sentinel.next;
            sentinel.next = toDel->next;

            delete toDel;
        }
    }

    int deleteText(int k) {
        int count = 0;

        while (&sentinel != cursor && count < k) {
            Node* toDel = cursor;
            cursor = toDel->prev;
            toDel->next->prev = toDel->prev;
            toDel->prev->next = toDel->next;

            delete toDel;

            ++count;
        }

        return count;
    }

    string cursorLeft(int k) {
        while (&sentinel != cursor && k > 0) {
            cursor = cursor->prev;

            --k;
        }

        return getLeftChars();
    }

    string cursorRight(int k) {
        while (&sentinel != cursor->next && k > 0) {
            cursor = cursor->next;

            --k;
        }

        return getLeftChars();
    }

    void addText(const string& text) {
        for (char ch : text) {
            Node* next = cursor->next;
            cursor->next = new Node(ch, cursor, next);
            next->prev = cursor->next;

            cursor = cursor->next;
        }
    }

private:
    string getLeftChars() {
        const Node* it = cursor;
        int count = 0;
        string result = "";

        while (&sentinel != it && count < 10) {
            result += it->data;

            it = it->prev;

            ++count;
        }

        std::reverse(result.begin(), result.end());

        return result;
    }

    Node sentinel;
    Node* cursor;
};