#include <iostream>
#include "header.h"

using std::ostream;

    CNode::CNode()
    {
        m_pPrev = NULL;
        m_iData = 0;
        m_pNext = NULL;
    }
    CNode::~CNode()
    {
        m_pPrev = NULL;
        m_iData = 0;
        m_pNext = NULL;
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

            pNewNode->m_iData = iValue;

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
        void CList::InsertLast(int iValue)
        {
            CNode *pNewNode = NULL;
    
                pNewNode = new CNode;
                if(NULL == pNewNode)
                {
                    std::cout << "Memory Allocation FAILED\n";
                    return;
                }

                pNewNode->m_pPrev = NULL;
                pNewNode->m_iData = iValue;
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
        void CList::InsertAtPosition(int iValue , int iPos)
        {
            int iCount = 0;
            CNode *pTemp = NULL;
            CNode *pNewNode = NULL;

            iCount = CountNode();

            if(iPos <= 0 || iPos > iCount+1)
            {
                std::cout << "Position is Invalid\n";
                return;
            }

            if(1 == iPos)
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
                printf("Memory Allocation FAILED\n");
                return;
            }
            pNewNode->m_pPrev = NULL;
            pNewNode->m_iData = iValue;
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

        bool CList::ListEmpty()
        {
            if(NULL == m_pFirst)
                return true;
            return false;
        }

        int CList::DeleteFirst()
        {
            int iValue;
    
            if(NULL == m_pFirst)
                return -1;

            iValue = m_pFirst->m_iData;

            if(m_pFirst == m_pLast)
            {
                m_pFirst->m_pNext = NULL;
                m_pLast->m_pPrev = NULL;
                delete m_pFirst;
                m_pFirst = NULL;
                m_pLast = NULL;
                return iValue;
            }
            m_pFirst = m_pFirst->m_pNext;
            m_pFirst->m_pPrev->m_pNext = NULL;
            m_pFirst->m_pPrev->m_pPrev = NULL;
            m_pLast->m_pNext = m_pFirst;

            delete m_pFirst->m_pPrev;
            m_pFirst->m_pPrev = m_pLast;    
            return iValue;
        }
        int CList::DeleteLast()
        {
            int iValue;
            
            if(NULL == m_pLast)
                return -1;

            iValue = m_pLast->m_iData;

            if(m_pFirst == m_pLast)
            {
                m_pFirst->m_pNext = NULL;
                m_pLast->m_pPrev = NULL;
                delete m_pLast;
                m_pLast = NULL;
                m_pFirst = NULL;
                return iValue;
            }
            m_pLast = m_pLast->m_pPrev;
            m_pLast->m_pNext->m_pNext = NULL;
            m_pLast->m_pNext->m_pPrev = NULL;
            m_pFirst->m_pPrev = m_pLast;

            delete m_pLast->m_pNext;
            m_pLast->m_pNext = m_pFirst;
            
            return iValue;
        }
        int CList::DeleteAtPosition(int iPos)
        {
            int iValue;
            CNode *pTemp = NULL;

            if(NULL == m_pFirst )
                return -1;

            iValue = CountNode();
            std::cout << "Count " << iValue << std::endl;

            if(iPos <= 0 || iPos > iValue)
            {
                std::cout << iPos << " Position is Invalid\n";
                return iPos;
            }

            if(1 == iPos)
            {
                iValue = DeleteFirst();
                return iValue;
            }
            if(iPos == iValue)
            {
                iValue = DeleteLast();
                return iValue;
            }

            iValue = 1;
            pTemp = m_pFirst;
            while(iValue < iPos)
            {
                iValue++;
                pTemp = pTemp->m_pNext;
            }
                iValue = pTemp->m_iData;
                pTemp->m_pPrev->m_pNext = pTemp->m_pNext;
                pTemp->m_pNext->m_pPrev = pTemp->m_pPrev;
                pTemp->m_pNext = NULL;
                pTemp->m_pPrev = NULL;
                delete pTemp;
                pTemp = NULL;
            
            return iValue;
        }

        int CList::SearchFirstOccurence(int iNo)
        {
            CNode *pHead = m_pFirst;
            int iPos = 0;

            if(NULL == m_pFirst )
                return -1;
            do
            {
                iPos++;
                if(pHead->m_iData == iNo)
                    return iPos;
                pHead = pHead->m_pNext;     
            }while(pHead != m_pLast->m_pNext);
            return 0;
        }
        int CList::SearchLastOccurence(int iNo)
        {
            int iPos = 0;
            int iRet = 0;
            CNode *pHead = m_pFirst;

            if(NULL == m_pFirst )
                return -1;
            do
            {
                iPos++;
                if(pHead->m_iData == iNo)
                    iRet = iPos;
                pHead = pHead->m_pNext;     
            }while(pHead != m_pLast->m_pNext);
                return iRet;
        }
        int CList::SearchAllOccurence(int iNo)
        { 
            int iPos = 0;
            CNode *pHead = m_pFirst;
            
            if(NULL == m_pFirst )
                return -1;
            do
            {
                if(pHead->m_iData == iNo)
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
            
            if(NULL == m_pFirst )
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
            if(NULL == m_pFirst )
            {
                printf("List is Empty..\n");
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
            CNode *pNext = NULL;

            if(NULL == m_pFirst )
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
            
            CNode *pTemp = NULL;

            if(refObj.m_pFirst == NULL)
            {
                return;
            }
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

        void CList::Display()
        {
            CNode *pHead = m_pFirst;
            if(NULL == pHead)
            {
                printf("List is empty...\n");
                return;
            }
            do
            {
                printf("|%d|->",pHead->m_iData);
                pHead = pHead->m_pNext;
            } while(pHead != m_pLast->m_pNext);
            std::cout << std::endl;
        }

        void CList::DeleteAll()
        {
            CNode *pTemp = NULL;
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

    CList::CList()
    {
        m_pFirst = NULL;
        m_pLast = NULL;
    }
    CList::~CList()
    {
        if(m_pFirst != NULL)
            DeleteAll();
        m_pFirst = NULL;
        m_pLast = NULL;
    }

ostream& operator << (ostream &out , CList &pLis)
{
    CNode *pTemp = pLis.m_pFirst;

    if(NULL == pLis.m_pFirst)
    {
        std::cout << "list is Empty...\n";
        return out;
    }
    do
    {
        std::cout << "|" << pTemp->m_iData << "|->";
        pTemp = pTemp->m_pNext;
    }while(pTemp != pLis.m_pLast->m_pNext);
    std::cout << std::endl;
    return out;
}