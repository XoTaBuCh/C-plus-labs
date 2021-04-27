#include <iostream> 
#include <vector>
#include <iterator>

using namespace std;

const int MAX_size = 4;

template <typename T>
class Deque
{
private:
    template <typename T>
    struct Block {
        T block[MAX_size];
    };

    vector<Block<T>*> List;
    int front;
    int rear;
    size_t size;

public:
    class Iterator : iterator<random_access_iterator_tag, T> {
    private:
        Deque<T>* pointer;
        int index;
    public:
        Iterator() {
            pointer = nullptr;
        }
        Iterator(Deque<T>* pointer, int index) {
            this->pointer = pointer;
            this->index = index;
        }
        T& operator*() {
            int x = (*pointer)[index];
            return x;
        }
        T& operator*() const {
            int x = (*pointer)[index];
            return x;
        }
        bool operator==(const Iterator& other) const {
            return this->index == other.index && this->pointer == other.pointer;
        }
        bool operator!=(const Iterator& other) const {
            return !(this->index == other.index && this->pointer == other.pointer);
        }
        bool operator<(const Iterator& other) const {
            return this->index < other.index;
        }
        bool operator>(const Iterator& other) const {
            return this->index > other.index;
        }
        bool operator<=(const Iterator& other) const {
            return this->index <= other.index;
        }
        bool operator>=(const Iterator& other) const {
            return this->index >= other.index;
        }
        Iterator& operator--(T) {
            auto old = new Iterator(pointer, index);
            index++;
            return *old;
        }
        Iterator& operator--() {
            index--;
            return *this;
        }
        Iterator& operator++() {
            index++;
            return *this;
        }
        Iterator& operator++(T) {
            auto old = new Iterator(pointer, index);
            index++;
            return *old;
        }
        Iterator& operator+=(int a) {
            index += a;
            return *this;
        }
        Iterator& operator-=(int a) {
            index -= a;
            return *this;
        }
        Iterator& operator-(int a) {
            auto new_it = new Iterator(pointer, index);
            new_it->index -= a;
            return *new_it;
        }
        Iterator& operator+(int a) {
            auto new_it = new Iterator(pointer, index);
            new_it->index += a;
            return *new_it;
        }
        Iterator& operator=(Iterator& a) {
            this->pointer = a.pointer;
            this->index = a.index;
            return *this;
        }
    };
    Deque() {
        Block<T>* block1 = new Block<T>;
        Block<T>* block2 = new Block<T>;
        List.push_back(block1);
        List.push_back(block2);
        size = 0;
        front = 0;
        rear = 0;
    }
    ~Deque() {
        for (int i = 0; i < List.size(); i++) {
            delete[] List[i];
        }
    }
    T& operator[](int index) {
        return List[index / MAX_size]->block[index % MAX_size];
    }
    size_t Size() {
        return size;
    }
    void Clear() {
        for (int i = 0; i < List.size(); i++) {
            delete[] List[i];
        }
    }
    void push_back(T key)
    {
        if (size == 0) {
            front = 0;
            rear = 1;
            List[0]->block[0] = key;
        }
        else if (rear == MAX_size * List.size()) {
            rear = 1;
            if (front - rear <= 4) {
                auto itVec = List.begin();
                Block<T>* newBlock = new Block<T>();
                List.insert(itVec, newBlock);
                front += MAX_size;
            }
            List[0]->block[0] = key;
        }
        else {
            if (front / MAX_size == rear / MAX_size && front >= rear) {
                auto itVec = List.begin();
                Block<T>* newBlock = new Block<T>();
                itVec += (rear / MAX_size);
                List.insert(itVec, newBlock);
                front += MAX_size;
            }
            List[rear / MAX_size]->block[rear % MAX_size] = key;
            rear++;
        }
        size++;
    }
    void push_front(T key)
    {
        if (front == 0) {
            front = MAX_size * List.size() - 1;
            if (front - rear <= 4) {
                Block<T>* newBlock = new Block<T>();
                List.push_back(newBlock);
                front += MAX_size;
            }
            List[front / MAX_size]->block[front % MAX_size] = key;
        }
        else {
            if (front / MAX_size == rear / MAX_size && front >= rear) {
                auto itVec = List.begin();
                Block<T>* newBlock = new Block<T>();
                itVec += (rear / MAX_size);
                List.insert(itVec, newBlock);
                front += MAX_size;
            }
            front--;
            List[front / MAX_size]->block[front % MAX_size] = key;
        }
        size++;
    }
    void pop_back() {
        if (size == 0) {
            exit(-1);
        }
        else if (rear == 1) {
            rear = MAX_size * List.size();
        }
        else {
            rear--;
        }
    }
    void pop_front() {
        if (size == 0) {
            exit(-1);
        }
        else if (front = MAX_size * List.size() - 1) {
            front = 0;
        }
        else {
            front++;
        }
    }
    Iterator begin() {
        return Iterator(this, 0);
    }
    Iterator end() {
        return Iterator(this, size);
    }
};



int main()
{
    Deque<int> dq;

    dq.push_front(12);
    dq.push_front(13);
    dq.push_front(14);
    dq.push_front(15);
    dq.push_front(16);
    dq.push_front(17);
    dq.push_front(18);
    dq.push_front(19);
    dq.push_front(20);
    dq.push_front(21);
    dq.push_front(22);
    dq.push_front(23);
    dq.push_front(24);
    dq.push_front(25);
    dq.push_front(11);
    dq.push_front(10);
    dq.push_front(9);
    dq.push_front(8);
    dq.push_front(7);
    dq.push_front(6);
    dq.push_front(5);
    dq.push_back(4);
    return 0;
}