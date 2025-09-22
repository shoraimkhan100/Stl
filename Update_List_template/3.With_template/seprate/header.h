using std::ostream;
class CList;
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
        CList();
        ~CList();
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