#include <iostream>
#include <cstring>

using std::ostream;

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
        memset(pVec, 0, iSize * sizeof(int));
    }
    ~Vector()
    {
        if (pVec != nullptr)
        {
            delete[] pVec;
            pVec = nullptr;
        }
        iSize = 0;
    }
    int size()
    {
        return iSize;
    }
    int &operator[](int iIndex)
    {
        return pVec[iIndex];
    }
    friend ostream &operator<<(ostream &, Vector &);

    class iterator
    {
        int *pCurrent;

    public:
        iterator() : pCurrent(nullptr) {}
        ~iterator() {}
        int *Get_Current()
        {
            return pCurrent;
        }
        bool operator==(iterator &other)
        {
            return (pCurrent == other.pCurrent);
        }
        bool operator!=(iterator &other)
        {
            return !(*this == other);
        }
        bool operator>=(iterator &other)
        {
            return (pCurrent >= other.pCurrent);
        }
        bool operator<=(iterator &other)
        {
            return (pCurrent <= other.pCurrent);
        }
        void set(int *pCurr)
        {
            pCurrent = pCurr;
        }
        iterator &operator++()
        {
            ++pCurrent;
            return *this;
        }
        iterator operator++(int)
        {
            iterator iter = *this;
            ++pCurrent;
            return iter;
        }
        iterator &operator--()
        {
            --pCurrent;
            return *this;
        }
        iterator operator--(int)
        {
            iterator iter = *this;
            --pCurrent;
            return iter;
        }
        int operator*()
        {
            return *pCurrent;
        }
        bool operator<(iterator &other)
        {
            return pCurrent < other.pCurrent;
        }
        bool operator>(iterator &other)
        {
            return pCurrent > other.pCurrent;
        }
    };

private:
    iterator m_Start;
    iterator m_End;

public:
    iterator &begin()
    {
        m_Start.set(pVec);
        return m_Start;
    }
    iterator &end()
    {
        m_End.set(pVec + iSize);
        return m_End;
    }
    void push_back(int iGet)
    {
        int *pPtr2 = new int[iSize + 1]; // Increase size by 1

        if (pPtr2 == nullptr)
        {
            std::cout << "MEMORY ALLOCATION FAILED\n";
            return;
        }

        for (int i = 0; i < iSize; ++i)
            pPtr2[i] = pVec[i]; // Copy existing elements

        pPtr2[iSize] = iGet; // Assign the new value at the end

        delete[] pVec;
        pVec = pPtr2;
        ++iSize; // Increment size
    }

    void push_front(int iGet)
    {
        int *pPtr2 = new int[iSize + 1]; // Increase size by 1

        if (pPtr2 == nullptr)
        {
            std::cout << "MEMORY ALLOCATION FAILED\n";
            return;
        }

        pPtr2[0] = iGet; // Assign the new value at the beginning

        for (int i = 0; i < iSize; ++i)
            pPtr2[i + 1] = pVec[i]; // Shift existing elements to the right

        delete[] pVec;
        pVec = pPtr2;
        ++iSize; // Increment size
    }

    void swap(Vector &rSwap)
    {
        int *pPtr = pVec;
        int iSwapsize = iSize;

        pVec = rSwap.pVec;
        iSize = rSwap.iSize;

        rSwap.pVec = pPtr;
        rSwap.iSize = iSwapsize;

        pPtr = nullptr;
    }

    void insert(iterator iter, int iValue)
    {
        int iIndex = iter.Get_Current() - pVec;
        int *pPtr2 = new int[iSize + 1];

        if (pPtr2 == nullptr)
        {
            std::cout << "MEMORY ALLOCATION FAILED\n";
            return;
        }

        for (int i = 0; i < iIndex; ++i)
            pPtr2[i] = pVec[i];

        pPtr2[iIndex] = iValue;

        for (int i = iIndex + 1; i < iSize + 1; ++i)
            pPtr2[i] = pVec[i - 1];

        delete[] pVec;
        pVec = pPtr2;
        ++iSize;
    }
};

ostream &operator<<(ostream &out, Vector &pVec)
{
    if (pVec.iSize == 0)
    {
        out << "List Is Empty ... \n";
        return out;
    }
    out << "Vector is: ";
    for (int i = 0; i < pVec.iSize; ++i)
        out << pVec.pVec[i] << ' ';
    out << '\n';
    return out;
}

int main(void)
{
    // an int vector of 10 elements
    Vector intV(10);
    Vector newV(20); // all elements are 0
    Vector::iterator I;
    size_t i;

    for (i = 0; i < intV.size(); ++i)
        intV[i] = i; // fill vector, random access

    // vector increases on demand
    intV.insert(intV.end(), 100); // append the number 100

    // use as array
    for (i = 0; i < intV.size(); ++i)
        std::cout << intV[i] << ' ';

    std::cout << '\n';

    // use with an iterator
    for (I = intV.begin(); I != intV.end(); ++I)
        std::cout << *I << ' ';

    std::cout << '\n';

    std::cout << "newV = ";
    for (i = 0; i < newV.size(); ++i)
        std::cout << newV[i] << ' ';

    // swapping two vectors.
    newV.swap(intV);

    std::cout << "\nnewV after swapping = ";
    for (i = 0; i < newV.size(); ++i)
        std::cout << newV[i] << ' '; // old contents of intV

    std::cout << "\nintV after swapping = ";
    for (i = 0; i < intV.size(); ++i)
        std::cout << intV[i] << ' '; // old contents of newV

    std::cout << "\n\nintV = ";
    std::cout << intV;
    std::cout << "\nnewV = ";
    std::cout << newV;

    return 0;
}
