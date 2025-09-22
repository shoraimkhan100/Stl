#include <iostream>

using std::ostream;

template <typename T>
class CList;

template <typename T>
class CNode
{
    CNode *m_pPrev;
    T Data;
    CNode *m_pNext;

    public:
        friend class CList<T>;
    template <typename T2>    
    friend ostream& operator << (ostream& , CList<T2> &);
     
    CNode();
    ~CNode();
};

template <typename T>
class CList
{
    CNode<T> *m_pFirst;
    CNode<T> *m_pLast;
 
    public:   
    void InsertFirst(T);
    void InsertLast(T);
    void InsertAtPosition(T , int);
    T DeleteFirst();
    T DeleteLast();
    T DeleteAtPosition(int);
    int SearchFirstOccurence(T);
    int SearchLastOccurence(T);
    int SearchAllOccurence(T);
    int CountNode();
    void ReverseDisplay();
    void PhysicalReverse();
    void ConcatList(CList &);
    void ConcatAtPosition(CList &, int);
    void Display();
    void DeleteAll();
    bool ListEmpty();
    template <typename T2>    
    friend ostream& operator << (ostream& , CList &);

    CList();
    ~CList();
};

template <typename T2>
ostream& operator << (ostream & , CList<T2> &);