#include <iostream>
#include "header.h"

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
                pCurrent = pCurrent->m_pNext;
                return *this;
            }

            CList::iterator CList::iterator::operator ++(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->m_pNext;
                return temp;
            }

            CList::iterator& CList::iterator::operator --()
            {
                pCurrent = pCurrent->m_pPrev;
                return *this;
            }

            CList::iterator CList::iterator::operator --(int)
            {
                iterator temp = *this;
                pCurrent = pCurrent->m_pPrev;
                return temp;
            }

            int CList::iterator::operator *()
            {
                return pCurrent->Data;
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
                m_Start.set(m_pFirst);
                return m_Start;
            }

            CList::iterator& CList::end()
            {
                m_End.set(m_pLast);
                return m_End;
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