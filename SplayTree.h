#ifndef SplayTree_hpp
#define SplayTree_hpp

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "exceptions.h"

#define HEAD SplayTree<T, Compare>::
#define TEMP template<class T, class Compare>
#define NODE typename SplayTree<T, Compare>::Node*

using namespace ColosseumEx;

using namespace std;

template<class T, class Compare = std::less<T> >
class SplayTree {
private:
    int NumberOfNodes;
    struct Node {
        Node* parent;
        Node* left;
        Node* right;
        T* key;
        
        int score;
        int scoreOfSubTree;
        int sizeOfSubTree;

        /* Default Constructor */
        Node()
        : parent(NULL), left(NULL), right(NULL), key(), score(0), scoreOfSubTree(0), sizeOfSubTree(0)  {}
        
        /* Constructor */
        Node(T const &key, int score)
        : parent(NULL), left(NULL), right(NULL), key(new T(key)),
        score(score), scoreOfSubTree(score), sizeOfSubTree(1) {}
        
        /* D'ctor */
        ~Node() {delete key; }
        
    } *root;
    
    Node* RightRotate(Node*);
    Node* LeftRotate(Node*);
    Node* Splay(Node*, T const&);
    void Split(T const& key, int score);

    Node* Splay_aux (Node* root, T const &key);
    void DeleteAll (Node* root);
    
    static bool EqualOrLess (T const &k1, T const &k2) {
        return !Compare()(k2, k1);
    }
    
    static bool Equal (T const &k1, T const &k2) {
        return(!Compare()(k2, k1) && !Compare()(k1, k2));
    }
    
    void InOrder_aux(Node* root) ;
    int scoreOfWeakestAux (Node* vertex, int index, int indexAux, int sum);
    void updateScoreAndSize(Node* n);
public:
    /* Constructor */
    SplayTree()
    : NumberOfNodes(0), root(NULL) {}
    
    ~SplayTree() { DeleteAll(root); }
    
    /* PUBLIC METHODS */
    void Insert(T const&, int score);
    T* Find(T const&);
    int Size() { return NumberOfNodes; };
    void InOrder();
    int scoreOfStrongestElements (int numberOfelements);
   
};

TEMP
void HEAD updateScoreAndSize(Node* n) {
    if (n == NULL) {
        return;
    }
    n->sizeOfSubTree = 1;
    n->scoreOfSubTree = n->score;
    if (n->left) {
        n->scoreOfSubTree += n->left->scoreOfSubTree;
        n->sizeOfSubTree += n->left->sizeOfSubTree;
    }
    if (n->right) {
        n->scoreOfSubTree += n->right->scoreOfSubTree;
        n->sizeOfSubTree += n->right->sizeOfSubTree;
    }
}

TEMP
NODE HEAD RightRotate(Node* n) {
    Node* tmp = n->left;
    n->left = tmp->right;
    updateScoreAndSize(n);
    if (tmp->right) {
        tmp->right->parent = n;
    }
    tmp->right = n;
    tmp->parent = n->parent;
    updateScoreAndSize(tmp);
    n->parent = tmp;
    return tmp;
}

TEMP
NODE HEAD LeftRotate(Node* n) {
    Node* tmp = n->right;
    n->right = tmp->left;
    updateScoreAndSize(n);
    if (tmp->left) {
        tmp->left->parent = n;
    }
    tmp->left = n;
    tmp->parent = n->parent;
    updateScoreAndSize(tmp);
    n->parent = tmp;
    return tmp;
}

TEMP
NODE HEAD Splay_aux(Node* root, T const &key) {
    if (!root || Equal(key,*root->key)) {
        return root;
    }
    // Key lies in left subtree
    if (Compare()(key,*root->key)) {
        root->left = Splay_aux(root->left, key);
        if (!root->left) {
            return root;
        } else if (root->left->right && EqualOrLess(*root->left->right->key,key)) {
            root->left = LeftRotate(root->left);
            root = RightRotate(root);
        } else if (EqualOrLess(*root->left->key,key)) {
            return root;
        } else if (root->left->left) {
            root = RightRotate(root);
            root = RightRotate(root);
        }
    } else {
        root->right = Splay_aux(root->right, key);
        if (!root->right) {
            return root;
        } else if (root->right->right && EqualOrLess(*root->right->right->key,key)) {
            root = LeftRotate(root);
            root = LeftRotate(root);
        } else if (EqualOrLess(*root->right->key,key)) {
            return root;
        } else if (root->right->left) {
            root->right =RightRotate(root->right);
            root = LeftRotate(root);
        }
    }
    return root;
}

TEMP
NODE HEAD Splay (Node* root, T const &key) {
    if (!root) return root;
    root = Splay_aux(root, key);
    if (root->right && EqualOrLess(*root->right->key, key)) {
        root = LeftRotate(root);
    } else if (EqualOrLess(*root->key, key)) {
        return root;
    } else if (root->left){
        root = RightRotate(root);
    }
    return root;
}

TEMP
void HEAD Split(T const& key, int score) {
    // Bring the closest leaf node to root
    root = Splay(root, key);
    
    // If key is already present, then return
    if (Equal(*root->key,key)) {
        throw (ElementAlreadyExistsException());
    }
    try
    {
        Node* n = new Node(key,score);
        Node* tmp = root;
        if(Compare()(*root->key,key)) {
            n->left = root;
            n->right = root->right;
            tmp->right = NULL;
            if (n->right) {
                n->right->parent = n;
            }
        } else {
            n->right = root;
            n->left = tmp->left;
            root->left = NULL;
            if(n->left) {
                n->left->parent = n;
            }
        }
        root = n;
        tmp->parent = n;
        updateScoreAndSize(n->left);
        updateScoreAndSize(n->right);
        updateScoreAndSize(n);
        NumberOfNodes++;
    }
    BadAlloc
}

TEMP
void HEAD Insert(T const& key, int score) {
    // Simple Case: If tree is empty
    if (root == NULL) {
        try
        {
            root = new Node(key, score);
        }
        BadAlloc
        NumberOfNodes++;
        return;
    }
    Split(key,score);
}

TEMP
T* HEAD Find (T const& key) {
    if (!Size()) {
        return NULL;
    }
    root = Splay(root,key);
    if (Equal(*root->key,key)) {
        return root->key;
    }
    return NULL;
}

TEMP
void HEAD DeleteAll (Node* n) {
    if (n != NULL) {
        DeleteAll(n->left);
        DeleteAll(n->right);
        delete n;
    }
}

TEMP
void HEAD InOrder_aux(Node* root) {
    if (root)
    {
        InOrder_aux(root->left);
        cout<< "key: " <<*root->key;
        if(root->left)
            cout<< " | left child: "<< *root->left->key;
        if(root->right)
            cout << " | right child: " << *root->right->key;
        cout<< "\n";
        InOrder_aux(root->right);
    }
}

TEMP
void HEAD InOrder() {
    InOrder_aux(root);
}

TEMP
int HEAD scoreOfStrongestElements (int numberOfelements) {
    if (NumberOfNodes == 0 ) {
        return 0;
    }
    if (numberOfelements >= NumberOfNodes ) {
        return root->scoreOfSubTree;
    }
    int index = NumberOfNodes - numberOfelements;
    return root->scoreOfSubTree - scoreOfWeakestAux(root, index, 0, 0);
}


TEMP
int HEAD scoreOfWeakestAux (Node* vertex, int index, int indexAux, int sum) {
    
    int leftSize = vertex->left? vertex->left->sizeOfSubTree : 0;
    int newSum = vertex->left? vertex->left->scoreOfSubTree + sum + vertex->score
    : sum + vertex->score;
    int next_index = indexAux + leftSize + 1;
    if(next_index < index)
        newSum = scoreOfWeakestAux (vertex->right, index, next_index, newSum);
    else if (next_index > index)
        newSum = scoreOfWeakestAux (vertex->left, index, indexAux, sum);
    return newSum;
}

#endif /* SplayTree_hpp */
