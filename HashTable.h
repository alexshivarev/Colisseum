#ifndef HashTable_h
#define HashTable_h

#include <cassert>
#include "list.h"
#include "exceptions.h"

using namespace ColosseumEx;

template <class T>
class hashTable {
private:
    list<T>* Chains;
    int NumberOfElements;
    int NumberOfBoxes;
    int Capacity() { return 2 * NumberOfBoxes; }
    void RehashUp();
    int Hash(int const &key);

public:
    hashTable();
    ~hashTable();
    int Size() {return NumberOfElements;}
    int GetNumberOfBoxes() {return NumberOfBoxes; }
    T* Find(int key);
    void Insert(T element);
    list<T>* GetChains();
    
};

template <class T>
hashTable<T>::hashTable()
    : Chains(new list<T>[2]),
    NumberOfElements(0), NumberOfBoxes(2) {}

template <class T>
hashTable<T>::~hashTable() {
    delete[] Chains;
}

template <class T>
int hashTable<T>:: Hash(int const &key) {
    return key % NumberOfBoxes;
}

template <class T>
T* hashTable<T>::Find(int key) {
    int index = Hash(key);
    assert(index < NumberOfBoxes);
    for (typename list<T>::iterator it = Chains[index].begin();
            it != Chains[index].end(); ++it) {
        if(***(*it) == key) {
            return *it;
        }
    }
    return NULL;
}

template <class T>
void hashTable<T>::RehashUp() {
    int SizeOld = NumberOfBoxes;
    list<T>* ChainsOld = Chains;
    NumberOfBoxes = NumberOfBoxes * 2;
    Chains = new list<T>[NumberOfBoxes];
    NumberOfElements = 0;
    for (int i = 0; i < SizeOld; i++) {
        for (typename list<T>::iterator it = ChainsOld[i].begin();
             it != ChainsOld[i].end(); ++it) {
            Insert(**it);
        }
    }
    delete[] ChainsOld;
}



template <class T>
void hashTable<T>::Insert(T element) {
    int index = Hash(**element);
    assert(index < NumberOfBoxes);
    Chains[index].pushFront(element);
    NumberOfElements++;
    if (NumberOfElements >= Capacity()) {
        RehashUp();
    }
}

template <class T>
list<T>* hashTable<T>::GetChains() {
    return Chains;
}




#endif /* HashTable_h */
