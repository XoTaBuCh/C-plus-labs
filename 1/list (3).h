#include <iostream>
#include <string>
#include <iterator>

using namespace std;

template<typename T>
class List {
private:
    struct Node {
        Node* pNext;
        Node* pPrev;
        T data;
        Node(T data = T(), Node* pNext = NULL, Node* pPrev = NULL) { // REVIEW nullptr âìåñòî NULL
            this->pNext = pNext;
            this->pPrev = pPrev;
            this->data = data;
        }
    };
    int size;
    Node* head;
    Node* tail;
public:
    class Iterator : iterator<bidirectional_iterator_tag, T>
    {
    public:
        Iterator(Node* ptr = NULL) {
            this->ptr = ptr;
        }
        Iterator(const Iterator& it) {
            this->ptr = it.ptr;
        }
        Iterator& operator=(const Iterator& it)
        {
            this->ptr = it.ptr;
            return *this;
        }
        bool operator == (const Iterator& it)
        {
            return (ptr == it.ptr);
        }
        bool operator!=(const Iterator& it)
        {
            return !(ptr == it.ptr);
        }
        Iterator& operator++()
        {
            if (ptr == NULL || ptr->pNext == NULL) {
                throw "incremented an empty iterator";
            }
            ptr = ptr->pNext;
            return *this;
        }
        Iterator& operator++(T) const
        {
            auto ans = this;
            if (ptr == NULL || ptr->pNext == NULL) {
                throw "incremented an empty iterator";
            }
            ptr = ptr->pNext;
            return *ans;
        }
        Iterator& operator--()
        {
            if (ptr == NULL || ptr->pPrev == NULL) {
                throw "decremented an empty iterator";
            }
            ptr = ptr->pPrev;
            return *this;
        }
        Iterator& operator--(T) const
        {
            auto ans = this;
            if (ptr == NULL || ptr->pPrev == NULL) {
                throw "decremented an empty iterator";
            }
            ptr = ptr->pPrev;
            return *ans;
        }
        T& operator*()
        {
            return ptr->data;
        }
        T operator*() const
        {
            return ptr->data;
        }
        bool operator>(const Iterator& it) const
        {
            return ptr->data > it.ptr->data;
        }
        bool operator<(const Iterator& it) const
        {
            return ptr->data < it.ptr->data;
        }
        bool operator<=(const Iterator& it) const
        {
            return ptr->data <= it.ptr->data;
        }
        bool operator>=(const Iterator& it) const
        {
            return ptr->data >= it.ptr->data;
        }
    private:
        Node* ptr;
    };
    List(const initializer_list<T>& list) : List<T>() {
        for (T value : list) {
            Push_back(value);
        }
    }
    List() {
        size = 0;
        head = NULL;
        tail = NULL;
    }
    List(const List& old_list) {
        if (old_list.head != NULL) {
            Node* current = old_list.head;
            while (current != old_list.tail) {
                this->Push_back(current->data);
                current = current->pNext;
            }
        }
        else {
            head = NULL;
            tail = NULL;
        }
    }
    ~List() {
        while (head != tail) {
            Node* first = head->pNext;
            delete head;
            head = first;
        }
    }
    void Push_back(T data) {
        if (head == NULL) {
            head = new Node(data);
            tail = new Node(NULL, NULL, head);
            head->pNext = tail;
        }
        else {
            Node* last = new Node(NULL, NULL, tail);
            tail->pNext = last;
            tail->data = data;
            tail = last;
        }
        size++;
    }
    void Push_front(T data) {
        if (head == NULL) {
            head = new Node(data);
            tail = new Node(NULL, NULL, head);
            head->pNext = tail;
        }
        else {
            Node* first = new Node(data, head, NULL);
            head->pPrev = first;
            head = first;
        }
        size++;
    }
    void Pop_back() {
        if (size == 1) {
            delete head;
            delete tail;
            head == NULL;
            tail == NULL;
            size--;
        }
        else if (size) {
            Node* last = tail->pPrev;
            delete tail;
            tail = last;
            size--;
        }
    }
    void Pop_front() {
        if (size == 1) {
            delete head;
            delete tail;
            head == NULL;
            tail == NULL;
            size--;
        }
        else if (size) {
            Node* first = head->pNext;
            delete head;
            head = first;
            size--;
        }
    }
    bool Empty() {
        return size == 0;
    }
    size_t Size() {
        return size;
    }
    /*ostream& operator<<(ostream& os, const List& list) {
        os << "{";
        for (auto item : list) os << item << ", ";
        os << "}";
        return os;
    }*/
    string Output() {
        string str = "";
        Node* current = head;
        while (current != tail) {
            str += to_string(current->data) + " ";
            current = current->pNext;
        }
        return str;
    }
    List& operator = (const List& old_list)
    {
        this->size = old_list.size;
        if (old_list.head != NULL) {
            Node* current = old_list.head;
            while (current != old_list.tail) {
                this->Push_back(current->data);
                current = current->pNext;
            }
        }
    }
    Iterator begin() {
        return Iterator(head);
    }
    Iterator end() {
        return Iterator(tail);
    }
};

/* REVIEW
 * leak'è îñòàþòñÿ, áîíóñà íåò çà ýòî
 * åñòü (áóäóò) áîíóñ çà øàáëîíû
 * ëîìàåòñÿ êîïèðîâàíèå
 List<int> arr = {1, 2, 3};
 List<int> arr2 = arr;
 * êîãäà ïî÷èíèøü, òî äîëæíî áûòü òàê
 *(++arr2.begin()) = 0;
 for (int item : arr) std::cerr << item << ' '; // 1 2 3
 for (int item : arr2) std::cerr << item << ' '; // 1 0 3
 * + äîëæåí ðàáîòàòü ñëåäóþùèé êîä:
 void print(List<int> list) {
    for (int item : list) std::cerr << item << ' ';
    std::cerr << '\n';
 }
 * 3 == *(--arr.end()) îíî ðàáîòàåò íî ïóñòü íå ïîëîìàåòñÿ))0)
 * 1 == *arr.begin() îíî ðàáîòàåò íî ïóñòü íå ïîëîìàåòñÿ))0)
 * íàäî ÷óòü äîðàáîòàòü ÷òîá ÿ ìîã õîòÿ áû ïîòåñòèòü
 * ïî÷òè çà÷òåíî
 */


