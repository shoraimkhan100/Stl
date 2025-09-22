#include <iostream>

using std::ostream;

class CList;

void DisplayIterator(CList &);

class CNode
{
    CNode *m_pPrev;
    int Data;
    CNode *m_pNext;

    public:
        friend class CList;
        
    friend ostream& operator << (ostream& , CList &);
    
    CNode();
    ~CNode();
};

class CList
{
    CNode *m_pFirst;
    CNode *m_pLast;

    public: 
        void InsertFirst(int);
        void InsertLast(int);
        void InsertAtPosition(int , int);
        int DeleteFirst();
        int DeleteLast();
        int DeleteAtPosition(int);
        int SearchFirstOccurence(int);
        int SearchLastOccurence(int);
        int SearchAllOccurence(int);
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
            CNode *pCurrent;
            
            public:
            iterator()
            {
                pCurrent = NULL;
            }
            ~iterator()
            {
                pCurrent = NULL;
            }

            bool operator ==(iterator &cNode)
            {
                return (pCurrent == cNode.pCurrent);
            }
            bool operator !=(iterator &cNode)
            {
                return (pCurrent != cNode.pCurrent);
            }
            bool operator >=(iterator &cNode)
            {
                return (pCurrent >= cNode.pCurrent);
            }
            bool operator <=(iterator &cNode)
            {
                return (pCurrent <= cNode.pCurrent);
            }

            void set(CNode *pCurr)
            {
                pCurrent = pCurr;
            }

            iterator& operator ++()
            {
                pCurrent = pCurrent->m_pNext;
                return *this;
            }

            iterator operator ++(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->m_pNext;
                return temp;
            }

            iterator& operator --()
            {
                pCurrent = pCurrent->m_pPrev;
                return *this;
            }

            iterator operator --(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->m_pPrev;
                return temp;
            }

            int operator *()
            {
                return pCurrent->Data;
            }

            bool operator <(iterator &cNode)
            {
                return pCurrent < cNode.pCurrent;
            }
            bool operator >(iterator &cNode)
            {
                return pCurrent > cNode.pCurrent;
            }
        };
        private:
        iterator m_Start;
        iterator m_End;
        public:
        iterator& begin()
        {
            m_Start.set(m_pFirst);
            return m_Start;
        }

        iterator& end()
        {
            m_End.set(m_pLast);
            return m_End;
        }
        friend ostream& operator << (ostream &out , CList &);
};

        CNode::CNode()
        {
            m_pPrev = NULL;
            Data = 0;
            m_pNext = NULL;
        }
        CNode::~CNode()
        {
            m_pPrev = NULL;
            Data = 0;
            m_pNext = NULL;
        }

        void CList::InsertFirst(int Value)
        {
            CNode *pNewNode = NULL;

            pNewNode = new CNode;
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

        void CList::InsertLast(int Value)
        {
            CNode *pNewNode = NULL;
    
                pNewNode = new CNode;
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
       
        void CList::InsertAtPosition(int Value , int iPos)
        {
            int iCount = 0;
            CNode *pintemp = NULL;
            CNode *pNewNode = NULL;

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

            pNewNode = new CNode;
            if(NULL == pNewNode)
            {
                std::cout << "Memory Allocation FAILED\n";
                return;
            }
            pNewNode->m_pPrev = NULL;
            pNewNode->Data = Value;
            pNewNode->m_pNext = NULL;

            pintemp = m_pFirst;
            iCount = 1;

            while(iCount < iPos-1)
            {
                pintemp = pintemp->m_pNext;
                iCount++;
            }  
            pNewNode->m_pNext = pintemp->m_pNext;
            pintemp->m_pNext->m_pPrev = pNewNode;
            pintemp->m_pNext = pNewNode;
            pNewNode->m_pPrev = pintemp;
        }

        int CList::DeleteFirst()
        {
            int Value;
    
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
        
        int CList::DeleteLast()
        {
            int Value;
            
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
        
        int CList::DeleteAtPosition(int iPos)
        {
            int Value;
            int iCount;
            CNode *pintemp = NULL;

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
            pintemp = m_pFirst;
            while(iCount < iPos)
            {
                iCount++;
                pintemp = pintemp->m_pNext;
            }
                Value = pintemp->Data;
                pintemp->m_pPrev->m_pNext = pintemp->m_pNext;
                pintemp->m_pNext->m_pPrev = pintemp->m_pPrev;
                pintemp->m_pNext = NULL;
                pintemp->m_pPrev = NULL;
                delete pintemp;
                pintemp = NULL;
            
            return Value;
        }

        int CList::SearchFirstOccurence(int No)
        {
            CNode *pHead = m_pFirst;
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
        
        int CList::SearchLastOccurence(int No)
        {
            int iPos = 0;
            int iRet = 0;
            CNode *pHead = m_pFirst;

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
        
        int CList::SearchAllOccurence(int No)
        { 
            int iPos = 0;
            CNode *pHead = m_pFirst;
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

        int CList::CountNode()
        {
            int iCount = 0;
            CNode *pHead = m_pFirst;
            if(NULL == pHead)
                return 0;
            do
            {
                iCount++;
                pHead = pHead->m_pNext;
            }while(pHead != m_pLast->m_pNext);
            return iCount;
        }

        void CList::ReverseDisplay()
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
        
        void CList::PhysicalReverse()
        {
            CNode *pPre = m_pLast;
            CNode *pCurrent = m_pFirst;
            CNode *m_pNext = NULL;

            if(NULL == m_pFirst)
                return;
            
            while(1)
            {
                m_pNext = pCurrent->m_pNext;
                pCurrent->m_pPrev = m_pNext;
                pCurrent->m_pNext = pPre;
                pPre = pCurrent;

                if(pCurrent == m_pLast)
                    break;
                pCurrent = m_pNext;
            }
            m_pFirst = m_pLast;
            m_pLast = m_pNext;
        }

        void CList::ConcatList(CList &refObj)
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

        void CList::ConcatAtPosition(CList &refObj, int iPos)
        {
           int iCount;
            
            CNode *temp = NULL;

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
            temp = m_pFirst;
            while(iCount < iPos-1)
            {
                temp = temp->m_pNext;
                iCount++;
            }
            refObj.m_pLast->m_pNext = temp->m_pNext;
            refObj.m_pFirst->m_pPrev = temp;
            temp->m_pNext->m_pPrev = refObj.m_pLast;
            temp->m_pNext = refObj.m_pFirst;

            refObj.m_pLast = NULL;
            refObj.m_pFirst = NULL; 
        }

        void CList::Display()
        {
            CNode *pHead = m_pFirst;
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

        void CList::DeleteAll()
        {
            CNode *pintemp = NULL;
            m_pLast->m_pNext = NULL;
            
            while(m_pFirst != NULL)
            {
            pintemp = m_pFirst;
            m_pFirst = pintemp->m_pNext;
            pintemp->m_pNext = NULL;
            pintemp->m_pPrev = NULL;
            delete pintemp;
            }
            pintemp = NULL;
        }

        bool CList::ListEmpty()
        {
            if(NULL == m_pFirst || NULL == m_pLast)
                return true;
            return false;
        }

    ostream& operator << (ostream &out , CList &pLis)
    {
        CNode *pintemp = pLis.m_pFirst;

        if(NULL == pLis.m_pFirst)
        {
            out << "list is Empty...\n";
            return out;
        }
        do
        {
            out << "|" << pintemp->Data << "|->";
            pintemp = pintemp->m_pNext;
        }while(pintemp != pLis.m_pLast->m_pNext);
        std::cout << std::endl;
        return out;
    }

int main(void)
{
    CList obj1;
    CList obj2;
    int iPos = 0;
    int iValue = 0;
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
                                DisplayIterator(obj1);
                                //obj1.Display();
                            }
                    break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";        
                        std::cout << "\nEnter Your Data :- ";
                                std::cin >> iValue;
                                if(iValue > 0)
                                {
                                    obj1.InsertLast(iValue);
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
                                std::cin >> iValue;
                                if(iValue > 0)
                                {
                                    obj1.InsertAtPosition(iValue , iPos);
                                    //obj1.Display();
                                    DisplayIterator(obj1);
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
                        DisplayIterator(obj1);
                        //obj1.Display();
                        break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    iValue = obj1.DeleteLast();
                        if(iValue != -1)
                            std::cout << "Deleted Data is : " << iValue << std::endl;
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
                            iValue = obj1.DeleteAtPosition(iPos);
                            if(iValue != -1)
                                std::cout << "Deleted Data is : " << iValue << std::endl;
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
                    std::cout << "Enter Data into Search :- ";
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
                        std::cout << "Enter Data into Search :- ";
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
                                std::cin >> iValue;
                                
                                if(iValue > 0)
                                {
                                    obj2.InsertFirst(iValue);
                                    DisplayIterator(obj2);
                                    //obj2.Display();
                                }
                            break;

                            case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                std::cout << "\nEnter Your Data :- ";
                                std::cin >> iValue;
                                
                                if(iValue > 0)
                                {
                                    obj2.InsertLast(iValue);
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
                                    std::cin >> iValue;
                                    
                                    if(iValue > 0)
                                    {
                                        obj2.InsertAtPosition(iValue , iPos);
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
                                    std::cin >> iValue;

                                    if(iValue > 0)
                                    {
                                        obj2.InsertFirst(iValue);
                                        DisplayIterator(obj2);
                                        //obj2.Display();
                                    }
                            break;

                            case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter Your Data :- ";
                                    std::cin >> iValue;
                                    
                                    if(iValue > 0)
                                    {
                                        obj2.InsertLast(iValue);
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
                                        continue;
                                    }

                                    std::cout << "Enter Your Data :- ";
                                    std::cin >> iValue;

                                    if(iValue > 0)
                                    {
                                        obj2.InsertAtPosition(iValue  , iPos);
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
                std::cout << "exiting....\n";
                iExit = -1;
        }
        break;
    }
    }
    std::cout << obj1 << obj2;

    return 0;
}

void DisplayIterator(CList &list)
{
    std::cout << "\nIterator siaplay start : Linked list is : \n";
    for (CList::iterator iter = list.begin(); iter != list.end() ; ++iter)
        std::cout << "<-|" << *iter << "|->";
    std::cout << std::endl;    
}