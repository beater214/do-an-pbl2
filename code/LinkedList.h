#include <iostream>

using namespace std;

// ================================================================
//  CLASS: Node<T>
// ================================================================
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& val) : data(val), next(nullptr) {}
    Node(const T& val, Node<T>* nxt) : data(val), next(nxt) {}
};

// ================================================================
//  CLASS: LinkedList<T> (Danh sach lien ket don - Template OOP)
// ================================================================
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    // ------------------------------------------------------------
    //  ITERATOR (Ho tro duyet bang for (auto it = ...) va range-based for)
    // ------------------------------------------------------------
    class Iterator {
    private:
        Node<T>* current;
    public:
        Iterator(Node<T>* node = nullptr) : current(node) {}

        T& operator*() { return current->data; }
        const T& operator*() const { return current->data; }
        T* operator->() { return &(current->data); }
        const T* operator->() const { return &(current->data); }

        Iterator& operator++() {
            if (current != nullptr) current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            if (current != nullptr) current = current->next;
            return temp;
        }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }

        Node<T>* getNode() const { return current; }
    };

    class ConstIterator {
    private:
        const Node<T>* current;
    public:
        ConstIterator(const Node<T>* node = nullptr) : current(node) {}

        const T& operator*() const { return current->data; }
        const T* operator->() const { return &(current->data); }

        ConstIterator& operator++() {
            if (current != nullptr) current = current->next;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            if (current != nullptr) current = current->next;
            return temp;
        }

        bool operator==(const ConstIterator& other) const { return current == other.current; }
        bool operator!=(const ConstIterator& other) const { return current != other.current; }

        const Node<T>* getNode() const { return current; }
    };

    // ------------------------------------------------------------
    //  CONSTRUCTOR & DESTRUCTOR
    // ------------------------------------------------------------
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    // Copy Constructor (Deep copy danh sach)
    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), count(0) {
        Node<T>* cur = other.head;
        while (cur != nullptr) {
            push_back(cur->data);
            cur = cur->next;
        }
    }

    // Move Constructor (C++11)
    LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }

    // Assignment Operator
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            clear();
            Node<T>* cur = other.head;
            while (cur != nullptr) {
                push_back(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    // Move Assignment (C++11)
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            count = other.count;
            other.head = nullptr;
            other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    ~LinkedList() {
        clear();
    }

    // ------------------------------------------------------------
    //  CAC PHUONG THUC CO BAN
    // ------------------------------------------------------------
    int size() const { return count; }
    int getKichThuoc() const { return count; }
    bool empty() const { return count == 0; }
    bool laRong() const { return count == 0; }

    Node<T>* getHead() const { return head; }
    Node<T>* getTail() const { return tail; }

    void push_back(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void themCuoi(const T& val) { push_back(val); }

    void push_front(const T& val) {
        Node<T>* newNode = new Node<T>(val, head);
        head = newNode;
        if (tail == nullptr) tail = head;
        count++;
    }

    void themDau(const T& val) { push_front(val); }

    void clear() {
        Node<T>* cur = head;
        while (cur != nullptr) {
            Node<T>* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }
        head = tail = nullptr;
        count = 0;
    }

    // Truy cap phan tu theo chi so (0-indexed)
    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw LoiVuotKhoang("Chi so vuot qua pham vi danh sach lien ket!");
        }
        Node<T>* cur = head;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->data;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= count) {
            throw LoiVuotKhoang("Chi so vuot qua pham vi danh sach lien ket!");
        }
        Node<T>* cur = head;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->data;
    }

    // Xoa phan tu tai vi tri iterator, tra ve iterator tiep theo
    Iterator erase(Iterator it) {
        Node<T>* target = it.getNode();
        if (target == nullptr || head == nullptr) return end();

        Node<T>* nextNode = target->next;

        if (target == head) {
            head = head->next;
            if (head == nullptr) tail = nullptr;
            delete target;
            count--;
            return Iterator(nextNode);
        }

        Node<T>* prev = head;
        while (prev != nullptr && prev->next != target) {
            prev = prev->next;
        }

        if (prev != nullptr) {
            prev->next = target->next;
            if (target == tail) tail = prev;
            delete target;
            count--;
            return Iterator(nextNode);
        }

        return end();
    }

    // ------------------------------------------------------------
    //  ITERATOR METHODS (Ho tro begin, end)
    // ------------------------------------------------------------
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end() const { return ConstIterator(nullptr); }

    ConstIterator cbegin() const { return ConstIterator(head); }
    ConstIterator cend() const { return ConstIterator(nullptr); }
};
