#ifndef Colloseum_h
#define Colloseum_h

#include "MinHeapArray.h"
#include "HashTable.h"

#include "Group.h"
#include "Gladiator.h"
#include "SplayTree.h"

class Colosseum {
private:
    hashTable<Group*> groupsTable;
    SplayTree<int> gladiatorsByID;
    MinHeapArray<int> groupsHeap;
    
    void SwapIndex(int ID1, int ID2);
    void SetGroupDown(int ID);
    
public:
    Colosseum(int n, int* trainingGroupsIDs);
    ~Colosseum(){
        list<Group*>* Chains = groupsTable.GetChains();
        for (int i = 0; i < groupsTable.GetNumberOfBoxes(); i++) {
            for (list<Group*>::iterator it = Chains[i].begin();
                 it != Chains[i].end(); ++it) {
                delete **it;
            }
        }
    }
    StatusType addTrainingGroup(int trainingGroupID);
    StatusType addGladiator(int gladiatorID, int score, int trainingGroup);
    StatusType trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);
    StatusType getMinTrainingGroup(int *trainingGroup);
    void printHeap() { groupsHeap.Print();}
    
};

#endif /* Colloseum_h */
