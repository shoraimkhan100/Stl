using std::ostream;

class CList;
ostream& operator << (ostream & , CList &);
class CNode
{
    CNode *pPrev;
    int iData;
    CNode *pNext;

public:
    friend CList;
    CNode();
    ~CNode();
    friend ostream& operator << (ostream & , CList &);
};

class CList
{
    CNode *pDummy;

public:    
    void InsertFirst(int);
    void InsertLast(int);
    void InsertAtPosition(int,int);

    int DeleteFirst();
    int DeleteLast();
    int DeleteAtPosition(int);

    int SearchFirstOccurence(int);
    int SearchLastOccurence(int);
    int SearchAllOccurence(int);

    void ConcatList(CList &);
    void ConcatAtPosition(CList & , int);

    int CountNode();
    
    void Display();

    void PhysicalReverse();
    void ReverseDisplay();

    void DeleteAll();

    bool ListEmpty();

    CList();
    ~CList();
    class iterator
        {
            CNode *pCurrent;
            
            public:
            iterator();
            ~iterator();

            bool operator ==(iterator &);
            bool operator !=(iterator &);
            bool operator >=(iterator &);
            bool operator <=(iterator &);

            void set(CNode *);

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
    friend ostream& operator << (ostream & , CList &);
};
