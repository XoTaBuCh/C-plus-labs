#include <iostream>
#include <iterator>
#include <initializer_list>

using namespace std;

template<typename T>
class Vector {
public:
    template<typename T>
    class Iterator : iterator<random_access_iterator_tag, T>
    {
    public:
        Iterator<T>(T* ptr = NULL) {
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
            if (++ptr == NULL) {
                throw "incremented an empty iterator";
            }
            return *this;
        }
        Iterator<T>& operator++(T)
        {
            if (++ptr == NULL) {
                throw "incremented an empty iterator";
            }
            return *this;
        }
        Iterator<T>& operator+=(int a) {
            ptr += a;
            return *this;
        }
        Iterator<T>& operator-=(int a) {
            ptr -= a;
            return *this;
        }
        Iterator<T>& operator--()
        {
            if (--ptr == NULL) {
                throw "incremented an empty iterator";
            }
            return *this;
        }
        Iterator<T>& operator--(T)
        {
            if (--ptr == NULL) {
                throw "incremented an empty iterator";
            }
            return *this;
        }
        T& operator*()
        {
            return *ptr;
        }
        bool operator>(const Iterator<T>& it)
        {
            return *ptr > *it.ptr;
        }
        bool operator<(const Iterator<T>& it)
        {
            return *ptr < *it.ptr;
        }
        bool operator<=(const Iterator<T>& it)
        {
            return *ptr <= *it.ptr;
        }
        bool operator>=(const Iterator<T>& it)
        {
            return *ptr >= *it.ptr;
        }
        T& operator [](int a) {
            return *(ptr + a);
        }
    private:
        T* ptr;
    };
    Vector(const initializer_list<T>& list) : Vector<T>() {
        for (T value : list) {
            Push_back(value);
        }
    }
    Vector(int a) { // setting an vector/deque whith size
        arr = new int[a + 2];
        Size = a;
        head = 1;
        tail = head + a;
        capacity = a + 2;
    }
    Vector() { // setting an empty vector/deque
        arr = new int[2];
        Size = 0;
        head = 0;
        tail = 0;
        capacity = 2;
    }
    Vector(const Vector& other) { // copying a vector/deque
        Size = other.Size;
        capacity = other.capacity;
        arr = new int[other.Size];
        head = other.head;
        tail = other.tail;
        for (int i = head; i < other.tail; i++) {
            arr[i] = other.arr[i];
        }
    }
    ~Vector() {
        delete[] arr;
    }
    int Get_size() {
        return Size;
    }
    int Get_cap() {
        return capacity;
    }
    void Output() { // output yhe whole vector/deque
        for (int i = head; i < tail; i++) {
            cout << arr[i] << " ";
        }
    }
    void Clear() { // cleaning vector or deque
        delete[] arr;
        Size = 0;
        capacity = 2;
        head = 0;
        tail = 0;
        arr = new int[2];
    }
    int at(int a) { // a - index of required element
        if (a >= tail || a < head) {
            exit(2);
        }
        return arr[head + a];
    }
    void at(int a, T b) { // a - index of required element, b - new element
        if (a >= tail || a < head) {
            exit(2);
        }
        arr[head + a] = b;
    }
    void Push_back(T a) { // a - new element
        if (tail == capacity)
        {
            capacity *= 2;
            int* tmp = new int[capacity];
            for (int i = head; i < tail; i++) {
                tmp[i] = arr[i];
            }
            delete[] arr;
            arr = tmp;
        }
        arr[tail] = a;
        tail++;
        Size++;
    }
    void Pop_back() { // removing last element
        if (tail == head) {
            exit(1);
        }
        Size--;
        tail--;
    }
    void Insert(int a, T b) { // b - element, a - its index
        if (a >= tail || a < head) {
            exit(2);
        }
        if ((tail - head) / 2 >= a) {
            if (head == 0) {
                int shift = capacity;
                capacity *= 2;
                int* tmp = new int[capacity];
                for (int i = head; i < tail; i++) {
                    tmp[i + shift] = arr[i];
                }
                delete[] arr;
                arr = tmp;
                head += shift;
                tail += shift;

            }
            head--;
            for (int i = head; i < a + head; i++) {
                arr[i] = arr[i + 1];
            }
            arr[a + head] = b;
        }
        else {
            if (tail == capacity)
            {
                capacity *= 2;
                int* tmp = new int[capacity];
                for (int i = head; i < tail; i++) {
                    tmp[i] = arr[i];
                }
                delete[] arr;
                arr = tmp;
            }
            for (int i = tail; i > a + head; i--) {
                arr[i] = arr[i - 1];
            }
            arr[a + head] = b;
            tail++;
        }

        Size++;
    }
    void Erase(int a) { // a - erasable index
        if (a >= tail || a < head) {
            exit(2);
        }
        if ((tail - head) / 2 >= a) {
            for (int i = head + a; i > head; i--) {
                arr[i] = arr[i - 1];
            }
            head++;
        }
        else {
            tail--;
            for (int i = head + a; i < tail; i++) {
                arr[i] = arr[i + 1];
            }
        }
        Size--;
    }
    int Find_value(T a) { // a - desired value
        for (int i = head; i < tail; i++) {
            if (arr[i] == a) {
                return i - head;
            }
        }
        exit(3);
    }
    Iterator<T> begin() {
        return Iterator<T>(arr);
    }
    Iterator<T> end() {
        return Iterator<T>(arr + Size);
    }
    Vector& operator = (const Vector& other) { // operator of assignment of one vector to another
        Size = other.Size;
        capacity = other.capacity;
        head = other.head;
        tail = other.tail;
        if (arr != nullptr) {
            delete[] arr;
        }
        arr = new int[capacity];
        for (int i = head; i < tail; i++) {
            arr[i] = other.arr[i];
        }
        return *this;
    }
    bool operator ==(const Vector& other) {  // equality operator
        if (other.Size != Size || head != other.head || tail != other.tail) {
            return false;
        }
        for (int i = head; i < tail; i++) {
            if (arr[i] != other.arr[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator !=(const Vector& other) { // inequality operator
        if (other.Size == Size && head != other.head && tail != other.tail) {
            for (int i = head; i < tail; i++) {
                if (arr[i] != other.arr[i]) {
                    return true;
                }
            }
            return false;
        }
        return true;
    }
    T& operator [](int a) {   //a - index of required element
        if (a >= tail || a < head) {
            exit(2);
        }
        return arr[head + a];
    }
private:
    int head;
    int tail;
    int Size;
    int* arr;
    int capacity;
};
int main() {
    Vector<int> myVec;
    myVec.Push_back(5);
    myVec.Push_back(567);
    myVec.Push_back(23);
    myVec.Push_back(53);
    myVec.Push_back(47);
    Vector<int>::Iterator<int> it = myVec.begin();
    it += 2;
    cout << *it << endl;
    cout << *(--it) << endl;
    cout << it[2] << endl;
    it = myVec.end();
    it--;
    cout << *it << endl;
    Vector<int> myVec2 = { 1, 2, 3, 4, 5 };
    cout << myVec2[3];
    return 0;
}