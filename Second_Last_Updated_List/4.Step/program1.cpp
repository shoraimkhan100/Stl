#include <iostream>

using std::ostream;

template <typename T>
class CList;

template <typename T>
class CNode
{
    CNode *pPrev;
    T Data;
    CNode *pNext;

public:
    template <typename T1>
    friend class CList;

    CNode()
    {
        pPrev = NULL;
        pNext = NULL;
    }
    ~CNode()
    {
        pPrev = NULL;
        pNext = NULL;
    }
    template <typename T2>
    friend ostream& operator << (ostream &out , CList<T2> &);
};

template <typename T>
class CList
{
    CNode<T> *pDummy;

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
    void ConcatList(CList &);
    void ConcatAtPosition(CList & , int);
    int CountNode();    
    void Display();
    void PhysicalReverse();
    void ReverseDisplay();
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

            bool operator ==(iterator &);
            bool operator !=(iterator &);
            bool operator >=(iterator &c);
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
    template <typename T2>
    friend ostream& operator << (ostream &out , CList<T2> &);
};
template <typename T2>
ostream& operator << (ostream &out , CList<T2> &pLis)
    {
        CNode<T2> *pTemp = pLis.pDummy->pNext;

        if(pLis.pDummy == pLis.pDummy->pNext)
        {
            out << "List is Empty...\n";
            return out;
        }
        while(pTemp != pLis.pDummy->pPrev->pNext)
        {
            out << "|" << pTemp->Data << "|->";
            pTemp = pTemp->pNext;
        }
        std::cout << std::endl;
        return out;
    }

template <typename T>
void CList<T>::InsertFirst(T Value)
    {
        CNode<T> *pNewNode = NULL;
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
        pNewNode->pPrev = pDummy->pNext->pPrev;
        pNewNode->pNext = pDummy->pNext;
        pDummy->pNext = pNewNode;
        pNewNode->pNext->pPrev = pNewNode;
    }
template <typename T>
void CList<T>::InsertLast(T Value)
    {
        CNode<T> *pNewNode = NULL;
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

        CNode<T> *pTemp = pDummy->pNext;
        
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
        
        while(pDummy != pTemp)
        {
            iPos++;
            if(pTemp->Data == Value)
                return iPos;
            pTemp = pTemp->pNext;
        }
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
        while(pDummy != pTemp)
        {
            iCount++;
            if(pTemp->Data == Value)
                iPos = iCount;
            pTemp = pTemp->pNext;
        }
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
        while(pDummy != pTemp)
        {
            if(pTemp->Data == Value)
                iPos++;
            pTemp=pTemp->pNext;
        }
        return iPos;
    }
template <typename T>
    void CList<T>::ConcatList(CList &refObj)
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
    void CList<T>::ConcatAtPosition(CList &refObj , int iPos)
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
        int iCount = 0;
        CNode<T> *pTemp = NULL;
        if(pDummy == pDummy->pNext)
            return 0;
        pTemp = pDummy->pNext;
        while(pDummy != pTemp)
        {
            iCount++;
            pTemp = pTemp->pNext;
        }
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
        while(pDummy != pTemp){
            std::cout << "|" << pTemp->Data << "|->";
            pTemp = pTemp->pNext;
        }
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
        CNode<T> *pTemp = pDummy->pPrev;
        if(pDummy == pDummy->pNext)
        {
            std::cout << "List is Empty...\n";
            return;
        }
        pTemp = pDummy->pPrev;
        while(pTemp != pDummy)
        {
            std::cout << "|" << pTemp->Data << "|->";
            pTemp = pTemp->pPrev;
        }
        std::cout << std::endl;
    }
template <typename T>
    void CList<T>::DeleteAll()
    {
        CNode<T> *pTemp = pDummy->pNext;
        if(pDummy == pDummy->pNext)
            return;
        while(pTemp != pDummy)
        {
            pTemp = pDummy->pNext;
            pDummy->pNext = pTemp->pNext;
            pTemp->pNext = NULL;
            pTemp->pPrev = NULL;
            delete pTemp;
                  
        }
        pTemp = NULL;
        pDummy->pNext = pDummy;
        pDummy->pPrev = pDummy;    
    }
template <typename T>
    bool CList<T>::ListEmpty()
    {
        if(pDummy == pDummy->pNext)
            return true;
        return false;
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
            void CList<T>::iterator::set(CNode<T> *pCurr)
            {
                pCurrent = pCurr;
            }
            template <typename T>
            //CList<T>::iterator& CList<T>::iterator::operator ++()
            typename CList<T>::iterator& CList<T>::iterator::operator++()
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

//template <typename T>
//void DisplayIterator(CList<T> &);
template <typename T>
void DisplayIterator(CList<T> &);

template <typename T>
void My_Main(T);

int main(void)
{
    int iChoice = 0;
    while(iChoice != -2)
    {
    std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
    std::cout << "\n\n|->1.Integer\n|->2.float\n|->3.char\n|->4.double\n|->5.Exit\n\n";
    std::cout << "Enter Your Choice :- ";
    std::cin >> iChoice;
    
        switch(iChoice)
        {
            case 1:
                My_Main(10);
                break;
            case 2:
                My_Main(20.22f);
                break;
            case 3:
                My_Main('A');
                break;
            case 4:
                My_Main(58.333);
                break;
            case 5:
                iChoice = -2;
        }
    }
    return 0;
}
template <typename T>
void My_Main(T tValue)
{
    CList<T> obj1;
    CList<T> obj2;
    int iPos = 0;
    T Value = 0;
    int iExit = 0;
    int iHold;
    int iChoice = 0;

    while(iExit != -1)
    {
        std::cout << "\n\n**********************************************************************************************************************\n\n";
                std::cout << "|->  1.Insert\n";
                std::cout << "|->  2.Delete\n";
                std::cout << "|->  3.Search\n";
                std::cout << "|->  4.Count\n";
                std::cout << "|->  5.Reverse\n";
                std::cout << "|->  6.Concat\n";
                std::cout << "|->  7.Back\n\n";
            std::cout << "Enter the Choice :- ";
            std::cin >> iChoice;

        if(iChoice > 7 || iChoice <= 0)
        {
            std::cout << "Your Choice is Wrong...\n";
            continue;
        }

        iExit = 1;
        while(iExit != -1)
        {
        switch(iChoice)
        {
            case 1://Insert
                while(iExit != -2)
                {
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "|->  1.Insert First\n";
                    std::cout << "|->  2.Insert Last\n";
                    std::cout << "|->  3.Insert At Position\n";
                    std::cout << "|->  4.Back\n";

                std::cout << "Enter Your Choice :- ";
                std::cin >> iChoice;
                
                    if(iChoice > 4 || iChoice <= 0)
                    {
                        std::cout << "Your Choice is Wrong...\n";
                        continue;
                    }
                switch(iChoice)
                {
                    case 1:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "\nEnter the Data :- ";
                            std::cin >> Value;
                            if(Value > 0)
                            {
                                obj1.InsertFirst(Value);
                                obj1.Display();
                                DisplayIterator(obj1);
                                //obj1.Display();
                            }
                    break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";        
                        std::cout << "\nEnter Your Data :- ";
                                std::cin >> Value;
                                if(Value > 0)
                                {
                                    obj1.InsertLast(Value);
                                    DisplayIterator(obj1);
                                    //obj1.Display();
                                }
                        break;

                        case 3:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        std::cout << "\nEnter inthe Position :- ";
                                std::cin >> iPos;
                                iHold = obj1.CountNode();
                                if(iPos < 0 || iPos > iHold+1)
                                {
                                    std::cout << "Position is invalid\n";
                                    continue;
                                }
                                std::cout << "Enter Your Data :- ";
                                std::cin >> Value;
                                if(Value > 0)
                                {
                                    obj1.InsertAtPosition(Value , iPos);
                                    //obj1.Display();
                                    DisplayIterator(obj1);
                                }
                            break;
                        case 4:
                            iExit = -2;
                    }
                }
                DisplayIterator(obj1);
                break;
               
            case 2:     
                iExit = 1;
                iHold = obj1.ListEmpty();
                if(iHold != 1)
                {
                while(iExit != -2)
                {
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "|->1.Delete First\n";
                    std::cout << "|->2.Delete Last\n";
                    std::cout << "|->3.Delete At Position\n";
                    std::cout << "|->4.Back\n";
                    std::cout << "Enter Your Choice :- ";
                    std::cin >> iChoice;
                    
                    if(iChoice > 4)
                    {
                        std::cout << "Your Choice is Wrong...\n";
                        continue;
                    }
                    
                    switch(iChoice)
                    {
                    case 1:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        Value = obj1.DeleteFirst();
                        if(Value != -1)
                            std::cout << "Deleted Data is " << Value << std::endl;
                        else    
                            break;
                        DisplayIterator(obj1);
                        //obj1.Display();
                        break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    Value = obj1.DeleteLast();
                        if(Value != -1)
                            std::cout << "Deleted Data is : " << Value << std::endl;
                        else
                            break;
                        DisplayIterator(obj1);
                        //obj1.Display();
                        break;

                    case 3:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        std::cout << "Enter Your Position :- ";
                        std::cin >> iPos;
                        iHold = obj1.CountNode();
                        if(iHold == 0)
                        {
                            std::cout << "List is Empty...\n";
                            break;
                        }
                        if(iPos <= 0 || iPos > iHold)
                        {   
                            std::cout << iPos << " Position is invalid\n";
                            continue;
                        }
                            Value = obj1.DeleteAtPosition(iPos);
                            if(Value != -1)
                                std::cout << "Deleted Data is : " << Value << std::endl;
                            DisplayIterator(obj1);
                            //obj1.Display();
                        break;

                    case 4:
                        iExit = -2;
                    }
                }
            }
            else
                DisplayIterator(obj1);
                //obj1.Display();
            break;
            
            case 3:  
            iExit = 1;  
            iHold = obj1.ListEmpty();
            if(iHold != 1)
            {
            while(iExit != -2)
            {
            std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                std::cout << "|->1.Search First Occurence\n";
                std::cout << "|->2.Search Last Occurence\n";
                std::cout << "|->3.Search All Occurence\n";
                std::cout << "|->4.Back\n";
                std::cout << "Enter Your Choice :- ";
                std::cin >> iChoice;
                
                if(iChoice > 4)
                {
                    std::cout << "Your Choice is Wrong...\n";
                    continue;
                }
                switch(iChoice)
                {
                case 1:
            std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "Enter Data into Search :- ";
                    std::cin >> Value;
     
                    if(Value != 0)
                    {
                    iHold = obj1.SearchFirstOccurence(Value);
                        if(iHold == -1)
                        {
                            std::cout << "List is Empty..\n";
                            break;
                        }
                        if(iHold == 0)
                            std::cout << "Data Not Found\n";
                        else
                            std::cout << "Position Of Data is " << iHold << std::endl;
                    }    
                    break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "Enter Data To Search :- ";
                    std::cin >> Value;

                    if(Value != 0)
                    {
                    iHold = obj1.SearchLastOccurence(Value);
                        if(iHold == -1)
                        {
                            std::cout << "List is Empty...\n";
                            break;
                        }
                        if(iHold == 0)
                            std::cout << "Data Not Found\n";
                        else
                            std::cout << "Position Of Data is " << iHold << std::endl;
                    }     
                    break;

                    case 3:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        std::cout << "Enter Data into Search :- ";
                        std::cin >> Value;

                    if(Value != 0)
                    {
                    iHold = obj1.SearchAllOccurence(Value);
                        if(iHold == -1)
                            {
                                std::cout << "List is Empty...\n";
                                break;
                            }
                        std::cout << "Data Found " << iHold << " Times\n";
                    }
                    break;

                    case 4:
                        iExit = -2;    
                } 
            }
            }
            else
                DisplayIterator(obj1);
                //obj1.Display();
            break;

            case 4:
                    std::cout << ("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    iHold = obj1.CountNode();
                    std::cout << "Count Of Node is " << iHold << std::endl << std::endl;
                break;
            
            case 5:
            iExit = 1;
            iHold = obj1.ListEmpty();
            if(iHold != 1)
            {
                while(iExit != -2)
                {
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "|->1.Reverse Display\n";
                    std::cout << "|->2.Physical Reverse\n";
                    std::cout << "|->3.Back\n";
                    std::cout << "Enter Your Choice :- ";
                    std::cin >> iChoice;

                        if(iChoice > 3)
                        {
                            std::cout << "Your Choice is Wrong...\n";
                            continue;
                        }

                    switch(iChoice)
                    {
                        case 1:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                            obj1.ReverseDisplay();
                            break;
                        case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                            obj1.PhysicalReverse();
                            DisplayIterator(obj1);
                            //obj1.Display();
                            break;
                        case 3:
                            iExit = -2;
                    }
                }
            }
            else
                DisplayIterator(obj1);
                //obj1.Display();
            break;
            
            case 6:     //concat
            iExit = 1;
            while(iExit != -2)
            {
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                std::cout << "|->1.Concat List\n";
                std::cout << "|->2.Concat At Position\n";
                std::cout << "|->3.Back\n";
                std::cout << "Enter Your Choice :- ";
                std::cin >> iChoice;
                
                if(iChoice > 3)
                {
                    std::cout << "Your Choice is Wrong...\n";
                    continue;
                }

                if(iChoice == 2)
                {
                    iPos = obj1.CountNode();
                    
                    while(iPos != -1)
                    {
                        std::cout << "Enter Your Position :- ";
                        std::cin >> iHold;

                    if(iHold <= 0 || iHold > iPos+1)
                    {
                        std::cout << "Position is Invalid\n";
                        continue;
                    }
                    break;
                    }
                }

                switch(iChoice)
                {
                case 1:
                    iExit = 0;
                    iPos = obj2.CountNode();
                    if(iPos == 0)
                    {
                        while(iExit != -1)
                        {
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                            std::cout << "|->  1.Insert First\n";
                            std::cout << "|->  2.Insert Last\n";
                            std::cout << "|->  3.Insert At Position\n";
                            std::cout << "|->  4.Back\n";
                        std::cout << "Enter Your Choice :- ";
                        std::cin >> iChoice;
                        
                        if(iChoice > 4)
                            {
                                std::cout << "Your Choice is Wrong...\n";
                                continue;
                            }
                        switch(iChoice)
                        {
                            case 1:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                std::cout << "\nEnter Your Data :- ";
                                std::cin >> Value;
                                
                                if(Value > 0)
                                {
                                    obj2.InsertFirst(Value);
                                    DisplayIterator(obj2);
                                    //obj2.Display();
                                }
                            break;

                            case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                std::cout << "\nEnter Your Data :- ";
                                std::cin >> Value;
                                
                                if(Value > 0)
                                {
                                    obj2.InsertLast(Value);
                                    DisplayIterator(obj2);
                                    //obj2.Display();
                                }
                                break;

                                case 3:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter inthe Position :- ";
                                    std::cin >> iPos;
            
                                    iExit = obj2.CountNode();
                                    if(iPos < 0 || iPos > iExit+1)
                                    {
                                        std::cout << "Position is invalid\n";
                                        iExit = 0;
                                        continue;
                                    }
                                    iExit = 0;
                                    std::cout << "Enter Your Data :- ";
                                    std::cin >> Value;
                                    
                                    if(Value > 0)
                                    {
                                        obj2.InsertAtPosition(Value , iPos);
                                        DisplayIterator(obj2);
                                        //obj2.Display();
                                    }                                    
                                break;

                                case 4:
                                    iExit = -1;
                            }
                    }        
                obj1.ConcatList(obj2);
                DisplayIterator(obj1);
                //obj1.Display();
                }
                break;
    
                case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                iPos = obj1.CountNode();
                    
                    if(iPos == 0)
                        {
                            std::cout << "Your First List is Empty...\n";
                            break;
                        }
                iPos = obj2.CountNode();
                iExit = 0;
                if(iPos == 0)
                {
                        while(iExit != -1)
                        {
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                            std::cout << "|->  1.Insert First\n";
                            std::cout << "|->  2.Insert Last\n";
                            std::cout << "|->  3.Insert At Position\n";
                            std::cout << "|->  4.Back\n";

                        std::cout << "Enter Your Choice :- ";
                        std::cin >> iChoice;

                            if(iChoice > 4)
                            {
                                std::cout << "Your Choice is Wrong...\n";
                                continue;
                            }        

                        switch(iChoice)
                        {
                            case 1:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter Your Data :- ";
                                    std::cin >> Value;

                                    if(Value > 0)
                                    {
                                        obj2.InsertFirst(Value);
                                        DisplayIterator(obj2);
                                        //obj2.Display();
                                    }
                            break;

                            case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter Your Data :- ";
                                    std::cin >> Value;
                                    
                                    if(Value > 0)
                                    {
                                        obj2.InsertLast(Value);
                                        DisplayIterator(obj2);
                                        //obj2.Display();
                                    }
                                break;

                                case 3:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter In the Position :- ";
                                    std::cin >> iPos;
                                    
                                    iExit = obj2.CountNode();
                                    if(iPos < 0 || iPos > iExit+1)
                                    {
                                        std::cout << "Position is invalid\n";
                                        continue;
                                    }

                                    std::cout << "Enter Your Data :- ";
                                    std::cin >> Value;

                                    if(Value > 0)
                                    {
                                        obj2.InsertAtPosition(Value  , iPos);
                                        //obj2.Display();
                                        DisplayIterator(obj2);
                                    }
                                break;
                                case 4:
                                    iExit = -1;
                        }
                    }        
                    obj1.ConcatAtPosition(obj2 ,iHold);
                    //obj1.Display();
                    DisplayIterator(obj1);

                }
                break;

                case 3:
                    iExit = -2;
                }
            }
            break;

            case 7:
                std::cout << "Exiting....\n";
                iExit = -1;
        }
        break;
    }
    }
    std::cout << obj1 << obj2;
    obj1.DeleteAll();
    obj2.DeleteAll();
    return;
}

template <typename T>
    void DisplayIterator(CList<T> &list)
    {
        //in ubuntu it's need typename.......
        std::cout << "\nIterator display start : Linked list is : \n";
    for(typename CList<T>::iterator iter = list.begin(); iter != list.end() ; ++iter)
        std::cout << "<-|" << *iter << "|->";
        std::cout << std::endl;    
    }