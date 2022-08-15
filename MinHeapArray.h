#ifndef MinHeapArray_h
#define MinHeapArray_h

#include <iostream>
#include "HashTable.h"
#include "Group.h"

template <class T>
class MinHeapArray {
private:
    int size;
    int capacity;
    T* data;
    hashTable<Group*>* groupsTable;
    
    void SiftDown(int index) {
        int LeftSon = 2 * index + 1;
        int RightSon = 2 * index + 2;
        if (LeftSon >= size) {
            return;
        }
        int min = index;
        if (data[LeftSon] < data[min]) {
            min = LeftSon;
        }
        if (RightSon < size && data[RightSon] < data[min]) {
            min = RightSon;
        }
        if (min != index) {
            Swap(index, min);
            SiftDown(min);
        }
    }
    
    void SiftUp(int index) {
        if (index == 0) {
            return;
        }
        int parent = (index - 1) / 2;
        if (data[parent] > data[index]) {
            Swap(parent, index);
            SiftUp(parent);
        }
    }
    
    void Resize(int newCapacity) {
        int *temp;
        temp = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity = newCapacity;
    }
    
    void SiftUpForDecKey(int index, int initial) {
        if (index == 0) {
            return;
        }
        int parent = (index - 1) / 2;
        if (data[parent] > data[index]) {
            int tmp = data[parent];
            data[parent] = data[index];
            data[index] = tmp;
            SwapIndex(initial, data[index]);
            SiftUpForDecKey(parent, initial);
        }
    }
    void Swap(int up, int down) {
        int tmp = data[up];
        data[up] = data[down];
        data[down] = tmp;
        SwapIndex(data[up], data[down]);
    }
    
    void SwapIndex(int ID1, int ID2) {
        Group* g1 = *groupsTable->Find(ID1);
        Group* g2 = *groupsTable->Find(ID2);
        int tmp = g1->getIndex();
        g1->changeIndex(g2->getIndex());
        g2->changeIndex(tmp);
    }
    
    void SetGroupDown(int ID) {
        Group* g = *groupsTable->Find(ID);
        g->lostFight();
    }
    
    
public:
 
    MinHeapArray(int n, int* input)
    : size(n), capacity(2*n), data(new T[2*n]), groupsTable(NULL) {
        for (int i = 0; i != n; ++i) {
            data[i] = input[i];
        }
    }
    ~MinHeapArray() {
        delete[] data;
    }
    
    void MakeHeap(hashTable<Group*>* p) {
        groupsTable = p;
        for (int i = size / 2 - 1; i >= 0; --i) {
            SiftDown(i);
        }
    }
    
    void Insert(int key) {
        data[size] = key;
        SiftUp(size);
        size++;
        if (size == capacity) {
            Resize(2*size);
        }
    }
    
    int GetSize() { return size; }
    int GetMin() {return data[0]; }
    
    void DecKey(int index, int x, int initial) {
        data[index] = x;
        SiftUpForDecKey(index, initial);
    }
    
    void DelMin(int initial) {
        int tmp = data[0];
        data[0] = data[size-1];
        data[size-1] = tmp;
        SwapIndex(initial, data[0]);
        
        SetGroupDown(initial);
        size--;
        if (4 * size == capacity) {
            Resize(2*size);
        }
        SiftDown(0);
    }
    
    void Delete(int index) {
        int initial = data[index];
        DecKey(index, -1, initial);
        DelMin(initial);
    }
    
    void Print() {
        for(int i = 0; i != size; ++i) {
            std::cout << data[i] << std::endl;
        }
    }
    
    void SetPointer(hashTable<Group>* p) {groupsTable = p;}
    
};
#endif /* MinHeapArray_h */
