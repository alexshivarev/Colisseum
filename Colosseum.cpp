#include "Colosseum.h"

Colosseum::Colosseum(int n, int* trainingGroupsIDs)
: groupsTable(), gladiatorsByID(), groupsHeap(MinHeapArray<int>(n, trainingGroupsIDs)) {
    for (int i = 0; i != n; ++i) {
        Group* g = new Group(trainingGroupsIDs[i], i);
        groupsTable.Insert(g);
    }
    groupsHeap.MakeHeap(&groupsTable);
}

StatusType Colosseum::addTrainingGroup(int trainingGroupID) {
    if (trainingGroupID < 0) {
        return INVALID_INPUT;
    }
    if (groupsTable.Find(trainingGroupID) != NULL) {
        return FAILURE;
    }
    try {
        Group* g = new Group(trainingGroupID, groupsHeap.GetSize());
        groupsTable.Insert(g);
        groupsHeap.Insert(trainingGroupID);
    } catch (OutOfMemoryException& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Colosseum::addGladiator(int gladiatorID, int score, int trainingGroup) {
    if ( gladiatorID < 0 || score < 0 || trainingGroup < 0 ) {
        return INVALID_INPUT;
    }
    if ( gladiatorsByID.Find(gladiatorID) || !groupsTable.Find(trainingGroup)) {
        return FAILURE;
    }
    try {
        Group* g = *groupsTable.Find(trainingGroup);
        gladiatorsByID.Insert(gladiatorID, gladiatorID);
        g->addGladiator(gladiatorID, score);
    } catch (OutOfMemoryException& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Colosseum::trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2) {
    if (k1 <= 0 || k2 <= 0 || trainingGroup1 < 0 || trainingGroup2 < 0) {
        return INVALID_INPUT;
    }
    if (!groupsTable.Find(trainingGroup1) || !groupsTable.Find(trainingGroup2)) {
        return FAILURE;
    }
    try {
        Group* g1 = *groupsTable.Find(trainingGroup1);
        Group* g2 = *groupsTable.Find(trainingGroup2);
        if (trainingGroup1 == trainingGroup2 || !g1 || !g2 || !g1->getFlag() || !g2->getFlag()
            || g1->getNumberOfGladiators() < k1 || g2->getNumberOfGladiators() < k2) {
            return FAILURE;
        }
        int scoreSum1 = g1->scoreOfStrongestInGroup(k1);
        int scoreSum2 = g2->scoreOfStrongestInGroup(k2);
        if (scoreSum1 > scoreSum2) {
            groupsHeap.Delete(g2->getIndex());
        } else if (scoreSum1 < scoreSum2) {
            groupsHeap.Delete(g1->getIndex());
        } else {
            if (g1->getID() < g2->getID()) {
                groupsHeap.Delete(g2->getIndex());
            } else {
                groupsHeap.Delete(g1->getIndex());
            }
        }
    } catch (OutOfMemoryException& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Colosseum::getMinTrainingGroup(int *trainingGroup) {
    if (!trainingGroup) {
        return INVALID_INPUT;
    }
    *trainingGroup = groupsHeap.GetMin();
    return SUCCESS;
}
