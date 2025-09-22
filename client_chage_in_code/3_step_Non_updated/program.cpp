#include <iostream>

using std::ostream;

class CList;
class iterator;       
void PrintList(CList & , CList &);                                
class CNode
{
    CNode *pPrev;
    int Data;
    CNode *pNext;

public:
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

    friend void splice(iterator& , CList , iterator&);     
    friend ostream& operator << (ostream &out , CList   &);
};

class CList
{
    CNode *pDummy;

public:    
    void InsertFirst(int Value)
    {
        CNode  *pNewNode = NULL;
        pNewNode = new CNode ;

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
    void InsertLast(int Value)
    {
        CNode  *pNewNode = NULL;
        pNewNode = new CNode ;

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
    void InsertAtPosition(int Value , int iPos)
    {
        CNode  *pNewNode = NULL;
        CNode  *pTemp = NULL;
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
        pNewNode = new CNode ;
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
    int DeleteFirst()
    {
        int DelData;

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
    int DeleteLast()
    {
        int DelData;
        CNode  *pTemp = NULL;

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
    int DeleteAtPosition(int iPos)
    {
        int iCount;
        int RetData = 0;
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

        CNode *pTemp = pDummy->pNext;
        
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
    int SearchFirstOccurence(int Value)
    {
        CNode  *pTemp = NULL;
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
    int SearchLastOccurence(int Value)
    {
        CNode  *pTemp = NULL;
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
    int SearchAllOccurence(int Value)
    {
        CNode  *pTemp = NULL;
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

    void ConcatList(CList &refObj)
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
    void ConcatAtPosition(CList &refObj , int iPos)
    {
        int iCount;
        CNode  *pTemp = NULL;

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

    int CountNode()
    {
        int iCount = 1;
        CNode  *pTemp = NULL;
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
    
    void Display()
    {
        CNode  *pTemp = pDummy->pNext;
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

    void PhysicalReverse()
    {
        CNode  *pPre = pDummy->pPrev;
        CNode  *pCurrent = pDummy->pNext;
        CNode  *pNext = NULL;

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
    void ReverseDisplay()
    {
        if(pDummy == pDummy->pNext)
            return;
        PhysicalReverse();
        Display();
        PhysicalReverse();
    }
    void DeleteAll()
    {
        CNode *pTemp = NULL;
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

    bool ListEmpty()
    {
        if(pDummy == pDummy->pNext)
            return 0;
        return 1;
    }
    CList()
    {
        pDummy = NULL;
        pDummy = new CNode ;
        pDummy->pPrev = pDummy;
        pDummy->Data = 0;
        pDummy->pNext = pDummy;
    }
    ~CList()
    {
        if(pDummy->pNext != pDummy) 
            DeleteAll();
    }
    class iterator
        {
            CNode  *pCurrent;
            
            public:
            iterator()
            {
                pCurrent = NULL;
            }
            ~iterator()
            {
                pCurrent = NULL;
            } 
            CNode* Get_Current()
            {
                return pCurrent;
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

            void set(CNode  *pCurr)
            {
                pCurrent = pCurr;
            }

            iterator& operator ++()
            {
                pCurrent = pCurrent->pNext;
                return *this;
            }

            iterator operator ++(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->pNext;
                return temp;
            }

            iterator& operator --()
            {
                pCurrent = pCurrent->pPrev;
                return *this;
            }

            iterator operator --(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->pPrev;
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
            m_Start.set(pDummy->pNext);
            return m_Start;
        }

        iterator& end()
        {
            m_End.set(pDummy);
            return m_End;
        }
        void push_back(int iGet)
        {
            InsertLast(iGet);
        }
        void push_front(int iGet)
        {
            InsertFirst(iGet);
        }
        iterator find(iterator Ci_Begin,iterator Ci_End,int iData)
        {
           iterator iter = Ci_Begin;
            
            while(Ci_End != iter)
            {
                if(*iter == iData)
                    return iter;
                ++iter;
            }
            if(*Ci_End == iData)
                return Ci_End;
            return Ci_Begin;
        }
    void splice(iterator Destination , CList &SourcePosition)
    {
        
        CNode *pDestination = Destination.Get_Current();
                
        pDestination->pPrev->pNext = SourcePosition.pDummy->pNext;
        SourcePosition.pDummy->pPrev->pNext = pDestination;
        pDestination->pPrev = SourcePosition.pDummy->pPrev;

        SourcePosition.pDummy->pNext = SourcePosition.pDummy;
        SourcePosition.pDummy->pPrev = SourcePosition.pDummy;
    }
    void splice(iterator Destination,CList &SourceList , iterator SourcePosition)
    {    
        CNode *pDestination = Destination.Get_Current();
        CNode *pSourcePosition = SourcePosition.Get_Current();
        
        pSourcePosition->pPrev->pNext = pSourcePosition->pNext;
        pSourcePosition->pNext->pPrev = pSourcePosition->pPrev;
        pSourcePosition->pNext = pDestination;
        pSourcePosition->pPrev = pDestination->pPrev;
        pDestination->pPrev->pNext = pSourcePosition;
        pDestination->pPrev = pSourcePosition;
    } 
    CList& operator =(CList &cList)
    {
        CNode *pTemp = NULL;
        CNode *pTemp2 = NULL;
        CNode *pNewNode = NULL;
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
                        pNewNode = new CNode;
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
        CNode *pTemp = NULL;
        CNode *pDelete = NULL;

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
        
            CNode *pTemp = NULL;
            int iData;
            CNode *pCheck = NULL;

            
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
    friend ostream& operator << (ostream &out , CList &);
};

 
ostream& operator << (ostream &out , CList  &pLis)
    {  
        CNode *pTemp = pLis.pDummy->pNext;

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
void DisplayIterator(CList &);
//void My_Main(T);
/*int main(void)
{
    int iChoice = 0;
    while(iChoice != -1)
    {
    std::cout << "|->1.Integer\n|->2.float\n|->3.char\n|->4.double\n|->5.Exit\n\n";
    std::cout << "Enter Your Choice";
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
        iChoice = -1;
    }
    }
    return 0;
}
template <typename T>
*/
int main(void)
{
    CList obj1;
    CList obj2;
    int iPos = 0;
    int Value = 0;
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
                            std::cin >> Value;
                            if(Value > 0)
                            {
                                obj1.InsertFirst(Value);
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
                            std::cout << "Position of Data is " << iHold << std::endl;
                    }    
                    break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "Enter Data to Search :- ";
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
                            std::cout << "Position of Data is " << iHold << std::endl;
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
                                    std::cout << "\nEnter inthe Position :- ";
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
                std::cout << "exiting....\n";
                iExit = -1;
        }
        break;
    }
    }
    std::cout << obj1 << obj2;
    std::cout << "\t------------------------------------------ before pushing ------------------------------------------ \n\n";
    for(iHold = 0 ; iHold < 6 ; iHold++)
    {
        obj1.push_back(iHold+65);
        obj2.push_front(iHold+65);
    }
    std::cout << "\t------------------------------------------ after pushing ------------------------------------------ \n\n";

    PrintList(obj1,obj2);

    
    std::cout << "\t------------------------------------------  before splice 2 param ------------------------------------------ \n\n";
    obj2.splice(obj2.find(obj2.begin(),obj2.end(),69),obj1);
    
    std::cout << "\t------------------------------------------  After splice 2 param ------------------------------------------ \n\n";

    PrintList(obj1,obj2);

    std::cout << "\t------------------------------------------ Before splice 3 param ------------------------------------------ \n\n";
    // move first element of obj2 to the end
    obj2.splice(
        obj2.end(),     // destination position
        obj2,           // source list
        obj2.begin()    // source position
                );   
    std::cout << "\t------------------------------------------ After Splice 3 parameter ------------------------------------------ \n\n";

    PrintList(obj1,obj2);

    std::cout << "\t------------------------------------------ before shorting ------------------------------------------ \n\n";
    // sort second list, assign to obj1 and remove dupicates
    obj2.sort();
    std::cout << "\t------------------------------------------ After shorting ------------------------------------------ \n\n";

    PrintList(obj1,obj2);

    std::cout << "\t------------------------------------------ Before = operator ------------------------------------------ \n\n";
    obj1 = obj2;
    std::cout << "\t------------------------------------------ after = operator ------------------------------------------ \n\n";
    PrintList(obj1,obj2);

    std::cout << "\t------------------------------------------ before unique ------------------------------------------ \n\n";
    obj2.unique();
    std::cout << "\t------------------------------------------ After unique ------------------------------------------ \n\n";

    PrintList(obj1,obj2);
    /**/

    // merge both sorted lists into the first list
    std::cout << "\t------------------------------------------ before merge------------------------------------------" << std::endl << std::endl;
    PrintList(obj1,obj2);
    obj1.merge(obj2);
    std::cout << "\t------------------------------------------ After merge ------------------------------------------" << std::endl << std::endl;
    PrintList(obj1,obj2);
    obj1.DeleteAll();
    obj2.DeleteAll();
    PrintList(obj1,obj2);
    std::cout << "Successfly..\n";

    return 0;
}
void PrintList(CList &obj1 , CList &obj2)
{
    std::cout << "list 1 :  " << obj1 << std::endl << "list 2 : " << obj2 << std::endl << std::endl;
}
    void DisplayIterator(CList &list)
    {
        std::cout << "\nIterator siaplay start : Linked list is : \n";
    for(CList::iterator iter = list.begin(); iter != list.end() ; ++iter)
        std::cout << "<-|" << *iter << "|->";
        std::cout << std::endl;    
    }