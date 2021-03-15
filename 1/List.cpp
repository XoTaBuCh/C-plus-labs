#include <iostream>
#include <string>
#include <iterator>

using namespace std;

template<typename T>
class List {
private:
    template<typename T>
    struct Node {
        Node* pNext;
        Node* pPrev;
        T data;
        Node(T data = T(), Node* pNext = NULL, Node* pPrev = NULL) {
            this->pNext = pNext;
            this->pPrev = pPrev;
            this->data = data;
        }
    };
    int size;
    Node<T>* head;
    Node<T>* tail;
public:
    template<typename T>
    class Iterator : iterator<bidirectional_iterator_tag, T>
    {
    public:
        Iterator<T>(Node<T>* ptr = NULL) {
            this->ptr = ptr;
        }
        Iterator<T>(const Iterator<T>& it) {
            this->ptr = it.ptr;
        }
        Iterator<T>& operator=(const Iterator<T>& it)
        {
            this->ptr = it.ptr;
            return *this;
        }
        bool operator == (const Iterator<T>& it)
        {
            return (ptr == it.ptr);
        }
        bool operator!=(const Iterator<T>& it)
        {
            return !(ptr == it.ptr);
        }
        Iterator<T>& operator++()
        {
            if (ptr == NULL || ptr->pNext == NULL) {
                throw "incremented an empty iterator";
            }
            ptr = ptr->pNext;
            return *this;
        }
        Iterator<T>& operator++(T)
        {
            if (ptr == NULL || ptr->pNext == NULL) {
                throw "incremented an empty iterator";
            }
            ptr = ptr->pNext;
            return *this;
        }
        Iterator<T>& operator--()
        {
            if (ptr == NULL || ptr->pPrev == NULL) {
                throw "decremented an empty iterator";
            }
            ptr = ptr->pPrev;
            return *this;
        }
        Iterator<T>& operator--(T)
        {
            if (ptr == NULL || ptr->pPrev == NULL) {
                throw "decremented an empty iterator";
            }
            ptr = ptr->pPrev;
            return *this;
        }
        T& operator*()
        {
            return ptr->data;
        }
        bool operator>(const Iterator<T>& it)
        {
            return ptr->data > it.ptr->data;
        }
        bool operator<(const Iterator<T>& it)
        {
            return ptr->data < it.ptr->data;
        }
        bool operator<=(const Iterator<T>& it)
        {
            return ptr->data <= it.ptr->data;
        }
        bool operator>=(const Iterator<T>& it)
        {
            return ptr->data >= it.ptr->data;
        }
    private:
        Node<T>* ptr;
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
        this->size = old_list.size;
        if (old_list.head != NULL) {
            Node<T>* current = old_list.head;
            while (current != old_list.tail) {
                this->Push_back(current->data);
                current = current->pNext;
            }
        }
    }
    ~List() {
        while (head != tail) {
            Node<T>* first = head->pNext;
            delete head;
            head = first;
        }
    }
    void Push_back(T data) {
        if (head == NULL) {
            head = new Node<T>(data);
            tail = new Node<T>(NULL, NULL, head);
            head->pNext = tail;
        }
        else {
            Node<T>* last = new Node<T>(NULL, NULL, tail);
            tail->pNext = last;
            tail->data = data;
            tail = last;
        }
        size++;
    }
    void Push_front(T data) {
        if (head == NULL) {
            head = new Node<T>(data);
            tail = new Node<T>(NULL, NULL, head);
            head->pNext = tail;
        }
        else {
            Node<T>* first = new Node<T>(data, head, NULL);
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
            Node<T>* last = tail->pPrev;
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
            Node<T>* first = head->pNext;
            delete head;
            head = first;
            size--;
        }
    }
    bool Empty() {
        if (size) {
            return 0;
        }
        else {
            return 1;
        }
    }
    size_t Size() {
        return size;
    }
    string Output() {
        string str = "";
        Node<T>* current = head;
        while (current != tail) {
            str += to_string(current->data) + " ";
            current = current->pNext;
        }
        return str;
    }
    Iterator<T> begin() {
        return Iterator<T>(head);
    }
    Iterator<T> end() {
        return Iterator<T>(tail);
    }
};


int main() {
    List<int> myList;
    myList.Push_back(5);
    myList.Push_front(44);
    myList.Push_back(567);
    myList.Push_back(23);
    myList.Push_front(235);
    myList.Push_front(7);
    cout << myList.Size() << endl;
    cout << myList.Output() << endl;
    List<int> newList(myList);
    List<int>::Iterator<int> it;
    it = newList.begin();
    it++; it++;
    cout << *it << endl;
    it--;
    cout << *it << endl;
    it = newList.end();
    cout << *it << endl;
    List<int> myList2 = { 1,2,3,4,5 };
    cout << *myList2.begin();
    return 0;
}
