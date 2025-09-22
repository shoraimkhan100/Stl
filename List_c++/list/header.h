using std::ostream;
class CList;
class CNode
{
    CNode *m_pPrev;
    int m_iData;
    CNode *m_pNext;

    public:
        friend class CList;
    
    CNode();
    ~CNode();
    friend ostream& operator<< (ostream& , CList&);
};

class CList
{
    CNode *m_pFirst;
    CNode *m_pLast;
 
    public:   
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
        void ConcatAtPosition(CList &, int );
        void Display();
        void DeleteAll();
        bool ListEmpty();
        friend ostream& operator<< (ostream& , CList&);

    CList();
    ~CList();
};
ostream& operator << (ostream & , CList &);