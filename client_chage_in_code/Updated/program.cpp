#include <iostream>

using std::ostream;
template <typename T>
class CList;
class iterator;   

template <typename T>
class CNode
{
    CNode *pPrev;
    T Data;
    CNode *pNext;

public:
    CNode();
    ~CNode();
    friend class CList<T>;
    template <typename T1>
    friend void splice(iterator& , CList<T1> , iterator&);  
    template <typename T2>   
    friend ostream& operator << (ostream &out , CList<T2> &);
};
    template <typename T>
    CNode<T>::CNode()
    {
        pPrev = NULL;
        pNext = NULL;
    }
    template <typename T>
    CNode<T>::~CNode()
    {
        pPrev = NULL;
        pNext = NULL;
    }
    template <typename T>
    typename CList<T>::iterator find(typename CList<T>::iterator,typename CList<T>::iterator,T);
    
    template <typename T>
class CList
{
    CNode<T> *pDummy;

public:   
    void InsertFirst(T);
    void InsertLast(T);
    void InsertAtPosition(T,int);

    int SearchFirstOccurence(T);
    int SearchLastOccurence(T);
    int SearchAllOccurence(T);

    T DeleteFirst();
    T DeleteLast();
    T DeleteAtPosition(int);

    int CountNode();

    void Display();

    void ConcatList(CList&);
    void ConcatAtPosition(CList& , int);

    void ReverseDisplay();
    void PhysicalReverse();

    void DeleteAll();

    bool ListEmpty();
    CList();
    ~CList();
    
    class iterator
        {
            CNode<T> *pCurrent;
            
            public:
            iterator();
            ~iterator();
            CNode<T>* Get_Current();
            bool operator ==(iterator &);
            bool operator !=(iterator &);
            bool operator >=(iterator &);
            bool operator <=(iterator &);
            void set(CNode<T> *);
            iterator& operator ++();
            iterator operator ++(int);
            iterator& operator --();
            iterator operator --(int);
            int operator *();
            bool operator <(iterator &);
            bool operator >(iterator &);
        };
        private:
        iterator m_Start;
        iterator m_End;
        public:
        iterator& begin();
        iterator& end();
        void push_back(T Get);
        void push_front(T Get);
    void splice(iterator Destination , CList &SourcePosition)
    {
        
        CNode<T> *pDestination = Destination.Get_Current();
                
        pDestination->pPrev->pNext = SourcePosition.pDummy->pNext;
        SourcePosition.pDummy->pPrev->pNext = pDestination;
        pDestination->pPrev = SourcePosition.pDummy->pPrev;

        SourcePosition.pDummy->pNext = SourcePosition.pDummy;
        SourcePosition.pDummy->pPrev = SourcePosition.pDummy;
    }
    void splice(iterator Destination,CList &SourceList , iterator SourcePosition)
    {    
        CNode<T> *pDestination = Destination.Get_Current();
        CNode<T> *pSourcePosition = SourcePosition.Get_Current();
        
        pSourcePosition->pPrev->pNext = pSourcePosition->pNext;
        pSourcePosition->pNext->pPrev = pSourcePosition->pPrev;
        pSourcePosition->pNext = pDestination;
        pSourcePosition->pPrev = pDestination->pPrev;
        pDestination->pPrev->pNext = pSourcePosition;
        pDestination->pPrev = pSourcePosition;
    } 
    CList& operator = (CList &cList)
    {
        CNode<T> *pTemp = NULL;
        CNode<T> *pTemp2 = NULL;
        CNode<T> *pNewNode = NULL;
        int iValue;
        
        pTemp = pDummy->pNext;
        if(pDummy == pDummy->pNext)
        {
            pTemp = cList.pDummy->pNext;
            while(pTemp != cList.pDummy)
            {
                iValue = pTemp->Data;
                InsertLast(iValue);
                pTemp = pTemp->pNext;    
            }
        }
        else
        {
            pTemp2 = cList.pDummy->pNext;
            pTemp = pDummy->pNext;            
            while(pTemp2 != cList.pDummy)
            {
                iValue = pTemp2->Data;
                if(pTemp == pDummy)
                    {
                        pNewNode = new CNode<T>;
                        pNewNode->pPrev = pDummy->pPrev;
                        pNewNode->Data = iValue;
                        pNewNode->pNext = pDummy;
                        pDummy->pPrev->pNext = pNewNode;
                        pDummy->pPrev = pNewNode;
                        pTemp = pTemp->pPrev;
                    }
                else
                    pTemp->Data = iValue;
                
                pTemp = pTemp->pNext;
                pTemp2 = pTemp2->pNext;
            }
        }
        return *this;
    }
    void unique()
    {
        CNode<T> *pTemp = NULL;
        CNode<T> *pDelete = NULL;

        pTemp = pDummy->pNext;
        do
        {
            pDelete = pTemp->pNext;
            if(pDelete->Data == pTemp->Data)
            {
                pDelete->pNext->pPrev = pTemp;
                pTemp->pNext = pDelete->pNext;
                pDelete->pNext = NULL;
                pDelete->pPrev = NULL;
                delete pDelete;
            }
            pTemp = pTemp->pNext;
        }while(pTemp != pDummy);
    }
    void merge(CList &refObj)
    {
        ConcatList(refObj);   
        sort();
        refObj.DeleteAll();
    }
    void sort()
    {
        CNode<T> *pTemp = NULL;
        int iData;
        CNode<T> *pCheck = NULL;
            
        if(pDummy == pDummy->pNext || pDummy == pDummy->pNext->pNext)
            return;

        pTemp = pDummy->pNext;
        do
        {
            pCheck = pTemp->pNext;
                do
                {
                    if(pTemp->Data > pCheck->Data)
                    {
                        iData = pTemp->Data;
                        pTemp->Data = pCheck->Data;
                        pCheck->Data = iData;
                    }
                pCheck=pCheck->pNext;
                }while(pCheck != pDummy);
            pTemp=pTemp->pNext;
        }while(pTemp->pNext != pDummy);  
    }
    template <typename T2>
    friend ostream& operator << (ostream &out , CList<T2> &);
};

        template <typename T>
        void CList<T>::push_back(T Get)
        {
            std::cout << "push back\n";
            InsertLast(Get);
        }

        template <typename T>
        void CList<T>::push_front(T Get)
        {
            std::cout << "push front\n";
            InsertFirst(Get);
        }
    template<typename T>
    typename CList<T>::iterator& CList<T>::begin()
        {
           m_Start.set(pDummy->pNext);
            return m_Start;
        }
    template <typename T>
    typename CList<T>::iterator& CList<T>::end()
        {
            m_End.set(pDummy);
            return m_End;
        }
    
    template <typename T>
    CList<T>::iterator::iterator()
            {
                pCurrent = NULL;
            }

    template <typename T>
    CList<T>::iterator::~iterator()
            {
                pCurrent = NULL;
            } 
    
    template <typename T>
    CNode<T>* CList<T>::iterator::Get_Current()
            {
                return pCurrent;
            }
    
    template <typename T>
    bool CList<T>::iterator::operator ==(iterator &cNode)
            {
                return (pCurrent == cNode.pCurrent);
            }
    
    template <typename T>
    bool CList<T>::iterator::operator !=(iterator &cNode)
            {
                return (pCurrent != cNode.pCurrent);
            }
    
    template <typename T>
    bool CList<T>::iterator::operator >=(iterator &cNode)
            {
                return (pCurrent >= cNode.pCurrent);
            }
    
    template <typename T>
    bool CList<T>::iterator::operator <=(iterator &cNode)
            {
                return (pCurrent <= cNode.pCurrent);
            }
    
    template <typename T>
    void CList<T>::iterator::set (CNode<T> *pCurr)
            {
                pCurrent = pCurr;
            }
    
    template <typename T>
    typename CList<T>::iterator& CList<T>::iterator::operator ++()
            {
                pCurrent = pCurrent->pNext;
                return *this;
            }
    
    template <typename T>
    typename CList<T>::iterator CList<T>::iterator::operator ++(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->pNext;
                return temp;
            }
    
    template <typename T>
    typename CList<T>::iterator& CList<T>::iterator::operator --()
            {
                pCurrent = pCurrent->pPrev;
                return *this;
            }
    
    template <typename T>
    typename CList<T>::iterator CList<T>::iterator::operator --(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->pPrev;
                return temp;
            }
    
    template <typename T>
    int CList<T>::iterator::operator *()
            {
                return pCurrent->Data;
            }
    
    template <typename T>
    bool CList<T>::iterator::operator <(iterator &cNode)
            {
                return pCurrent < cNode.pCurrent;
            }
    
    template <typename T>
    bool CList<T>::iterator::operator >(iterator &cNode)
            {
                return pCurrent > cNode.pCurrent;
            }

    template <typename T>
    void CList<T>::InsertFirst(T Value)
    {
        CNode<T>  *pNewNode = NULL;
        pNewNode = new CNode<T>;

        if(NULL == pNewNode)
        {
            std::cout << "Memory Allocation FAILED\n";
            return;
        }
        pNewNode->pPrev = NULL;
        pNewNode->Data = Value;
        pNewNode->pNext = NULL;

        if(pDummy == pDummy->pNext)
        {
            pDummy->pNext = pNewNode;
            pDummy->pPrev = pNewNode;
            pNewNode->pNext = pDummy;
            pNewNode->pPrev = pDummy;
            return;
        }
        pNewNode->pNext = pDummy->pNext;
        pNewNode->pPrev = pDummy->pNext->pPrev;
        pDummy->pNext = pNewNode;
        pNewNode->pNext->pPrev = pNewNode;
    }
    
    template <typename T>
    void CList<T>::InsertLast(T Value)
    {
        CNode<T>  *pNewNode = NULL;
        pNewNode = new CNode<T>;

        if(NULL == pNewNode)
        {
            std::cout << "Memory Allocation FAILED\n";
            return;
        }
        pNewNode->pPrev = NULL;
        pNewNode->Data = Value;
        pNewNode->pNext = NULL;

        if(pDummy == pDummy->pNext)
        {
            pDummy->pNext = pNewNode;
            pDummy->pPrev = pNewNode;
            pNewNode->pNext = pDummy;
            pNewNode->pPrev = pDummy;
            return;
        }
        pNewNode->pNext = pDummy;
        pNewNode->pPrev = pDummy->pPrev;
        pDummy->pPrev->pNext = pNewNode;
        pDummy->pPrev = pNewNode;
    }
    
    template <typename T>
    void CList<T>::InsertAtPosition(T Value , int iPos)
    {
        CNode<T> *pNewNode = NULL;
        CNode<T> *pTemp = NULL;
        int iCount = 0;
        iCount = CountNode();

        if(iPos <= 0 || iPos > iCount+1)
        {
            std::cout << "Position is Invalid\n";
            return;
        }
        if(iPos == 1)
        {
            InsertFirst(Value);
            return;
        }
        if(iPos == iCount+1)
        {
            InsertLast(Value);
            return;
        }
        pNewNode = new CNode<T>;
        if(NULL == pNewNode)
        {
            std::cout << "Memory Allocation FAILED\n";
            return;
        }
        pNewNode->pPrev = NULL;
        pNewNode->Data = Value;
        pNewNode->pNext = NULL;

        pTemp = pDummy->pNext;
        iCount = 1;
        while(iCount < iPos-1)
        {
            iCount++;
            pTemp = pTemp->pNext;
        }
        pNewNode->pNext = pTemp->pNext;
        pNewNode->pPrev = pTemp;
        pTemp->pNext->pPrev = pNewNode;
        pTemp->pNext = pNewNode;

    }
    
    template <typename T>
    T CList<T>::DeleteFirst()
    {
        T DelData;

        if(pDummy == pDummy->pNext)
            return -1;

        DelData = pDummy->pNext->Data;
        if(pDummy == pDummy->pNext->pNext)
        {
            pDummy->pNext->pNext = NULL;
            pDummy->pNext->pPrev = NULL;
            delete pDummy->pNext;
            pDummy->pNext = pDummy;
            pDummy->pPrev = pDummy;
            return DelData;
        }
            pDummy->pNext = pDummy->pNext->pNext;
            pDummy->pNext->pPrev->pNext = NULL;
            pDummy->pNext->pPrev->pPrev = NULL;
            delete (pDummy->pNext->pPrev);
            pDummy->pNext->pPrev = pDummy;
        return DelData;
    }
    
    template <typename T>
    T CList<T>::DeleteLast()
    {
        T DelData;
        CNode<T> *pTemp = NULL;

        if(pDummy == pDummy->pNext)
            return -1;
        DelData = pDummy->pPrev->Data;

        if(pDummy == pDummy->pNext->pNext)
        {
            pDummy->pNext->pNext = NULL;
            pDummy->pNext->pPrev = NULL;
            delete pDummy->pPrev;
            pDummy->pNext = pDummy;
            pDummy->pPrev = pDummy;
            return DelData;
        }
        pTemp = pDummy->pPrev;
        pDummy->pPrev->pPrev->pNext = pDummy;
        pDummy->pPrev = pDummy->pPrev->pPrev;
        pTemp->pNext = NULL;
        pTemp->pPrev = NULL;
        delete pTemp;
        pTemp = NULL;
        return DelData;
    }
    
    template <typename T>
    T CList<T>::DeleteAtPosition(int iPos)
    {
        int iCount;
        T RetData = 0;
        iCount = CountNode();
        CNode<T> *pTemp = NULL;

        if(iPos <= 0 || iPos > iCount+1)
        {
            std::cout << "Position is Invalid\n";
            return -1;
        }

        if(iPos == 1)
        {
            RetData = DeleteFirst();
            return RetData;
        }
        if(iPos == iCount)
        {
            iCount = DeleteLast();
            return iCount;
        }

        pTemp = pDummy->pNext;
        
        iCount = 1;
        while(iPos > iCount)
        {
            iCount++;
            pTemp = pTemp->pNext;
        }

        pTemp->pPrev->pNext = pTemp->pNext;
        pTemp->pNext->pPrev = pTemp->pPrev;
        RetData = pTemp->Data;

        pTemp->pNext = NULL;
        pTemp->pPrev = NULL;
        delete pTemp;
        pTemp = NULL;
        return RetData;
    }
    
    template <typename T>
    int CList<T>::SearchFirstOccurence(T Value)
    {
        CNode<T> *pTemp = NULL;
        int iPos = 0;
        if(pDummy == pDummy->pNext)
            return -1;
        pTemp = pDummy->pNext;
        do
        {
            iPos++;
            if(pTemp->Data == Value)
                return iPos;
            pTemp = pTemp->pNext;
        }
        while(pDummy != pTemp);
        return 0;
    }
    
    template <typename T>
    int CList<T>::SearchLastOccurence(T Value)
    {
        CNode<T> *pTemp = NULL;
        int iPos = 0;
        int iCount = 0;
        if(pDummy == pDummy->pNext)
            return -1;
        pTemp = pDummy->pNext;
        do
        {
            iCount++;
            if(pTemp->Data == Value)
                iPos = iCount;
            pTemp = pTemp->pNext;
        }while(pDummy != pTemp);
        if(iPos != 0)
            return iPos;
        return 0;
    }
    
    template <typename T>
    int CList<T>::SearchAllOccurence(T Value)
    {
        CNode<T> *pTemp = NULL;
        int iPos = 0;
        if(pDummy == pDummy->pNext)
            return -1;
        pTemp = pDummy->pNext;
        do
        {
            if(pTemp->Data == Value)
                iPos++;
            pTemp=pTemp->pNext;
        }while(pDummy != pTemp);
        return iPos;
    }
    
    template <typename T>
    void CList<T>::ConcatList(CList<T> &refObj)
    {
        if(pDummy == pDummy->pNext)
        {
            pDummy->pNext = refObj.pDummy->pNext;
            pDummy->pPrev = refObj.pDummy->pPrev;
            pDummy->pNext->pPrev = pDummy;
            pDummy->pPrev->pNext = pDummy;
            refObj.pDummy->pNext = refObj.pDummy->pPrev = refObj.pDummy;
        }
        else
        {
            pDummy->pPrev->pNext = refObj.pDummy->pNext;
            refObj.pDummy->pNext->pPrev = pDummy->pPrev;
            pDummy->pPrev = refObj.pDummy->pPrev;
            refObj.pDummy->pPrev->pNext = pDummy;
            refObj.pDummy->pNext = refObj.pDummy->pPrev = refObj.pDummy;
        }
        refObj.pDummy->pPrev = refObj.pDummy->pNext = refObj.pDummy;
    }
    
    template <typename T>
    void CList<T>::ConcatAtPosition(CList<T> &refObj , int iPos)
    {
        int iCount;
        CNode<T> *pTemp = NULL;

        iCount = CountNode();
        
        if(iPos <= 0 || iPos > iCount+1)
        {
            std::cout << "Position is Invalid\n";
            return;
        }
        if(refObj.pDummy == refObj.pDummy->pNext)
            return;
        if(iPos == 1)
        {
            refObj.pDummy->pPrev->pNext = this->pDummy->pNext;
            this->pDummy->pPrev->pNext = refObj.pDummy;
            this->pDummy->pNext->pPrev = refObj.pDummy->pPrev;
            refObj.pDummy->pPrev = this->pDummy->pPrev;
            
            this->pDummy->pNext = refObj.pDummy->pNext;
            this->pDummy->pPrev = refObj.pDummy->pPrev;

            this->pDummy->pNext->pPrev = this->pDummy;
            this->pDummy->pPrev->pNext = this->pDummy;

            refObj.pDummy->pNext = refObj.pDummy->pPrev = refObj.pDummy;
        }
        if(iPos == iCount+1)
        {
            ConcatList(refObj);
            return;
        }
        iCount = 1;
        pTemp = pDummy->pNext;
            while(iCount < iPos-1)
            {
                iCount++;
                pTemp = pTemp->pNext;
            }
        refObj.pDummy->pNext->pPrev = pTemp;
        refObj.pDummy->pPrev->pNext = pTemp->pNext;
        pTemp->pNext->pPrev = refObj.pDummy->pPrev;
        pTemp->pNext = refObj.pDummy->pNext;

        refObj.pDummy->pNext = refObj.pDummy->pPrev = refObj.pDummy;        
    }
    
    template <typename T>
    int CList<T>::CountNode()
    {
        int iCount = 1;
        CNode<T> *pTemp = NULL;
        if(pDummy == pDummy->pNext)
            return 0;
        pTemp = pDummy->pNext;
        do
        {
            iCount++;
            pTemp = pTemp->pNext;
        }while(pDummy != pTemp->pNext);
        return iCount;
    }
    
    template <typename T>
    void CList<T>::Display()
    {
        CNode<T> *pTemp = pDummy->pNext;
        if(pDummy == pDummy->pNext)
        {
            std::cout << "List is Empty...\n";
            return;
        }
        do{
            std::cout << "|" << pTemp->Data << "|->";
            pTemp = pTemp->pNext;
        }while(pDummy != pTemp);
        std::cout << std::endl;
    }
    
    template <typename T>
    void CList<T>::PhysicalReverse()
    {
        CNode<T> *pPre = pDummy->pPrev;
        CNode<T> *pCurrent = pDummy->pNext;
        CNode<T> *pNext = NULL;

        if(pDummy == pDummy->pNext)
            return;
        
        pDummy->pNext->pPrev = pDummy->pPrev;
        pDummy->pPrev->pNext = pDummy->pNext;

        pDummy->pNext = pPre;
        pDummy->pPrev = pCurrent;
            
            while(1)
            {
                pNext = pCurrent->pNext;
                pCurrent->pPrev = pNext;
                pCurrent->pNext = pPre;
                pPre = pCurrent;

                if(pCurrent == pDummy->pNext)
                    break;
                pCurrent = pNext;
            }
        pNext->pNext = pDummy;
        pCurrent->pPrev = pDummy;
    }

    template <typename T>
    void CList<T>::ReverseDisplay()
    {
        if(pDummy == pDummy->pNext)
            return;
        PhysicalReverse();
        Display();
        PhysicalReverse();
    }
    
    template <typename T>
    void CList<T>::DeleteAll()
    {
        CNode<T> *pTemp = NULL;
        while(pDummy != pTemp)
        {
            pTemp = pDummy->pNext;
            if(pDummy->pNext == pDummy)
                {
                    pDummy->pNext = pDummy->pPrev = NULL;
                    break;
                }
            pDummy->pNext = pTemp->pNext;
            pTemp->pNext->pPrev = pDummy;
            pTemp->pNext = NULL;
            pTemp->pPrev = NULL;
            delete pTemp;
        }
        pDummy->pNext = pDummy;
        pDummy->pPrev = pDummy;
        pTemp = NULL;
    }
    
    template <typename T>
    bool CList<T>::ListEmpty()
    {
        if(pDummy == pDummy->pNext)
            return 0;
        return 1;
    }
    
    template <typename T>
    CList<T>::CList()
    {
        pDummy = NULL;
        pDummy = new CNode<T>;
        pDummy->pPrev = pDummy;
        pDummy->Data = 0;
        pDummy->pNext = pDummy;
    }
    
    template <typename T>
    CList<T>::~CList()
    {
        if(pDummy->pNext != pDummy) 
            DeleteAll();
    }
 
    template <typename T2>
    ostream& operator << (ostream &out , CList<T2>  &pLis)
    {  
        CNode<T2> *pTemp = pLis.pDummy->pNext;

        if(pLis.pDummy == pLis.pDummy->pNext || pLis.pDummy == NULL)
        {
            out << "List is Empty...\n";
            return out;
        }
        do
        {
            out << "|" << pTemp->Data << "|->";
            pTemp = pTemp->pNext;
        }while(pTemp != pLis.pDummy->pPrev->pNext);
        std::cout << std::endl;
        return out;
    }

template <typename T>
void DisplayIterator(CList<T> &);
template <typename T>
void PrintList(CList<T> & , CList<T> &);         

int main(void)
{
    CList<char> obj1;
    CList<char> obj2;

    int iCounter;
    
    std::cout << obj1 << obj2;
    for(iCounter = 0 ; iCounter < 6 ; iCounter++)
    {
        obj1.push_back(iCounter+65);
        obj1.Display();
        obj2.push_front(iCounter+65);
        obj2.Display();
    }

    PrintList(obj1,obj2);

    
    obj2.splice(find(obj2.begin(),obj2.end(),(char)'E'),obj1);
    

    PrintList(obj1,obj2);

    // move first element of obj2 to the end
    obj2.splice(
        obj2.end(),     // destination position
        obj2,           // source list
        obj2.begin()    // source position
                );   

    PrintList(obj1,obj2);

    // sort second list, assign to obj1 and remove dupicates
    obj2.sort();

    obj1 = obj2;

    obj2.unique();

    // merge both sorted lists into the first list
    PrintList(obj1,obj2);
    obj1.merge(obj2);
    PrintList(obj1,obj2);
    
    return 0;    
}

template <typename T>
        typename CList<T>::iterator find(typename CList<T>::iterator Ci_Begin ,typename CList<T>::iterator Ci_End,T Data)
        {
           typename CList<T>::iterator iter = Ci_Begin;
            
            while(Ci_End != iter)
            {
                if(*iter == Data)
                    return iter;
                ++iter;
            }
           return Ci_End;
        }

template <typename T>
void PrintList(CList<T> &obj1 , CList<T> &obj2)
{
    std::cout << "list 1 :-\n\t " << obj1 << std::endl << "list 2 :-\n\t " << obj2 << std::endl << std::endl;
}

    template <typename T>
    void DisplayIterator(CList<T> &list)
    {
        std::cout << "\nIterator display start : Linked list is : \n";
    for(typename CList<T>::iterator iter = list.begin(); iter != list.end() ; ++iter)
        std::cout << "<-|" << *iter << "|->";
        std::cout << std::endl;    
    }