#include <iostream>

using std::ostream;

template <typename T>
class CList;

template <typename T>
void My_Main(T No);
template <typename T>
void DisplayIterator(CList<T>);

template <typename T>
class CNode
{
    CNode *m_pPrev;
    T Data;
    CNode *m_pNext;

    public:
    template <typename T1>
        friend class CList;
    
    template <typename T2>    
    friend ostream& operator << (ostream& , CList<T2> &);
    //friend void DisplayIterator(CList &);   
    
    CNode();
    ~CNode();
};

template <typename T>
class CList
{
    CNode<T> *m_pFirst;
    CNode<T> *m_pLast;

    template <typename T3>
    class iterator;
    
    iterator<T> *m_Start;
    iterator<T> *m_End;
    
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
        void ConcatAtPosition(CList & , int);
        void Display();
        void DeleteAll();
        bool ListEmpty();
        
        CList()
        {
            m_pFirst = NULL;
            m_pLast = NULL;
        }
        
        ~CList()
        {
            if(m_pFirst != NULL)
                DeleteAll();
            m_pFirst = NULL;
            m_pLast = NULL;
        }

        class iterator
        {
            CNode<T3> *pCurrent;
            public:
             
                /*
                iterator();
                bool operator ==(iterator);
                bool operator !=(iterator);
                bool operator <=(iterator);
                bool operator >=(iterator);

                iterator& operator ++(iterator &);
                iterator operator ++(iterator & , int);

                iterator& operator --(iterator &);
                iterator operator --(iterator & , int);

                iterator operator *();

                void begin();
                void end();
                void set(CNode<T> *);
                */
            iterator()
            {
                pCurrent = NULL;
                begin();
            }

            void begin()
            {
                m_Start.set(pCurrent);
            }

            void end()
            {
                m_End.set(pCurrent);
            }

            bool operator ==(iterator cNode)
            {
                return (pCurrent == cNode.pCurrent)
            }
            bool operator !=(iterator cNode)
            {
                return (pCurrent != cNode.pCurrent)
            }
            bool operator >=(iterator cNode)
            {
                return (pCurrent >= cNode.pCurrent)
            }
            bool operator <=(iterator cNode)
            {
                return (pCurrent <= cNode.pCurrent)
            }

            void set(CNode<T3> *pCurr)
            {
                pCurrent = pCurr;
            }

            iterator& operator ++(iterator &cNode)
            {
                cNode = cNode->pNext;
                return *this;
            }

            iterator operator ++(iterator &cNode,int)
            {
                iterator *pTemp = pCurrent;
                cNode = cNode->pNext;
                return pTemp;
            }

            iterator& operator --(iterator &cNode)
            {
                cNode = cNode->pPrev;
                return *this;
            }

            iterator operator --(iterator &cNode,int)
            {
                iterator *pTemp = pCurrent;
                cNode = cNode->pPrev;
                return pTemp;
            }

            iterator operator *()
            {
                return (pCurrent->Data);
            }
        };
        friend void DisplayIterator(CList &);  
        template <typename T2>
        friend ostream& operator << (ostream &out , CList<T2> &);
};

        template <typename T>
        CNode<T>::CNode()
        {
            m_pPrev = NULL;
            Data = 0;
            m_pNext = NULL;
        }
        template <typename T>
        CNode<T>::~CNode()
        {
            m_pPrev = NULL;
            Data = 0;
            m_pNext = NULL;
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

            pNewNode->Data = Value;

            if(NULL == m_pFirst)
            {
                m_pFirst = pNewNode;
                m_pLast = pNewNode;
                m_pFirst->m_pNext = m_pFirst;
                m_pFirst->m_pPrev = m_pLast;
                return;
            }

            pNewNode->m_pNext = m_pFirst;
            pNewNode->m_pPrev = m_pLast;
            m_pFirst->m_pPrev = pNewNode;
            m_pFirst = pNewNode;
            m_pLast->m_pNext = m_pFirst;
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

                pNewNode->m_pPrev = NULL;
                pNewNode->Data = Value;
                pNewNode->m_pNext = NULL;

                if(NULL == m_pFirst)
                {
                    m_pLast = pNewNode;
                    m_pFirst = pNewNode;
                    pNewNode->m_pNext = m_pFirst;
                    pNewNode->m_pPrev = m_pLast;
                }
                pNewNode->m_pNext = m_pFirst;
                pNewNode->m_pPrev = m_pLast;
                m_pLast->m_pNext = pNewNode;
                m_pLast = pNewNode;
                m_pFirst->m_pPrev = m_pLast;
        }
       
        template <typename T>
        void CList<T>::InsertAtPosition(T Value , int iPos)
        {
            int iCount = 0;
            CNode<T> *pTemp = NULL;
            CNode<T> *pNewNode = NULL;

            iCount = CountNode();

            if(iPos <= 0 || iPos > iCount+1)
            {
                std::cout << "Position is Invalid\n";
                return;
            }

            if(1 == iPos)
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
            pNewNode->m_pPrev = NULL;
            pNewNode->Data = Value;
            pNewNode->m_pNext = NULL;

            pTemp = m_pFirst;
            iCount = 1;

            while(iCount < iPos-1)
            {
                pTemp = pTemp->m_pNext;
                iCount++;
            }  
            pNewNode->m_pNext = pTemp->m_pNext;
            pTemp->m_pNext->m_pPrev = pNewNode;
            pTemp->m_pNext = pNewNode;
            pNewNode->m_pPrev = pTemp;
        }

        template <typename T>
        T CList<T>::DeleteFirst()
        {
            T Value;
    
            if(NULL == m_pFirst)
                return -1;

            Value = m_pFirst->Data;

            if(m_pFirst == m_pLast)
            {
                m_pFirst->m_pNext = NULL;
                m_pLast->m_pPrev = NULL;
                delete m_pFirst;
                m_pFirst = NULL;
                m_pLast = NULL;
                return Value;
            }
            m_pFirst = m_pFirst->m_pNext;
            m_pFirst->m_pPrev->m_pNext = NULL;
            m_pFirst->m_pPrev->m_pPrev = NULL;
            m_pLast->m_pNext = m_pFirst;

            delete m_pFirst->m_pPrev;
            m_pFirst->m_pPrev = m_pLast;    
            return Value;
        }
        
        template <typename T>
        T CList<T>::DeleteLast()
        {
            T Value;
            
            if(NULL == m_pLast)
                return -1;

            Value = m_pLast->Data;

            if(m_pFirst == m_pLast)
            {
                m_pFirst->m_pNext = NULL;
                m_pLast->m_pPrev = NULL;
                delete m_pLast;
                m_pLast = NULL;
                m_pFirst = NULL;
                return Value;
            }
            m_pLast = m_pLast->m_pPrev;
            m_pLast->m_pNext->m_pNext = NULL;
            m_pLast->m_pNext->m_pPrev = NULL;
            m_pFirst->m_pPrev = m_pLast;

            delete m_pLast->m_pNext;
            m_pLast->m_pNext = m_pFirst;
            
            return Value;
        }
        
        template <typename T>
        T CList<T>::DeleteAtPosition(int iPos)
        {
            T Value;
            int iCount;
            CNode<T> *pTemp = NULL;

            iCount = CountNode();

            if(iPos <= 0 || iPos > iCount)
            {
                std::cout << iPos << " Position is Invalid\n";
                return iPos;
            }

            if(1 == iPos)
            {
                Value = DeleteFirst();
                return Value;
            }
            if(iPos == iCount)
            {
                Value = DeleteLast();
                return Value;
            }

            iCount = 1;
            pTemp = m_pFirst;
            while(iCount < iPos)
            {
                iCount++;
                pTemp = pTemp->m_pNext;
            }
                Value = pTemp->Data;
                pTemp->m_pPrev->m_pNext = pTemp->m_pNext;
                pTemp->m_pNext->m_pPrev = pTemp->m_pPrev;
                pTemp->m_pNext = NULL;
                pTemp->m_pPrev = NULL;
                delete pTemp;
                pTemp = NULL;
            
            return Value;
        }

        template <typename T>
        int CList<T>::SearchFirstOccurence(T No)
        {
            CNode<T> *pHead = m_pFirst;
            int iPos = 0;
            if(NULL == pHead)
                return -1;
            do
            {
                iPos++;
                if(pHead->Data == No)
                    return iPos;
                pHead = pHead->m_pNext;     
            }while(pHead != m_pLast->m_pNext);
            return 0;
        }
        
        template <typename T>
        int CList<T>::SearchLastOccurence(T No)
        {
            int iPos = 0;
            int iRet = 0;
            CNode<T> *pHead = m_pFirst;

            if(NULL == pHead)
                return -1;
            do
            {
                iPos++;
                if(pHead->Data == No)
                    iRet = iPos;
                pHead = pHead->m_pNext;     
            }while(pHead != m_pLast->m_pNext);
                return iRet;
        }
        
        template <typename T>
        int CList<T>::SearchAllOccurence(T No)
        { 
            int iPos = 0;
            CNode<T> *pHead = m_pFirst;
            if(NULL == pHead)
                return -1;
            do
            {
                if(pHead->Data == No)
                    iPos++;
                pHead = pHead->m_pNext;
            } while(pHead != m_pLast->m_pNext);
            if(iPos != 0)
                return iPos;
            return 0;   
        }

        template <typename T>
        int CList<T>::CountNode()
        {
            int iCount = 0;
            CNode<T> *pHead = m_pFirst;
            if(NULL == pHead)
                return 0;
            do
            {
                iCount++;
                pHead = pHead->m_pNext;
            }while(pHead != m_pLast->m_pNext);
            return iCount;
        }

        template <typename T>
        void CList<T>::ReverseDisplay()
        {
            if(NULL == m_pFirst)
            {
                std::cout << "List is Empty..\n";
                return;
            }

            PhysicalReverse();
            Display();
            PhysicalReverse();
        }
        
        template <typename T>
        void CList<T>::PhysicalReverse()
        {
            CNode<T> *pPre = m_pLast;
            CNode<T> *pCurrent = m_pFirst;
            CNode<T> *pNext = NULL;

            if(NULL == m_pFirst)
                return;
            
            while(1)
            {
                pNext = pCurrent->m_pNext;
                pCurrent->m_pPrev = pNext;
                pCurrent->m_pNext = pPre;
                pPre = pCurrent;

                if(pCurrent == m_pLast)
                    break;
                pCurrent = pNext;
            }
            m_pFirst = m_pLast;
            m_pLast = pNext;
        }

        template <typename T>
        void CList<T>::ConcatList(CList &refObj)
        {
            if(refObj.m_pFirst == NULL)
            {
                return;
            }

            if(m_pFirst == NULL)
            {
                //3rd case
                m_pFirst = refObj.m_pFirst;
                m_pLast = refObj.m_pLast;
                // concat
            }
            else
            {
                // case 4
                m_pLast->m_pNext = refObj.m_pFirst;
                refObj.m_pFirst->m_pPrev = m_pLast;
                refObj.m_pLast->m_pNext = m_pFirst;
                m_pFirst->m_pPrev = refObj.m_pLast;
                m_pLast = refObj.m_pLast;
            }

            refObj.m_pLast = NULL;
            refObj.m_pFirst = NULL;        
        }

        template <typename T>
        void CList<T>::ConcatAtPosition(CList &refObj, int iPos)
        {
           int iCount;
            
            CNode<T> *pTemp = NULL;

            iCount = CountNode();

            if(iPos <= 0 || iPos > iCount+1)
            {
                std::cout << "Position is invalid\n";
                return;
            }

            if(NULL == refObj.m_pFirst)
                return;

            if(1 == iPos)
            {   
                refObj.m_pLast->m_pNext = this->m_pFirst;
                refObj.m_pFirst->m_pPrev = this->m_pLast;
                this->m_pFirst->m_pPrev = refObj.m_pLast;
                this->m_pLast->m_pNext = refObj.m_pFirst;

                this->m_pFirst = refObj.m_pFirst;
                refObj.m_pFirst = refObj.m_pLast = NULL;
                return;
            }

            if(iPos == iCount+1)
            {
                ConcatList(refObj);
                return;
            }
            
            iCount = 1;
            pTemp = m_pFirst;
            while(iCount < iPos-1)
            {
                pTemp = pTemp->m_pNext;
                iCount++;
            }
            refObj.m_pLast->m_pNext = pTemp->m_pNext;
            refObj.m_pFirst->m_pPrev = pTemp;
            pTemp->m_pNext->m_pPrev = refObj.m_pLast;
            pTemp->m_pNext = refObj.m_pFirst;

            refObj.m_pLast = NULL;
            refObj.m_pFirst = NULL; 
        }

        template <typename T>
        void CList<T>::Display()
        {
            CNode<T> *pHead = m_pFirst;
            if(NULL == pHead)
            {
                std::cout << "List is empty...\n";
                return;
            }
            do
            {
                std::cout << "|" << pHead->Data << "|->";
                pHead = pHead->m_pNext;
            } while(pHead != m_pLast->m_pNext);
            std::cout << std::endl;
        }

        template <typename T>
        void CList<T>::DeleteAll()
        {
            CNode<T> *pTemp = NULL;
            m_pLast->m_pNext = NULL;
            
            while(m_pFirst != NULL)
            {
            pTemp = m_pFirst;
            m_pFirst = pTemp->m_pNext;
            pTemp->m_pNext = NULL;
            pTemp->m_pPrev = NULL;
            delete pTemp;
            }
            pTemp = NULL;
        }

        template <typename T>
        bool CList<T>::ListEmpty()
        {
            if(NULL == m_pFirst || NULL == m_pLast)
                return true;
            return false;
        }

    template <typename T2>
    ostream& operator << (ostream &out , CList<T2> &pLis)
    {
        CNode<T2> *pTemp = pLis.m_pFirst;

        if(NULL == pLis.m_pFirst)
        {
            out << "list is Empty...\n";
            return out;
        }
        do
        {
            out << "|" << pTemp->Data << "|->";
            pTemp = pTemp->m_pNext;
        }while(pTemp != pLis.m_pLast->m_pNext);
        std::cout << std::endl;
        return out;
    }

int main(void)
{   
    int iChoice;

    while(iChoice != -1)
    {
        std::cout << "\n\n|\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\||\\|\n\n";
        std::cout << "|->1.Integer\n" << "|->2.Float\n" << "|->3.Char\n" << "|->4.Double\n" << "|->5.Exit\n";
        std::cout << "Enter Your Choice :- ";
        std::cin >> iChoice;

        if(iChoice > 5)
        {
            std::cout << "Wrong Choice\n";
            continue;
        }
        switch(iChoice)
        {
            case 1:
                My_Main<int>(10);
                break;
            case 2:
                My_Main<float>(43.33f);
                break;
            case 3:
                My_Main<char>('A');
                break;
            case 4:
                My_Main<double>(49.44);
                break;
            case 5:
                iChoice = -1;
        }
    }

    return 0;
}

template <typename T>
void My_Main(T No)
{
    CList<T> obj1;
    CList<T> obj2;
    int iPos = 0;
    T iValue = 0;
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
                std::cout << "|->  7.Exit\n";
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
                            std::cin >> iValue;
                            if(iValue > 0)
                            {
                                obj1.InsertFirst(iValue);
                                obj1.Display();
                            }
                    break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";        
                        std::cout << "\nEnter Your Data :- ";
                                std::cin >> iValue;
                                if(iValue > 0)
                                {
                                    obj1.InsertLast(iValue);
                                    obj1.Display();
                                }
                        break;

                        case 3:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        std::cout << "\nEnter The Position :- ";
                                std::cin >> iPos;
                                iHold = obj1.CountNode();
                                if(iPos < 0 || iPos > iHold+1)
                                {
                                    std::cout << ("Position is invalid\n");
                                    continue;
                                }
                                std::cout << "Enter Your Data :- ";
                                std::cin >> iValue;
                                if(iValue > 0)
                                {
                                    obj1.InsertAtPosition(iValue , iPos);
                                    obj1.Display();
                                }
                            break;
                        case 4:
                            iExit = -2;
                    }
                }
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
                        iValue = obj1.DeleteFirst();
                        if(iValue != -1)
                            std::cout << "Deleted Data is " << iValue << std::endl;
                        else    
                            break;
                        obj1.Display();
                        break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    iValue = obj1.DeleteLast();
                        if(iValue != -1)
                            std::cout << "Deleted Data is : " << iValue << std::endl;
                        else
                            break;
                        obj1.Display();
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
                            iValue = obj1.DeleteAtPosition(iPos);
                            if(iValue != -1)
                                std::cout << "Deleted Data is : " << iValue << std::endl;
                            obj1.Display();
                        break;

                    case 4:
                        iExit = -2;
                    }
                }
            }
            else
                obj1.Display();
            break;
            
            case 3:  
            iExit = 1;  
            iHold = obj1.ListEmpty();
            if(iHold != 1)
            {
            while(iExit != -2)
            {
            std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                std::cout << "|->1.Seach First Occurence\n";
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
                    std::cout << "Enter Data To Search :- ";
                    std::cin >> iValue;
     
                    if(iValue != 0)
                    {
                    iHold = obj1.SearchFirstOccurence(iValue);
                        if(iHold == -1)
                        {
                            std::cout << "List is Empty..\n";
                            break;
                        }
                        if(iHold == 0)
                            std::cout << "Data Not Found\n";
                        else
                            std::cout << "Position of Data is " << iHold << std::endl;
                    }    
                    break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "Enter Data to Search :- ";
                    std::cin >> iValue;

                    if(iValue != 0)
                    {
                    iHold = obj1.SearchLastOccurence(iValue);
                        if(iHold == -1)
                        {
                            std::cout << "List is Empty...\n";
                            break;
                        }
                        if(iHold == 0)
                            std::cout << "Data Not Found\n";
                        else
                            std::cout << "Position of Data is " << iHold << std::endl;
                    }     
                    break;

                    case 3:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        std::cout << "Enter Data To Search :- ";
                        std::cin >> iValue;

                    if(iValue != 0)
                    {
                    iHold = obj1.SearchAllOccurence(iValue);
                        if(iHold == -1)
                            {
                                std::cout << "List is Empty...\n";
                                break;
                            }
                        std::cout << "Data Found " << iHold << "times\n";
                    }
                    break;

                    case 4:
                        iExit = -2;    
                } 
            }
            }
            else
                obj1.Display();
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
                            obj1.Display();
                            break;
                        case 3:
                            iExit = -2;
                    }
                }
            }
            else
                obj1.Display();
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
                                std::cin >> iValue;
                                
                                if(iValue > 0)
                                {
                                    obj2.InsertFirst(iValue);
                                    obj2.Display();
                                }
                            break;

                            case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                std::cout << "\nEnter Your Data :- ";
                                std::cin >> iValue;
                                
                                if(iValue > 0)
                                {
                                    obj2.InsertLast(iValue);
                                    obj2.Display();
                                }
                                break;

                                case 3:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter The Position :- ";
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
                                    std::cin >> iValue;
                                    
                                    if(iValue > 0)
                                    {
                                        obj2.InsertAtPosition(iValue , iPos);
                                        obj2.Display();
                                    }                                    
                                break;

                                case 4:
                                    iExit = -1;
                            }
                    }        
                obj1.ConcatList(obj2);
                obj1.Display();
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
                                    std::cin >> iValue;

                                    if(iValue > 0)
                                    {
                                        obj2.InsertFirst(iValue);
                                        obj2.Display();
                                    }
                            break;

                            case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter Your Data :- ";
                                    std::cin >> iValue;
                                    
                                    if(iValue > 0)
                                    {
                                        obj2.InsertLast(iValue);
                                        obj2.Display();
                                    }
                                break;

                                case 3:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter The Position :- ";
                                    std::cin >> iPos;
                                    
                                    iExit = obj2.CountNode();
                                    if(iPos < 0 || iPos > iExit+1)
                                    {
                                        std::cout << "Position is invalid\n";
                                        continue;
                                    }

                                    std::cout << "Enter Your Data :- ";
                                    std::cin >> iValue;

                                    if(iValue > 0)
                                    {
                                        obj2.InsertAtPosition(iValue  , iPos);
                                        obj2.Display();
                                    }
                                break;
                                case 4:
                                    iExit = -1;
                        }
                    }        
                    obj1.ConcatAtPosition(obj2 ,iHold);
                    obj1.Display();
                }
                break;

                case 3:
                    iExit = -2;
                }
            }
            break;

            case 7:
                std::cout << "exiting....\n";
                iExit = -1;
        }
        break;
    }
    }
    std::cout << obj1 << obj2;
}

template <typename T4>
friend void DisplayIterator(CList<T4> &list)
{
    std::cout << "\nIterator siaplay start : Linked list is : \n";
    for (CList<T4>::iterator iter = list.begin(); iter != list.end ; ++iter)
        std::cout << "<-|" << *iter << "|->";
    std::cout << std::endl;    
}