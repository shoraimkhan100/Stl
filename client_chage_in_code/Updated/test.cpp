#include <iostream>

using std::ostream;

template <typename T>
class CList;

template <typename T>
class CNode {
    CNode *pPrev;
    T Data;
    CNode *pNext;

public:
    CNode() : pPrev(nullptr), pNext(nullptr) {}
    ~CNode() {}
    friend class CList<T>;
    template <typename T1>
    friend void splice(typename CList<T1>::iterator&, CList<T1>&, typename CList<T1>::iterator&);
    template <typename T2>
    friend ostream& operator<<(ostream& out, CList<T2>&);
};

template <typename T>
class CList {
    CNode<T> *pDummy;

public:
    class iterator {
        CNode<T> *pCurrent;

    public:
        iterator() : pCurrent(nullptr) {}
        ~iterator() {}
        CNode<T>* Get_Current() { return pCurrent; }
        bool operator==(iterator& other) { return pCurrent == other.pCurrent; }
        bool operator!=(iterator& other) { return pCurrent != other.pCurrent; }
        iterator& operator++() {
            if (pCurrent)
                pCurrent = pCurrent->pNext;
            return *this;
        }
        iterator operator++(int) {
            iterator temp(*this);
            ++(*this);
            return temp;
        }
        iterator& operator--() {
            if (pCurrent)
                pCurrent = pCurrent->pPrev;
            return *this;
        }
        iterator operator--(int) {
            iterator temp(*this);
            --(*this);
            return temp;
        }
        T operator*() { return pCurrent->Data; }
    };

    CList() {
        pDummy = new CNode<T>();
        pDummy->pNext = pDummy;
        pDummy->pPrev = pDummy;
    }

    ~CList() {
        DeleteAll();
        delete pDummy;
    }

    void InsertFirst(T);
    void InsertLast(T);
    void InsertAtPosition(T, int);

    int SearchFirstOccurence(T);
    int SearchLastOccurence(T);
    int SearchAllOccurence(T);

    T DeleteFirst();
    T DeleteLast();
    T DeleteAtPosition(int);

    int CountNode();

    void Display();

    void ConcatList(CList&);
    void ConcatAtPosition(CList&, int);

    void ReverseDisplay();
    void PhysicalReverse();

    void DeleteAll();

    bool ListEmpty();

    iterator begin() {
        iterator iter;
        iter.pCurrent = pDummy->pNext;
        return iter;
    }

    iterator end() {
        iterator iter;
        iter.pCurrent = pDummy;
        return iter;
    }

    void push_back(T Get) {
        InsertLast(Get);
    }

    void push_front(T Get) {
        InsertFirst(Get);
    }

    void splice(iterator Destination, CList& SourcePosition) {
        CNode<T> *pDestination = Destination.pCurrent;

        pDestination->pPrev->pNext = SourcePosition.pDummy->pNext;
        SourcePosition.pDummy->pNext->pPrev = pDestination->pPrev;
        pDestination->pPrev = SourcePosition.pDummy->pPrev;
        SourcePosition.pDummy->pPrev->pNext = pDestination;

        SourcePosition.pDummy->pNext = SourcePosition.pDummy;
        SourcePosition.pDummy->pPrev = SourcePosition.pDummy;
    }

    void splice(iterator Destination, CList& SourceList, iterator SourcePosition) {
        CNode<T> *pDestination = Destination.pCurrent;
        CNode<T> *pSourcePosition = SourcePosition.pCurrent;

        pSourcePosition->pPrev->pNext = pSourcePosition->pNext;
        pSourcePosition->pNext->pPrev = pSourcePosition->pPrev;
        pSourcePosition->pNext = pDestination;
        pSourcePosition->pPrev = pDestination->pPrev;
        pDestination->pPrev->pNext = pSourcePosition;
        pDestination->pPrev = pSourcePosition;
    }

    CList& operator=(CList& cList) {
        if (this == &cList)
            return *this;

        DeleteAll();

        CNode<T>* pTemp = cList.pDummy->pNext;
        while (pTemp != cList.pDummy) {
            InsertLast(pTemp->Data);
            pTemp = pTemp->pNext;
        }
        return *this;
    }

    void unique() {
        CNode<T>* pTemp = pDummy->pNext;
        while (pTemp != pDummy) {
            CNode<T>* pDelete = pTemp->pNext;
            if (pDelete->Data == pTemp->Data) {
                pDelete->pNext->pPrev = pTemp;
                pTemp->pNext = pDelete->pNext;
                delete pDelete;
            }
            pTemp = pTemp->pNext;
        }
    }

    void merge(CList& refObj) {
        ConcatList(refObj);
        sort();
        refObj.DeleteAll();
    }

    void sort() {
        if (pDummy == pDummy->pNext || pDummy == pDummy->pNext->pNext)
            return;

        CNode<T>* pTemp = pDummy->pNext;
        do {
            CNode<T>* pCheck = pTemp->pNext;
            do {
                if (pTemp->Data > pCheck->Data) {
                    T temp = pTemp->Data;
                    pTemp->Data = pCheck->Data;
                    pCheck->Data = temp;
                }
                pCheck = pCheck->pNext;
            } while (pCheck != pDummy);
            pTemp = pTemp->pNext;
        } while (pTemp->pNext != pDummy);
    }

    template <typename T2>
    friend ostream& operator<<(ostream& out, CList<T2>&);
};

template <typename T>
void CList<T>::InsertFirst(T value) {
    CNode<T>* newNode = new CNode<T>();
    newNode->Data = value;
    newNode->pNext = pDummy->pNext;
    newNode->pPrev = pDummy;
    pDummy->pNext->pPrev = newNode;
    pDummy->pNext = newNode;
}

template <typename T>
void CList<T>::InsertLast(T value) {
    CNode<T>* newNode = new CNode<T>();
    newNode->Data = value;
    newNode->pNext = pDummy;
    newNode->pPrev = pDummy->pPrev;
    pDummy->pPrev->pNext = newNode;
    pDummy->pPrev = newNode;
}

template <typename T>
int CList<T>::CountNode() {
    int count = 0;
    CNode<T>* temp = pDummy->pNext;
    while (temp != pDummy) {
        count++;
        temp = temp->pNext;
    }
    return count;
}

template <typename T>
bool CList<T>::ListEmpty() {
    return pDummy->pNext == pDummy;
}

template <typename T>
void CList<T>::Display() {
    CNode<T>* temp = pDummy->pNext;
    while (temp != pDummy) {
        std::cout << temp->Data << " ";
        temp = temp->pNext;
    }
    std::cout << std::endl;
}

template <typename T>
typename CList<T>::iterator find(typename CList<T>::iterator Ci_Begin, typename CList<T>::iterator Ci_End, T Data) {
    typename CList<T>::iterator iter = Ci_Begin;

    while (iter != Ci_End) {
        if (*iter == Data)
            return iter;
        ++iter;
    }
    return Ci_End;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, CList<T>& list) {
    CNode<T>* temp = list.pDummy->pNext;
    while (temp != list.pDummy) {
        out << temp->Data << " ";
        temp = temp->pNext;
    }
    return out;
}

void My_Main() {
    CList<int> obj1, obj2;
    std::cout << obj1 << obj2;
    std::cout << "\t------------------------------------------ before pushing ------------------------------------------ \n\n";
    for (int iHold = 0; iHold < 6; iHold++) {
        obj1.push_back(iHold + 65);
        obj2.push_front(iHold + 65);
    }
    std::cout << "\t------------------------------------------ after pushing ------------------------------------------ \n\n";
    std::cout << obj1 << std::endl;
    std::cout << obj2 << std::endl;

    std::cout << "\t------------------------------------------  before splice 2 param ------------------------------------------ \n\n";
    obj2.splice(find(obj2.begin(), obj2.end(), 'A'), obj1);

    //obj2.splice(find(obj2.begin(), obj2.end(), 'A'), obj1);
    std::cout << "\t------------------------------------------  After splice 2 param ------------------------------------------ \n\n";
    std::cout << obj1 << std::endl;
    std::cout << obj2 << std::endl;

    std::cout << "\t------------------------------------------ Before splice 3 param ------------------------------------------ \n\n";
    obj2.splice(obj2.end(), obj2, obj2.begin());
    std::cout << "\t------------------------------------------ After Splice 3 parameter ------------------------------------------ \n\n";
    std::cout << obj1 << std::endl;
    std::cout << obj2 << std::endl;

    std::cout << "\t------------------------------------------ before sorting ------------------------------------------ \n\n";
    obj2.sort();
    std::cout << "\t------------------------------------------ After sorting ------------------------------------------ \n\n";
    std::cout << obj1 << std::endl;
    std::cout << obj2 << std::endl;

    std::cout << "\t------------------------------------------ Before = operator ------------------------------------------ \n\n";
    obj1 = obj2;
    std::cout << "\t------------------------------------------ after = operator ------------------------------------------ \n\n";
    std::cout << obj1 << std::endl;
    std::cout << obj2 << std::endl;

    std::cout << "\t------------------------------------------ before unique ------------------------------------------ \n\n";
    obj2.unique();
    std::cout << "\t------------------------------------------ After unique ------------------------------------------ \n\n";
    std::cout << obj1 << std::endl;
    std::cout << obj2 << std::endl;

    std::cout << "\t------------------------------------------ before merge ------------------------------------------" << std::endl << std::endl;
    std::cout << obj1 << std::endl;
    std::cout << obj2 << std::endl;
    obj1.merge(obj2);
    std::cout << "\t------------------------------------------ After merge ------------------------------------------" << std::endl << std::endl;
    std::cout << obj1 << std::endl;
    std::cout << obj2 << std::endl;
    obj1.DeleteAll();
    obj2.DeleteAll();
    std::cout << "Successfully executed..\n";
}

int main() {
    My_Main();
    return 0;
}
