﻿#include <iostream> 
#include <vector>
#include <deque>
using namespace std;
const int MAX_size = 4;
// Deque class 
template <typename T>
class Deque
{
private:
    template <typename T>
    struct Block {
        Block() {
            this->pPrev = NULL;
            this->pNext = NULL;
        }
        Block(Block<T>* pPrev, Block<T>* pNext) {
            this->pPrev = pPrev;
            this->pNext = pNext;
        }
        T block[MAX_size];
        Block<T>* pNext;
        Block<T>* pPrev;
    };

    vector<Block<T>*> List;
    int  front;
    int  rear;
    size_t  size;
public:
    Deque() {
        Block<T>* block1 = new Block<T>;
        Block<T>* block2 = new Block<T>(block1, block1);
        List.push_back(block1);
        List.push_back(block2);
        block1->pNext = block2;
        block1->pPrev = block2;
        size = 0;
        front = -1;
        rear = 0;
    }
    size_t Size() {
        return size;
    }
    void test() {

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
                Block<T>* newBlock = new Block<T>(List[List.size() - 1], List[0]->pNext);
                newBlock->pPrev->pNext = newBlock;
                newBlock->pNext->pPrev = newBlock;
                List.insert(itVec, newBlock);
                front += MAX_size;
            }
            List[0]->block[0] = key;
        }
        else {
            if (front - 1 - rear <= 4 && front > rear) {
                auto itVec = List.begin();
                Block<T>* newBlock = new Block<T>(List[front / MAX_size]->pPrev, List[front / MAX_size]);
                newBlock->pPrev->pNext = newBlock;
                newBlock->pNext->pPrev = newBlock;
                itVec += (rear / MAX_size + 1);
                List.insert(itVec, newBlock);
                front += MAX_size;
            }
            List[rear / MAX_size]->block[rear % MAX_size] = key;
            rear++;
        }
        size++;
    }
    /*void push_front(T key)
    {
        if (size == 0) {
            front = MAX_size * List.size() - 1;
            rear = 0;
            List[List.size() - 1]->block[MAX_size - 1] = key;
        }
        else if (front == 0) {
            front = MAX_size * List.size() - 1;
            if (front - rear <= 4) {
                Block<T>* newBlock = new Block<T>(List[(rear - 1) / MAX_size], List[(rear - 1) / MAX_size]->pNext);
                newBlock->pPrev->pNext = newBlock;
                newBlock->pNext->pPrev = newBlock;
                List.push_back(newBlock);
                front += MAX_size;
            }
            List[front / MAX_size]->block[front % MAX_size] = key;
        }
        else {
            if (front - 1 - rear <= 4 && front > rear) {
                auto itVec = List.begin();
                Block<T>* newBlock = new Block<T>(List[(rear - 1) / MAX_size], List[(rear - 1) / MAX_size]->pNext);
                newBlock->pPrev->pNext = newBlock;
                newBlock->pNext->pPrev = newBlock;
                itVec += (rear / MAX_size + 1);
                List.insert(itVec, newBlock);
                front += MAX_size;
            }
            front--;
            List[front / MAX_size]->block[front % MAX_size] = key;
        }
        size++;
    }*/
    void push_front(T key)
    {
        front--;
        if (front<0) {
            front = MAX_size * List.size() - 1;

            rear = 0;
            List[List.size() - 1]->block[MAX_size - 1] = key;
        }
        else if (front == 0) {
            front = MAX_size * List.size() - 1;
            if (front - rear <= 4) {
                Block<T>* newBlock = new Block<T>(List[(rear - 1) / MAX_size], List[(rear - 1) / MAX_size]->pNext);
                newBlock->pPrev->pNext = newBlock;
                newBlock->pNext->pPrev = newBlock;
                List.push_back(newBlock);
                front += MAX_size;
            }
            List[front / MAX_size]->block[front % MAX_size] = key;
        }
        else {
            if (front - 1 - rear <= 4 && front > rear) {
                auto itVec = List.begin();
                Block<T>* newBlock = new Block<T>(List[(rear - 1) / MAX_size], List[(rear - 1) / MAX_size]->pNext);
                newBlock->pPrev->pNext = newBlock;
                newBlock->pNext->pPrev = newBlock;
                itVec += (rear / MAX_size + 1);
                List.insert(itVec, newBlock);
                front += MAX_size;
            }
            front--;
            List[front / MAX_size]->block[front % MAX_size] = key;
        }
        size++;
    }
};



//main program
int main()
{
    Deque<int> dq;

    dq.push_back(12);
    dq.push_back(13);
    dq.push_back(14);
    dq.push_back(15);
    dq.push_back(16);
    dq.push_back(17);
    dq.push_back(18);
    dq.push_back(19);
    dq.push_front(11);
    dq.push_front(10);
    dq.push_front(9);
    dq.push_front(8);
    dq.push_front(7);
    dq.push_front(6);
    dq.push_front(5);
    return 0;
}