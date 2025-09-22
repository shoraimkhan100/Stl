#include <iostream>
#include <cstring>

using std::ostream;
//class iterator;   
    
template <typename T>
class Vector
{
        T *pVec;
        int iSize;
        
        public:   
            Vector()
            {
                pVec = NULL;
                iSize = 0;
            } 
            Vector(int ipSize)
            {
                iSize = ipSize;
                pVec = new T[ipSize];
                memset(pVec, 0 , iSize * sizeof(T));
            }
            ~Vector()
            {
                if(pVec != NULL)
                {
                    delete []pVec;
                    pVec = NULL;
                }
                iSize = 0;
            }    
            int size()
            {
                return iSize;
            }
            template <typename T>
            T& operator [] (int iIndex)
            {
                return pVec[iIndex];
            }
            template <typename T>
            friend ostream& operator << (ostream & , Vector<T> &);

            class iterator
        {
            int *pCurrent;
            
            public:
            iterator();
            ~iterator();
            int* Get_Current();
            bool operator ==(iterator &);
            bool operator !=(iterator &);
            bool operator >=(iterator &);
            bool operator <=(iterator &);
            void set(int *);
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
        void push_back(int Get);
        void push_front(int Get);
        
        template <typename T>
        void swap(Vector &rSwap)
        {
            int *pPtr = pVec;
            int iSwapsize = iSize;

            pVec = rSwap.pVec;
            iSize = rSwap.iSize;

            rSwap.pVec = pPtr;
            rSwap.iSize = iSwapsize;

            pPtr = NULL;
        }
        void insert(iterator iter , int iValue)
        {
            int iIndex = iter.Get_Current() - pVec;
            int *pPtr2 = NULL;
            int iCounter;

            pPtr2 = new int[iSize+1];
            
            if(NULL == pPtr2)
            {
                std::cout << "MEMORY ALLOCATION FAILED\n";
                return;
            }

            for(iCounter = 0 ; iCounter < iSize ; iCounter++)
                pPtr2[iCounter] = pVec[iCounter];
            
            pPtr2[iIndex] = iValue;

            std::cout << "iIndex : " << iIndex << std::endl;

            for(iCounter = iIndex ; iCounter < iSize-1 ; iCounter++)
                pPtr2[iCounter+1] = pVec[iCounter];

            delete []pVec;
            pVec = pPtr2;
            pPtr2 = NULL;
            ++iSize;
        }
};
    template <typename T>
    void Vector<T>::push_back(int iGet)
    {
        int iCounter;
        int *pPtr2 = NULL;
        pPtr2 = new int[iSize++];

        if(NULL == pPtr2)
        {
            std::cout << "MEMORY ALLOCATIO FAILED\n";
            return;
        }

        pPtr2[iSize] = iGet;

        for(iCounter = 0 ; iCounter < iSize-1 ; iCounter++)
            pPtr2[iCounter] = pVec[iCounter];

        delete []pVec;
        pVec = pPtr2;
        pPtr2 = NULL;
    }
    template <typename T>
    void Vector<T>::push_front(int iGet)
    {
        int iCounter;
        int *pPtr2 = NULL;
        pPtr2 = new int[iSize++];

        if(NULL == pPtr2)
        {
            std::cout << "MEMORY ALLOCATION FAILED\n";
            return;
        }
        pPtr2[0] = iGet;

        for(iCounter = 0 ; iCounter < iSize-1 ; iCounter++)
            pPtr2[iCounter + 1] = pVec[iCounter]; //shifting right side ...
        
        delete []pVec;
        pVec = pPtr2;
        pPtr2 = NULL;
    }
    template <typename T>
    typename Vector<T>::iterator& Vector<T>::begin()
    {
        m_Start.set(pVec);
        return m_Start;
    }
    template <typename T>
    typename Vector<T>::iterator& Vector<T>::end()
    {
        m_End.set(pVec + iSize);
        return m_End;
    }
    template <typename T>
    Vector<T>::iterator::iterator()
        {
            pCurrent = NULL;
        }
    template <typename T>
    Vector<T>::iterator::~iterator()
        {
            pCurrent = NULL;
        } 
    template <typename T>
    int* Vector<T>::iterator::Get_Current()
        {
            return pCurrent;
        }
    template <typename T>
    bool Vector<T>::iterator::operator ==(iterator &cNode)
        {
            return (pCurrent == cNode.pCurrent);
        }
    template <typename T>
    bool Vector<T>::iterator::operator !=(iterator &cNode)
        {
            return (pCurrent != cNode.pCurrent);
        }
    template <typename T>
    bool Vector<T>::iterator::operator >=(iterator &cNode)
        {
                return (pCurrent >= cNode.pCurrent);
        }
    template <typename T>
    bool Vector<T>::iterator::operator <=(iterator &cNode)
        {
            return (pCurrent <= cNode.pCurrent);
        }
    template <typename T>
    void Vector<T>::iterator::set(int *pCurr)
        {
            pCurrent = pCurr;
        }
    template <typename T>
    typename Vector<T>::iterator& Vector<T>::iterator::operator ++()
        {
            pCurrent++;
            return *this;
        }
    template <typename T>
    typename Vector<T>::iterator Vector<T>::iterator::operator ++(int)
        {
            iterator iter = *this;
            ++pCurrent;
            return iter;
        }
    template <typename T>
    typename Vector<T>::iterator& Vector<T>::iterator::operator --()
        {
            pCurrent--;
            return *this;
        }
    template <typename T>
    typename Vector<T>::iterator Vector<T>::iterator::operator --(int)
        {
            iterator iter = *this;
            --pCurrent;
            return iter;
        }
    template <typename T>
    int Vector<T>::iterator::operator *()
        {
            return *pCurrent;
        }
    template <typename T>
    bool Vector<T>::iterator::operator <(iterator &cNode)
        {
            return pCurrent < cNode.pCurrent;
        }
    template <typename T>
    bool Vector<T>::iterator::operator >(iterator &cNode)
        {
            return pCurrent > cNode.pCurrent;
        }
    template <typename T>
    ostream& operator << (ostream &out , Vector<T> &pVec)
    {
        int iCounter;

        if(pVec.iSize == 0)
        {
            out << "List Is Empty ... \n";
            return out;
        }
        std::cout << "Vector is :- \t";
        for(iCounter = 0 ; iCounter < pVec.iSize ; iCounter++)
            std::cout << pVec.pVec[iCounter] << ' ';
        std::cout << std::endl;
        return out;
    }

    int main(void)
    {
        // an int vector of 10 elements 
        Vector <int>intV(10);
        Vector <int>newV(20); // all elements are 0
        Vector <int>::iterator I;
        size_t i;

        for(i = 0 ; i < intV.size() ; ++i)
            intV[i] = i;        // fill vector, random access
        
        // vector increases on demand
        intV.insert(intV.end() ,100); // append the number 100

        // use as array
        for(i = 0 ; i < intV.size() ; ++i)
            std::cout << intV[i] << ' ';
        
        std::cout << std::endl << std::endl;

        // use with an iterator
        for(I = intV.begin() ; I != intV.end() ; ++I)
            std::cout << *I << ' ';
        
        std::cout << std::endl << std::endl;

        std::cout << "newV = ";
        for(i = 0 ; i < newV.size() ; ++i)
            std::cout << newV[i] << ' ';
        
        // swapping two vectors.
        newV.swap(intV);

        std::cout << "\nnewV after swapping = ";
        for(i = 0 ; i < newV.size() ; ++i)
            std::cout << newV[i] << ' '; // old contents of intV
        
        std::cout << "\nintV after swapping = ";
        for(i = 0 ; i < intV.size() ; ++i)
            std::cout << intV[i] << ' '; // old contents of newV

        std::cout << "\n\nintV = ";
        std::cout << intV;
        std::cout << "\nnewV = ";
        std::cout << newV;

        return 0;
    }