# Опашка

Опашката е линейна структура от данни, която обработва елементите си в реда на тяхното постъпване, следвайки принципа FIFO.

Ключови характеристики:

- Първият добавен елемент е първият премахнат.
- Новите елементи се добавят в края, а премахванията винаги стават от началото.

Често срещана аналогия са хората, чакащи на каса в магазин. Първият наредил се бива обслужен най-напред. Всеки новопристигнал заема мястото си зад останалите и изчаква своя ред.

## 1. Основни операции

| Операция | Времева сложност | Описание |
| --- | --- | --- |
| **Добавяне в края** | $\mathcal{O}(1)$ | Стойността се записва на позицията на `rear + 1` (с превъртане по модул при цикличен буфер) или се добавя като нов възел след `tail` (при свързан списък). Не се изисква изместване на съществуващите елементи. |
| **Премахване от началото** | $\mathcal{O}(1)$ | Извлича се стойността от позицията на `front` или `head`, след което указателят се измества напред. При свързан списък старият възел се деалокира. Времето е константно и независимо от броя елементи. |
| **Преглед на първия елемент** | $\mathcal{O}(1)$ | Връща се стойността на елемента в началото на опашката (сочен от `front` или `head`), без да се модифицира структурата или да се променят указателите. |
| **Проверка за празнота** | $\mathcal{O}(1)$ | Извършва се директно сравнение (напр. `size == 0` или `head == nullptr`), за да се установи дали опашката съдържа елементи. |

## 2. Възможни реализации

### 2.1. Чрез масив

При обикновения масив премахването на елемент от началото означава изместване на всичко останало с една позиция наляво. Това струва $\mathcal{O}(n)$ време, което може да бъде неефективно при голям набор от входни данни.

За да избегнем тази сложност, използваме цикличен буфер.

Идеята е да поддържаме два индекса, `front` и `rear`, които се движат напред с добавянето и премахването на елементи. Ако някой от тях достигне последната позиция на масива, го връщаме обратно в началото, за да не излезе извън рамките на буфера.

Пример за цикличен масив с капацитет 5:

| Индекс | 0 | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- | --- |
| **Стойност** | 60 | `NULL` | 30 | 40 | 50 |
| **Показалец** | `rear` | | `front` | | |

Тук `rear` се е преместил от индекс 4 обратно на 0, тъй като първите две позиции са били освободени от предходни изваждания. Опашката все още съдържа 30, 40, 50 и 60, въпреки че буферът изглежда като `[60, NULL, 30, 40, 50]` от ляво надясно.

Превъртането в кръг е причината цикличният масив да носи това име. Както `enqueue`, така и `dequeue` стават $\mathcal{O}(1)$, тъй като никога не изместваме елементи: мърдаме само двата индекса.

Аритметиката, която прави това възможно, е едно единствено модулно деление:

```cpp
front = (front + 1) % capacity;
rear = (rear + 1) % capacity;
```

Ето как можем да реализираме това в код:

```cpp
class ArrayQueue {
public:
    ArrayQueue(int capacity = 16)
        : data(nullptr),
        capacity(capacity),
        size(0),
        front(0),
        rear(-1) {
        if (capacity <= 0) {
            throw std::invalid_argument("Invalid capacity.");
        }

        data = new int[capacity];
    }

    ~ArrayQueue() noexcept {
        delete[] data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return capacity == size;
    }

    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty.");
        }

        int val = data[front];

        front = (front + 1) % capacity;

        --size;

        return val;
    }

    void enqueue(int val) {
        if (isFull()) {
            throw std::overflow_error("Queue is full.");
        }

        rear = (rear + 1) % capacity;

        data[rear] = val;

        ++size;
    }

private:
    int* data;

    int capacity, size;
    int front, rear;
};
```

- Използваме масив за съхранение на елементите, заедно с два показалеца (`front` и `rear`), които проследяват началото и края на опашката.
- Когато добавяме, преместваме `rear` напред, като го превъртаме циклично, ако е необходимо, и вкарваме новия елемент на тази позиция.
- Когато изваждаме, прочитаме елемента в началото, след което преместваме `front` напред, отново превъртайки го циклично.

Това движение ни гарантира повторно използване на позициите, освободени от операциите по премахване. Така предотвратяваме загубата на памет в началото на масива.

Чрез превъртане на двата показалеца поддържаме опашката максимално компактна и ефективна.

### 2.2. Чрез свързан списък

Друг популярен и ефективен начин за реализиране на опашка е чрез използване на свързан списък.

Свързаният списък нараства и намалява динамично, без да е необходимо изместване на елементи. Както добавянето, така и премахването се изпълняват за $\mathcal{O}(1)$ време без сложността на цикличната индексация.

Поддържаме два показалеца:

- **`head`:** Сочи към началото на опашката (използва се при премахване).
- **`tail`:** Сочи към края на опашката (използва се при добавяне).

```cpp
class ListQueue {
public:
    ListQueue()
        : head(nullptr), tail(nullptr) {
    }

    ~ListQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;

            delete temp;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty.");
        }

        int val = head->val;

        Node* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;

        return val;
    }

    void enqueue(int val) {
        Node* newNode = new Node(val);

        if (tail != nullptr) {
            tail->next = newNode;
        }

        tail = newNode;

        if (head == nullptr) {
            head = newNode;
        }
    }

private:
    struct Node {
        int val;

        Node* next;

        Node(int val, Node* next = nullptr)
            : val(val), next(next) {
        }
    };

    Node* head;
    Node* tail;
};
```

- При добавяне създаваме нов възел със съответната стойност. Ако `head` не е нулев указател, свързваме показалеца `next` на текущия край с новия елемент. След това обновяваме `tail`, за да сочи към новодобавения възел. Ако опашката е била празна, задаваме и `head = newNode`. Това гарантира, че първият елемент става едновременно начало и край.
- При изваждане, ако `head` е нулев указател, хвърляме изключение. Извличаме стойността от първия възел. Обновяваме главата, за да сочи към следващия нод, премахвайки първия елемент. Ако след това опашката стане празна, задаваме и `tail = nullptr`. Накрая връщаме извадената стойност.

## 3. Приоритетна опашка

Приоритетната опашка извлича първо елементите с най-голяма тежест. При равни стойности се запазва **FIFO** редът.

Когато броят на възможните приоритети $k \in [0, \text{maxPriority} - 1]$ е известен и малък, структурата може да се реализира чрез **масив от стандартни опашки** (*bucket queue*).

```cpp
class BucketQueue {
public:
    BucketQueue(int maxPriority = 4)
        : maxPriority(maxPriority), topPriority(-1) {
        if (maxPriority <= 0) {
            throw std::invalid_argument("Max priority must be greater than zero.");
        }

        buckets.resize(maxPriority);
    }

    bool isEmpty() const {
        return topPriority == -1;
    }

    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Priority queue is empty.");
        }

        int val = buckets[topPriority].front();

        buckets[topPriority].pop();

        // If the current top bucket is now empty,
        // find the next highest non-empty bucket
        if (buckets[topPriority].empty()) {
            while (topPriority >= 0 && buckets[topPriority].empty()) {
                --topPriority;
            }
        }

        return val;
    }

    void enqueue(int priority, int val) {
        if (priority < 0 || priority >= maxPriority) {
            throw std::out_of_range("Invalid priority level.");
        }

        buckets[priority].push(val);

        // Update the highest non-empty priority
        // if this one is higher
        if (priority > topPriority) {
            topPriority = priority;
        }
    }

private:
    int maxPriority;
    std::vector<std::queue<int>> buckets;

    // Tracks the index of the highest non-empty bucket
    int topPriority;
};
```

Времева сложност:

- **Добавяне:** Директен достъп до опашката с индекс равняващ се на приоритета - $\mathcal{O}(1)$.
- **Извличане:** Обхождане на масива от най-високия към най-ниския приоритет - $\mathcal{O}(k)$. Тъй като $k$ е константа, реалната сложност е $\mathcal{O}(1)$.

> **Бележка:** `std::priority_queue` е съвсем различна структура, която се базира на двоична пирамида и няма нищо общо с реализацията на *bucket queue*.