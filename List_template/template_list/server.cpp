#include <iostream>
#include "header.h"

using std::ostream;

    template <typename T>
    CNode<T>::CNode()
    {
        m_pPrev = NULL;
        Data = 0;
        m_pNext = NULL;
    }

    template <typename T2>
    CNode<T2>::~CNode()
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
    
            if(NULL == m_pFirst || NULL == m_pLast)
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
            CNode<T> *pTemp = NULL;

            Value = CountNode();

            if(iPos <= 0 || iPos > Value)
            {
                std::cout << iPos << " Position is Invalid\n";
                return iPos;
            }

            if(1 == iPos)
            {
                Value = DeleteFirst();
                return Value;
            }
            if(iPos == Value)
            {
                Value = DeleteLast();
                return Value;
            }

            int iValue = 1;
            pTemp = m_pFirst;
            while(iValue < iPos)
            {
                iValue++;
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
                ConcatList(refObj);                
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

    template <typename T>
    CList<T>::CList()
    {
        m_pFirst = NULL;
        m_pLast = NULL;
    }
    template <typename T>
    CList<T>::~CList()
    {
        if(m_pFirst != NULL)
            DeleteAll();
        m_pFirst = NULL;
        m_pLast = NULL;
    }

template <typename T>
ostream& operator << (ostream &out , CList<T> &pLis)
{
    CNode<T> *pTemp = pLis.m_pFirst;

    if(NULL == pLis.m_pFirst)
    {
        std::cout << "list is Empty...\n";
        return out;
    }
    do
    {
        std::cout << "|" << pTemp->Data << "|->";
        pTemp = pTemp->m_pNext;
    }while(pTemp != pLis.m_pLast->m_pNext);
    std::cout << std::endl;
    return out;
}