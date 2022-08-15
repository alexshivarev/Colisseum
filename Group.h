#ifndef Group_h
#define Group_h

#include <iostream>
#include "Gladiator.h"
#include "MinHeapArray.h"
#include "SplayTree.h"

class Group {
private:
    int groupID;
    SplayTree<Gladiator> gladiators;
    int indexInHeap;
    bool ableToFight;
    
public:
    Group(int const& groupID, int index)
    : groupID(groupID), gladiators(), indexInHeap(index), ableToFight(1) {}
    
    ~Group(){}
    
    void addGladiator(int gladiatorID, int score) {
        Gladiator g = Gladiator(gladiatorID, score);
        gladiators.Insert(g, score);
    }
    
    int scoreOfStrongestInGroup(int const& k) { return gladiators.scoreOfStrongestElements(k); }
    
    void lostFight() {
        ableToFight = 0;
        indexInHeap = -1;
    }
    void changeIndex(int newIndex) {indexInHeap = newIndex;}
    int operator* () const { return groupID; }
    bool getFlag() { return ableToFight; }
    
    int getNumberOfGladiators() { return gladiators.Size(); }
    int getIndex() { return indexInHeap; }
    int getID() {return groupID; }
};

#endif /* Group_h */

