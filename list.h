#ifndef list_h
#define list_h

using namespace std;

template <class T, class Compare = std::less<T> >
class list {
private:
    struct Node {
        T* data;
        Node* next;
        
        /* Default Constructor */
        Node() : data(NULL), next(NULL) {};
        
        /* Constructor */
        Node(T const &data, Node *next) : data(new T(data)), next(next) {}
        
        /* D'ctor */
        ~Node() { delete data; }
        
    } *head;

public:
    
class iterator {
    friend class list<T>;
private:
    list* listPointer;
    Node* nodePointer;
    
public:
    iterator (list* listPointer, Node* nodePointer)
    : listPointer(listPointer), nodePointer (nodePointer) {}
    
    T* operator* () const { return nodePointer->data; } //CHANGE IT!
    bool operator == (const iterator &it) const {
        return nodePointer == it.nodePointer && listPointer == it.listPointer;
    }
    bool operator != (const iterator &it)const { return !(*this == it); }
    iterator& operator++() {
        nodePointer = nodePointer->next;
        return *this;
    }
};
    /* Constructor */
    list() : head(new Node) {}
    
    /* D'ctor */
    ~list()
    {
        while (head)
        {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    
    iterator begin() { return iterator(this, head->next); }
    iterator end() { return iterator(this, NULL); }
    void pushFront(T const &element) {
        head->next = new Node(element, head->next);
    }
    
    
    T* find(const T &element) {
        for (Node* place = head->next; place != NULL; place = place->next) {
            if (!Compare()(*place->data, element) && !Compare()(element, *place->data)) {
                return place->data;
            }
        }
        return NULL;
    }
    
};

#endif /* list_h */
