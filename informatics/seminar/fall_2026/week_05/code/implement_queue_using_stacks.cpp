#include <stack>

class MyQueue {
public:
    MyQueue() = default;

    bool isEmpty() { return s1.empty() && s2.empty(); }

    int peek() {
        if (isEmpty()) {
            return -1;
        }

        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());

                s1.pop();
            }
        }

        return s2.top();
    }

    int pop() {
        if (isEmpty()) {
            return -1;
        }

        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());

                s1.pop();
            }
        }

        int value = s2.top();
        s2.pop();

        return value;
    }

    void push(int value) { s1.push(value); }

private:
    std::stack<int> s1, s2;
};