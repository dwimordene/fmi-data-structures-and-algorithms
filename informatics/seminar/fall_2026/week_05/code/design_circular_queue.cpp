class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        capacity = k + 1;
        data = new int[capacity];
        front = rear = 0;
    }

    ~MyCircularQueue() {
        delete[] data;
    }

    bool dequeue() {
        if (isEmpty()) {
            return false;
        }

        front = (front + 1) % capacity;

        return true;
    }

    bool enqueue(int value) {
        if (isFull()) {
            return false;
        }

        data[rear] = std::move(value);
        rear = (rear + 1) % capacity;

        return true;
    }

    bool isEmpty() const { return front == rear; }

    bool isFull() const { return (rear + 1) % capacity == front; }

    int getFront() const {
        if (isEmpty()) {
            return -1;
        }

        return data[front];
    }

    int getRear() const {
        if (isEmpty()) {
            return -1;
        }

        int pos = (capacity + rear - 1) % capacity;

        return data[pos];
    }

private:
    int* data;

    int capacity, front, rear;
};