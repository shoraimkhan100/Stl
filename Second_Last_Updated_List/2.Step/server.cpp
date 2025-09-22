#include <iostream>
#include "header.h"

using std::ostream;

    CNode::CNode()
    {
        pPrev = NULL;
        pNext = NULL;
    }
    CNode::~CNode()
    {
        pPrev = NULL;
        pNext = NULL;
    }
    
    void CList::InsertFirst(int iValue)
    {
        CNode *pNewNode = NULL;
        pNewNode = new CNode;

        if(NULL == pNewNode)
        {
            std::cout << "Memory Allocation FAILED\n";
            return;
        }
        pNewNode->pPrev = NULL;
        pNewNode->iData = iValue;
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
    void CList::InsertLast(int iValue)
    {
        CNode *pNewNode = NULL;
        pNewNode = new CNode;

        if(NULL == pNewNode)
        {
            std::cout << "Memory Allocation FAILED\n";
            return;
        }
        pNewNode->pPrev = NULL;
        pNewNode->iData = iValue;
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
    void CList::InsertAtPosition(int iValue , int iPos)
    {
        CNode *pNewNode = NULL;
        CNode *pTemp = NULL;
        int iCount = 0;
        iCount = CountNode();

        if(iPos <= 0 || iPos > iCount+1)
        {
            std::cout << "Position is Invalid\n";
            return;
        }
        if(iPos == 1)
        {
            InsertFirst(iValue);
            return;
        }
        if(iPos == iCount+1)
        {
            InsertLast(iValue);
            return;
        }
        pNewNode = new CNode;
        if(NULL == pNewNode)
        {
            std::cout << "Memory Allocation FAILED\n";
            return;
        }
        pNewNode->pPrev = NULL;
        pNewNode->iData = iValue;
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
    int CList::DeleteFirst()
    {
        int iDelData;

        if(pDummy == pDummy->pNext)
            return -1;

        iDelData = pDummy->pNext->iData;
        if(pDummy == pDummy->pNext->pNext)
        {
            pDummy->pNext->pNext = NULL;
            pDummy->pNext->pPrev = NULL;
            delete pDummy->pNext;
            pDummy->pNext = pDummy;
            pDummy->pPrev = pDummy;
            return iDelData;
        }
            pDummy->pNext = pDummy->pNext->pNext;
            pDummy->pNext->pPrev->pNext = NULL;
            pDummy->pNext->pPrev->pPrev = NULL;
            delete (pDummy->pNext->pPrev);
            pDummy->pNext->pPrev = pDummy;
        return iDelData;
    }
    int CList::DeleteLast()
    {
        int iDelData;
        CNode *pTemp = NULL;

        if(pDummy == pDummy->pNext)
            return -1;
        iDelData = pDummy->pPrev->iData;

        if(pDummy == pDummy->pNext->pNext)
        {
            pDummy->pNext->pNext = NULL;
            pDummy->pNext->pPrev = NULL;
            delete pDummy->pPrev;
            pDummy->pNext = pDummy;
            pDummy->pPrev = pDummy;
            return iDelData;
        }
        pTemp = pDummy->pPrev;
        pDummy->pPrev->pPrev->pNext = pDummy;
        pDummy->pPrev = pDummy->pPrev->pPrev;
        pTemp->pNext = NULL;
        pTemp->pPrev = NULL;
        delete pTemp;
        pTemp = NULL;
        return iDelData;
    }
    int CList::DeleteAtPosition(int iPos)
    {
        int iCount;
        
        iCount = CountNode();

        if(iPos <= 0 || iPos > iCount+1)
        {
            std::cout << "Position is Invalid\n";
            return -1;
        }

        if(iPos == 1)
        {
            iCount = DeleteFirst();
            return iCount;
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
        std::cout << "Value is " << pTemp->iData << std::endl;
        std::cout << "Value is " << pTemp->pPrev->iData << std::endl;

        pTemp->pPrev->pNext = pTemp->pNext;
        pTemp->pNext->pPrev = pTemp->pPrev;
        iCount = pTemp->iData;

        pTemp->pNext = NULL;
        pTemp->pPrev = NULL;
        delete pTemp;
        pTemp = NULL;
        return iCount;
    }

    int CList::SearchFirstOccurence(int iValue)
    {
        CNode *pTemp = NULL;
        int iPos = 0;
        if(pDummy == pDummy->pNext)
            return -1;
        pTemp = pDummy->pNext;
        do
        {
            iPos++;
            if(pTemp->iData == iValue)
                return iPos;
            pTemp = pTemp->pNext;
        }
        while(pDummy != pTemp);
        return 0;
    }

    int CList::SearchLastOccurence(int iValue)
    {
        CNode *pTemp = NULL;
        int iPos = 0;
        int iCount = 0;
        if(pDummy == pDummy->pNext)
            return -1;
        pTemp = pDummy->pNext;
        do
        {
            iCount++;
            if(pTemp->iData == iValue)
                iPos = iCount;
            pTemp = pTemp->pNext;
        }while(pDummy != pTemp);
        if(iPos != 0)
            return iPos;
        return 0;
    }
    int CList::SearchAllOccurence(int iValue)
    {
        CNode *pTemp = NULL;
        int iPos = 0;
        if(pDummy == pDummy->pNext)
            return -1;
        pTemp = pDummy->pNext;
        do
        {
            if(pTemp->iData == iValue)
                iPos++;
            pTemp=pTemp->pNext;
        }while(pDummy != pTemp);
        return iPos;
    }

    void CList::ConcatList(CList &refObj)
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
    void CList::ConcatAtPosition(CList &refObj , int iPos)
    {
        int iCount;
        CNode *pTemp = NULL;

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

    int CList::CountNode()
    {
        int iCount = 1;
        CNode *pTemp = NULL;
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
    
    void CList::Display()
    {
        CNode *pTemp = pDummy->pNext;
        if(pDummy == pDummy->pNext)
        {
            std::cout << "List is Empty...\n";
            return;
        }
        do{
            std::cout << "|" << pTemp->iData << "|->";
            pTemp = pTemp->pNext;
        }while(pDummy != pTemp);
        std::cout << std::endl;
    }

    void CList::PhysicalReverse()
    {
        CNode *pPre = pDummy->pPrev;
        CNode *pCurrent = pDummy->pNext;
        CNode *pNext = NULL;

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
    void CList::ReverseDisplay()
    {
        if(pDummy == pDummy->pNext)
            return;
        PhysicalReverse();
        Display();
        PhysicalReverse();
    }
    void CList::DeleteAll()
    {
        CNode *pTemp = NULL;
        pDummy->pNext->pPrev = NULL;
        pDummy->pPrev->pNext = NULL;
        
        while(pDummy != pDummy->pNext)
        {
            pTemp = pDummy->pNext;
            if(pTemp->pNext == NULL)
                break;
            pDummy->pNext = pTemp->pNext;
            pTemp->pNext = NULL;
            pTemp->pPrev = NULL;
            delete pTemp;
        }
        pDummy->pNext = pDummy;
        pDummy->pPrev = pDummy;
        pTemp = NULL;
    }

    bool CList::ListEmpty()
    {
        if(pDummy == pDummy->pNext)
            return true;
        return false;
    }
    CList::CList()
    {
        pDummy = NULL;
        pDummy = new CNode;
        pDummy->pPrev = pDummy;
        pDummy->iData = 0;
        pDummy->pNext = pDummy;
    }
    CList::~CList()
    {
        delete pDummy;
        pDummy = NULL;
    }
            CList::iterator::iterator()
            {
                pCurrent = NULL;
            }
            CList::iterator::~iterator()
            {
                pCurrent = NULL;
            }

            bool CList::iterator::operator ==(iterator &cNode)
            {
                return (pCurrent == cNode.pCurrent);
            }
            bool CList::iterator::operator !=(iterator &cNode)
            {
                return (pCurrent != cNode.pCurrent);
            }
            bool CList::iterator::operator >=(iterator &cNode)
            {
                return (pCurrent >= cNode.pCurrent);
            }
            bool CList::iterator::operator <=(iterator &cNode)
            {
                return (pCurrent <= cNode.pCurrent);
            }

            void CList::iterator::set(CNode *pCurr)
            {
                pCurrent = pCurr;
            }

            CList::iterator& CList::iterator::operator ++()
            {
                pCurrent = pCurrent->pNext;
                return *this;
            }

            CList::iterator CList::iterator::operator ++(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->pNext;
                return temp;
            }

            CList::iterator& CList::iterator::operator --()
            {
                pCurrent = pCurrent->pPrev;
                return *this;
            }

            CList::iterator CList::iterator::operator --(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->pPrev;
                return temp;
            }

            int CList::iterator::operator *()
            {
                return pCurrent->iData;
            }

            bool CList::iterator::operator <(iterator &cNode)
            {
                return pCurrent < cNode.pCurrent;
            }
            bool CList::iterator::operator >(iterator &cNode)
            {
                return pCurrent > cNode.pCurrent;
            }
        CList::iterator& CList::begin()
        {
            m_Start.set(pDummy->pNext);
            return m_Start;
        }

        CList::iterator& CList::end()
        {
            m_End.set(pDummy);
            return m_End;
        }

ostream& operator << (ostream &out , CList &pLis)
    {
        CNode *pTemp = pLis.pDummy->pNext;

        if(pLis.pDummy == pLis.pDummy->pNext)
        {
            out << "List is Empty...\n";
            return out;
        }
        do
        {
            out << "|" << pTemp->iData << "|->";
            pTemp = pTemp->pNext;
        }while(pTemp != pLis.pDummy->pPrev->pNext);
        std::cout << std::endl;
        return out;
    }