#include <iostream>
#include <cstring>

using std::ostream;

//class iterator;   
    
class Vector
{
        int *pVec;
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
                pVec = new int[ipSize];
                memset(pVec, 0 , iSize * sizeof(int));
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
            int& operator [] (int iIndex)
            {
                return pVec[iIndex];
            }
            friend ostream& operator << (ostream & , Vector &);

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
    void Vector::push_back(int iGet)
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
    void Vector::push_front(int iGet)
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
    Vector::iterator& Vector::begin()
    {
        m_Start.set(pVec);
        return m_Start;
    }
    Vector::iterator& Vector::end()
    {
        m_End.set(pVec + iSize);
        return m_End;
    }
    Vector::iterator::iterator()
        {
            pCurrent = NULL;
        }

    Vector::iterator::~iterator()
        {
            pCurrent = NULL;
        } 
    
    int* Vector::iterator::Get_Current()
        {
            return pCurrent;
        }
     bool Vector::iterator::operator ==(iterator &cNode)
        {
            return (pCurrent == cNode.pCurrent);
        }
    
     bool Vector::iterator::operator !=(iterator &cNode)
        {
            return (pCurrent != cNode.pCurrent);
        }
    
    bool Vector::iterator::operator >=(iterator &cNode)
        {
                return (pCurrent >= cNode.pCurrent);
        }
    
    bool Vector::iterator::operator <=(iterator &cNode)
        {
            return (pCurrent <= cNode.pCurrent);
        }
    void Vector::iterator::set(int *pCurr)
        {
            pCurrent = pCurr;
        }
    Vector::iterator& Vector::iterator::operator ++()
        {
            pCurrent++;
            return *this;
        }
    Vector::iterator Vector::iterator::operator ++(int)
        {
            iterator iter = *this;
            ++pCurrent;
            return iter;
        }
    Vector::iterator& Vector::iterator::operator --()
        {
            pCurrent--;
            return *this;
        }
    Vector::iterator Vector::iterator::operator --(int)
        {
            iterator iter = *this;
            --pCurrent;
            return iter;
        }
    int Vector::iterator::operator *()
        {
            return *pCurrent;
        }
    
    bool Vector::iterator::operator <(iterator &cNode)
        {
            return pCurrent < cNode.pCurrent;
        }
    
    bool Vector::iterator::operator >(iterator &cNode)
        {
            return pCurrent > cNode.pCurrent;
        }
    ostream& operator << (ostream &out , Vector &pVec)
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
        Vector intV(10);
        Vector newV(20); // all elements are 0
        Vector::iterator I;
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