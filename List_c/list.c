#include <stdio.h>
#include <malloc.h>

struct Node
{
    struct Node *pPrev;
    int iData;
    struct Node *pNext;
};

void InsertFirst(struct Node ** , struct Node ** , int);
void InsertLast(struct Node ** , struct Node ** , int);
void InsertAtPosition(struct Node ** , struct Node ** , int , int);

int DeleteFirst(struct Node ** , struct Node **);
int DeleteLast(struct Node ** , struct Node **);
int DeleteAtPosition(struct Node ** , struct Node ** , int); 

int SearchFirstOccurence(struct Node * , struct Node * , int);
int SearchLastOccurence(struct Node * , struct Node * , int);
int SearchAllOccurence(struct Node * , struct Node * , int);

int CountNode(struct Node * , struct Node *);

void ReverseDisplay(struct Node * , struct Node *);
void PhysicalReverse(struct Node ** , struct Node **); 

void ConcatList(struct Node ** , struct Node ** , struct Node ** , struct Node **);
void ConcatAtPosition(struct Node ** , struct Node ** , struct Node ** , struct Node ** , int);

void DeleteAll(struct Node ** , struct Node **);

void Display(struct Node * , struct Node *);

int main(void)
{
    int iChoice = 0;
    int iValue = 1;
    int iPos;
    int iHold;
    struct Node *pFirst = NULL;
    struct Node *pLast1 = NULL;
    struct Node *pSecond = NULL;
    struct Node *pLast2 = NULL;
    
    while(iValue != -1)
    {
        printf("\n\n**********************************************************************************************************************\n\n");
                printf("|->  1.Insert\n");
                printf("|->  2.Delete\n");
                printf("|->  3.Search\n");
                printf("|->  4.Count\n");
                printf("|->  5.Reverse\n");
                printf("|->  6.Concat\n");
                printf("|->  7.Exit\n");
            printf("Enter the Choice :- ");
            scanf("%d",&iChoice);
        if(pFirst == NULL)
        {
            if(iChoice == 2 || iChoice == 3 || iChoice == 5)
            {
                Display(pFirst,pLast1);
                continue;
            }
        }
           
        if(iChoice > 7 || iChoice <= 0)
        {
            printf("Your Choice is Wrong...\n");
            continue;
        }
        iValue = 1;
        while(iValue != -1)
        {
        switch(iChoice)
        {
            case 1://Insert
                while(iValue != -2)
                {
                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("|->  1.Insert First\n");
                    printf("|->  2.Insert Last\n");
                    printf("|->  3.Insert At Position\n");
                    printf("|->  4.Back\n");

                printf("Enter Your Choice :- ");
                scanf("%d",&iChoice);
                
                    if(iChoice > 4 || iChoice <= 0)
                    {
                        printf("Your Choice is Wrong...\n");
                        continue;
                    }
                switch(iChoice)
                {
                    case 1:
                printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("\nEnter the Data :- ");
                            scanf("%d",&iValue);
                            if(iValue > 0)
                            {
                                InsertFirst(&pFirst , &pLast1 , iValue);
                                Display(pFirst , pLast1);
                            }
                    break;

                    case 2:
                            printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                        printf("\nEnter Your Data :- ");
                                scanf("%d",&iValue);
                                if(iValue > 0)
                                {
                                    InsertLast(&pFirst , &pLast1 , iValue);
                                    Display(pFirst , pLast1);
                                }
                        break;

                        case 3:
                            printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                                printf("\nEnter The Position :- ");
                                scanf("%d",&iPos);
                                iChoice = CountNode(pFirst , pLast1);
                                if(iPos <= 0 || iPos > iChoice+1)
                                {
                                    printf("Position is invalid\n");
                                    continue;
                                }
                                printf("Enter Your Data :- ");
                                scanf("%d",&iValue);
                                if(iValue > 0)
                                {
                                    InsertAtPosition(&pFirst , &pLast1 , iValue  , iPos);
                                    Display(pFirst , pLast1);
                                }
                            break;
                        case 4:
                            iValue = -2;
                    }
                }
                break;
               
            case 2:     
                iValue = 1;
                while(iValue != -2)
                {
                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("|->1.Delete First\n");
                    printf("|->2.Delete Last\n");
                    printf("|->3.Delete At Position\n");
                    printf("|->4.Back\n");
                    printf("Enter Your Choice :- ");
                    scanf("%d",&iChoice);
                    if(iChoice > 4)
                    {
                        printf("Your Choice is Wrong...\n");
                        continue;
                    }
                    
                    switch(iChoice)
                    {
                    case 1:
                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    iValue = DeleteFirst(&pFirst , &pLast1);
                        if(iValue != -1)
                            printf("Deleted Data is %d\n",iValue);
                        else    
                            break;
                        Display(pFirst , pLast1);
                        break;
                    case 2:
                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    iValue = DeleteLast(&pFirst , &pLast1);
                        if(iValue != -1)
                            printf("Deleted Data is : %d\n",iValue);
                        else
                            break;
                        Display(pFirst , pLast1);
                        break;
                    case 3:
                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                        printf("Enter Your Position :- ");
                        scanf("%d",&iPos);
                        iValue = CountNode(pFirst , pLast1);
                        if(iValue == 0)
                        {
                            printf("List is Empty...\n");
                            break;
                        }
                            if(iPos <= 0 || iPos > iValue)
                            {
                                printf("%d Position is invalid\n",iPos);
                                continue;
                            }
                            iValue = DeleteAtPosition(&pFirst , &pLast1 , iPos);
                            if(iValue != -1)
                                printf("Deleted Data is : %d\n",iValue);
                            Display(pFirst , pLast1);
                        break;
                    case 4:
                        iValue = -2;
                    }
                }
            break;
            
            case 3:  
            iValue = 1;  
            while(iValue != -2)
            {
            printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                printf("|->1.Seach First Occurence\n");
                printf("|->2.Search Last Occurence\n");
                printf("|->3.Search All Occurence\n");
                printf("|->4.Back\n");
                printf("Enter Your Choice :- ");
                scanf("%d",&iChoice);
                if(iChoice > 4)
                {
                    printf("Your Choice is Wrong...\n");
                    continue;
                }
                switch(iChoice)
                {
                    case 1:
                        printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                        printf("Enter Data To Search :- ");
                        scanf("%d",&iValue);

                    if(iValue != 0)
                    {
                    iValue = SearchFirstOccurence(pFirst , pLast1 , iValue);
                        if(iValue == -1)
                        {
                            printf("List is Empty..\n");
                            break;
                        }
                        if(iValue == 0)
                            printf("Data Not Found\n");
                        else
                            printf("Position of Data is %d\n",iValue);
                    }    
                    break;

                    case 2:
                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("Enter Data to Search :- ");
                    scanf("%d",&iValue);

                    if(iValue != 0)
                    {
                    iValue = SearchLastOccurence(pFirst , pLast1 , iValue);
                        if(iValue == -1)
                        {
                            printf("List is Empty...\n");
                            break;
                        }
                        if(iValue == 0)
                            printf("Data Not Found\n");
                        else
                            printf("Position of Data is %d\n",iValue);
                    }     
                    break;

                    case 3:
                        printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                        printf("Enter Data To Search :- ");
                        scanf("%d",&iValue);

                    if(iValue != 0)
                    {
                    iValue = SearchAllOccurence(pFirst , pLast1 , iValue);
                        if(iValue == -1)
                            {
                                printf("List is Empty...\n");
                                break;
                            }
		
                        printf("Data Found %d times\n",iValue);
                    }
                    break;

                    case 4:
                        iValue = -2;    
                } 
            }
            break;

            case 4:
                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    iValue = CountNode(pFirst , pLast1);
                    printf("Count Of Node is %d\n\n",iValue);
                break;
            
            case 5:
            iValue = 1;
                while(iValue != -2)
                {
                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("|->1.Reverse Display\n");
                    printf("|->2.Physical Reverse\n");
                    printf("|->3.Back\n");
                    printf("Enter Your Choice :- ");
                    scanf("%d",&iChoice);
                        if(iChoice > 3)
                        {
                            printf("Your Choice is Wrong...\n");
                            continue;
                        }

                    switch(iChoice)
                    {
                        case 1:
                            printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                            ReverseDisplay(pFirst , pLast1);
                            break;
                        case 2:
                            printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                            PhysicalReverse(&pFirst , &pLast1);
                            Display(pFirst,pLast1);
                            break;
                        case 3:
                            iValue = -2;
                    }
                }
            break;
            
            case 6:     //concat
            iValue = 1;
            while(iValue != -2)
            {
                iValue = 1;
                printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                printf("|->1.Concat List\n");
                printf("|->2.Concat At Position\n");
                printf("|->3.Back\n");
                
                printf("Enter Your Choice :- ");
                scanf("%d",&iChoice);

                if(iChoice == 2)
                {
                    
                    iValue = CountNode(pFirst,pLast1);
                    
                    while(iValue != -1)
                    {
                        printf("Enter Your Position :- ");
                        scanf("%d",&iHold);

                    if(iHold <= 0 || iHold > iValue+1)
                    {
                        printf("Position is Invalid\n");
                        continue;
                    } 
                    break;
                    }
                }

                if(iChoice > 3)
                {
                    printf("Your Choice is Wrong...\n");
                    continue;
                }

                switch(iChoice)
                {
                case 1:
                    if(pSecond == NULL)
                    {
                        while(iValue != -1)
                        {
                            printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                            printf("|->  1.Insert First\n");
                            printf("|->  2.Insert Last\n");
                            printf("|->  3.Insert At Position\n");
                            printf("|->  4.Back\n");
                        printf("Enter Your Choice :- ");
                        scanf("%d",&iChoice);
                        if(iChoice > 4)
                            {
                                printf("Your Choice is Wrong...\n");
                                continue;
                            }
                        switch(iChoice)
                        {
                            case 1:
                                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                                    printf("\nEnter Your Data :- ");
                                    scanf("%d",&iValue);
                                    if(iValue > 0)
                                    {
                                        InsertFirst(&pSecond , &pLast2 , iValue);
                                        Display(pSecond , pLast2);
                                    }
                            break;

                            case 2:
                                printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                                printf("\nEnter Your Data :- ");
                                scanf("%d",&iValue);
                                if(iValue > 0)
                                {
                                    InsertLast(&pSecond , &pLast2 , iValue);
                                    Display(pSecond , pLast2);
                                }
                                break;

                                case 3:
                                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                                    printf("\nEnter The Position :- ");
                                    scanf("%d",&iPos);
                                    iChoice = CountNode(pSecond , pLast2);
                                    if(iPos <= 0 || iPos > iChoice+1)
                                    {
                                        printf("Position is invalid\n");
                                        continue;
                                    }
                                    printf("Enter Your Data :- ");
                                    scanf("%d",&iValue);
                                    if(iValue > 0)
                                    {
                                        InsertAtPosition(&pSecond , &pLast2 , iValue  , iPos);
                                        Display(pSecond , pLast2);
                                    }                                    
                                break;

                                case 4:
                                    iValue = -1;
                            }
                    }        
                ConcatList(&pFirst , &pLast1 , &pSecond , &pLast2);
                Display(pFirst,pLast1);
                }
                break;
    
                case 2:
                printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                iValue = CountNode(pFirst,pLast1);
                    if(iValue == 0)
                        {
                            printf("Your First List is Empty...\n");
                            break;
                        }
                if(pSecond == NULL)
                    {
                        while(iValue != -1)
                        {
                            printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                            printf("|->  1.Insert First\n");
                            printf("|->  2.Insert Last\n");
                            printf("|->  3.Insert At Position\n");
                            printf("|->  4.Back\n");
                        printf("Enter Your Choice :- ");
                        scanf("%d",&iChoice);
                            if(iChoice > 4)
                            {
                                printf("Your Choice is Wrong...\n");
                                continue;
                            }        
                        switch(iChoice)
                        {
                            case 1:
                                    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                                    printf("\nEnter Your Data :- ");
                                    scanf("%d",&iValue);
                                    if(iValue > 0)
                                    {
                                        InsertFirst(&pSecond , &pLast2 , iValue);
                                        iValue = CountNode(pSecond,pLast2);
                                        printf("count is : %d\n",iValue);
                                        Display(pSecond , pLast2);
                                    }
                            break;

                            case 2:
                                        printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                                        printf("\nEnter Your Data :- ");
                                        scanf("%d",&iValue);
                                        if(iValue > 0)
                                        {
                                            InsertLast(&pSecond , &pLast2 , iValue);
                                            iValue = CountNode(pSecond,pLast2);
                                            printf("count is : %d\n",iValue);

                                            Display(pSecond , pLast2);
                                        }
                                break;

                                case 3:
                                        printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                                        printf("\nEnter The Position :- ");
                                        scanf("%d",&iPos);
                                        iValue = CountNode(pSecond , pLast2);
                                        if(iPos <= 0 || iPos > iValue+1)
                                        {
                                            printf("Position is invalid\n");
                                            continue;
                                        }
                                        printf("Enter Your Data :- ");
                                        scanf("%d",&iValue);

                                        if(iValue > 0)
                                        {
                                            InsertAtPosition(&pSecond , &pLast2 , iValue  , iPos);
                                            iValue = CountNode(pSecond,pLast2);
                                            printf("count is : %d\n",iValue);
                                            Display(pSecond , pLast2);
                                        }
                                    break;
                                case 4:
                                    iValue = -1;
                            }
                    }        
                    ConcatAtPosition(&pFirst , &pLast1 , &pSecond , &pLast2 , iHold);
                    Display(pFirst,pLast1);
                }
                break;

                case 3:
                    iValue = -2;
                }
            }
            break;

            case 7:
                if(pFirst != NULL)
                    {
                        DeleteAll(&pFirst,&pLast1);
                        pFirst = pLast1 = NULL;
                    }          
                if(pSecond != NULL)
                    {
                        DeleteAll(&pSecond,&pLast2);          
                        pSecond = pLast2 = NULL;
                    }
                printf("exiting....\n");
                iValue = -1;
        }
        break;
    }
    }
    Display(pFirst,pLast1);
    Display(pSecond,pLast2);
        printf("\n\n**********************************************************************************************************************\n\n");
    return 0;
}
void InsertFirst(struct Node **ppHead , struct Node **ppTail , int iValue)
{
    struct Node *pNewNode = NULL;

    pNewNode = (struct Node *)malloc(sizeof(struct Node));
    if(NULL == pNewNode)
    {
        printf("Memory Allocation FAILED\n");
        return;
    }

    pNewNode->pPrev = NULL;
    pNewNode->iData = iValue;
    pNewNode->pNext = NULL;

    if(NULL == *ppHead)
    {
        *ppHead = pNewNode;
        *ppTail = pNewNode;
        (*ppTail)->pNext = *ppHead;
        (*ppHead)->pPrev = *ppTail;
        return;
    }

    pNewNode->pNext = *ppHead;
    pNewNode->pPrev = *ppTail;
    (*ppHead)->pPrev = pNewNode;
    *ppHead = pNewNode;
    (*ppTail)->pNext = *ppHead;
}
void InsertLast(struct Node **ppHead , struct Node **ppTail , int iValue)
{
    struct Node *pNewNode = NULL;
    
    pNewNode = (struct Node *)malloc(sizeof(struct Node));
    if(NULL == pNewNode)
    {
        printf("Memory Allocation FAILED\n");
        return;
    }

    pNewNode->pPrev = NULL;
    pNewNode->iData = iValue;
    pNewNode->pNext = NULL;

    if(NULL == *ppHead)
    {
        *ppTail = pNewNode;
        *ppHead = pNewNode;
        pNewNode->pNext = *ppHead;
        pNewNode->pPrev = *ppTail;
    }
    pNewNode->pNext = *ppHead;
    pNewNode->pPrev = *ppTail;
    (*ppTail)->pNext = pNewNode;
    *ppTail = pNewNode;
    (*ppHead)->pPrev = *ppTail;
}
void InsertAtPosition(struct Node **ppHead , struct Node **ppTail , int iValue , int iPos)
{
    int iCount = 0;
    struct Node *pTemp = NULL;
    struct Node *pNewNode = NULL;

    iCount = CountNode(*ppHead , *ppTail);

    if(iPos <= 0 || iPos > iCount+1)
    {
        printf("Position is Invalid\n");
        return;
    }

    if(1 == iPos)
    {
        InsertFirst(ppHead , ppTail , iValue);
        return;
    }
    if(iPos == iCount+1)
    {
        InsertLast(ppHead , ppTail , iValue);
        return;
    }

    pNewNode = (struct Node *)malloc(sizeof(struct Node));
    if(NULL == pNewNode)
    {
        printf("Memory Allocation FAILED\n");
        return;
    }
    pNewNode->pPrev = NULL;
    pNewNode->iData = iValue;
    pNewNode->pNext = NULL;

    pTemp = *ppHead;
    iCount = 1;

    while(iCount < iPos-1)
    {
        pTemp = pTemp->pNext;
        iCount++;
    }  
    pNewNode->pNext = pTemp->pNext;
    pTemp->pNext->pPrev = pNewNode;
    pTemp->pNext = pNewNode;
    pNewNode->pPrev = pTemp;
}
int DeleteFirst(struct Node **ppHead , struct Node **ppTail)
{
    int iValue;
    
    if(NULL == *ppHead || NULL == *ppTail)
        return -1;

    iValue = (*ppHead)->iData;

    if(*ppHead == *ppTail)
    {
        (*ppHead)->pNext = NULL;
        (*ppTail)->pPrev = NULL;
        free(*ppHead);
        *ppHead = NULL;
        *ppTail = NULL;
        return iValue;
    }
    (*ppHead) = (*ppHead)->pNext;
    (*ppHead)->pPrev->pNext = NULL;
    (*ppHead)->pPrev->pPrev = NULL;
    (*ppTail)->pNext = *ppHead;

    free((*ppHead)->pPrev);
    (*ppHead)->pPrev = *ppTail;    
    return iValue;
}
int DeleteLast(struct Node **ppHead , struct Node **ppTail)
{
    int iValue;
    if(NULL == *ppTail)
        return -1;

    iValue = (*ppTail)->iData;

    if(*ppHead == *ppTail)
    {
        (*ppHead)->pNext = NULL;
        (*ppTail)->pPrev = NULL;
        free(*ppTail);
        *ppTail = NULL;
        *ppHead = NULL;
        return iValue;
    }
    *ppTail = (*ppTail)->pPrev;
    (*ppTail)->pNext->pNext = NULL;
    (*ppTail)->pNext->pPrev = NULL;
    (*ppHead)->pPrev = *ppTail;

    free((*ppTail)->pNext);
    (*ppTail)->pNext = *ppHead;
    
    return iValue;
}
int DeleteAtPosition(struct Node **ppHead , struct Node **ppTail , int iPos)
{
    int iValue;
    struct Node *pTemp = NULL;

    iValue = CountNode(*ppHead,*ppTail);

    if(iPos <= 0 || iPos > iValue)
    {
        printf("%d Position is Invalid\n",iPos);
        return iPos;
    }

    if(1 == iPos)
    {
        iValue = DeleteFirst(ppHead , ppTail);
        return iValue;
    }
    if(iPos == iValue)
    {
        iValue = DeleteLast(ppHead , ppTail);
        return iValue;
    }

    iValue = 1;
    pTemp = *ppHead;
    while(iValue < iPos)
    {
        iValue++;
        pTemp = pTemp->pNext;
    }
        iValue = pTemp->iData;
        pTemp->pPrev->pNext = pTemp->pNext;
        pTemp->pNext->pPrev = pTemp->pPrev;
        pTemp->pNext = NULL;
        pTemp->pPrev = NULL;
        free(pTemp);
        pTemp = NULL;
    
    return iValue;
}
int SearchFirstOccurence(struct Node *pHead , struct Node *pTail , int iNo)
{
    int iPos = 0;
    if(NULL == pHead)
        return -1;
    do
    {
        iPos++;
        if(pHead->iData == iNo)
            return iPos;
        pHead = pHead->pNext;     
    } while(pHead != pTail->pNext);
    return 0;    
};
int SearchLastOccurence(struct Node *pHead , struct Node *pTail , int iNo)
{
    int iPos = 0;
    int iRet = 0;
    if(NULL == pHead)
        return -1;
    do
    {
        iPos++;
        if(pHead->iData == iNo)
            iRet = iPos;
        pHead = pHead->pNext;     
    }while(pHead != pTail->pNext);
        return iRet;
}
int SearchAllOccurence(struct Node *pHead , struct Node *pTail , int iNo)
{
    int iPos = 0;
    if(NULL == pHead)
        return -1;
    do
    {
        if(pHead->iData == iNo)
            iPos++;
        pHead = pHead->pNext;
    } while (pHead != pTail->pNext);
    if(iPos != 0)
        return iPos;
    return 0;
}
int CountNode(struct Node *pHead , struct Node *pTail)
{
    int iCount = 0;
    if(NULL == pHead)
        return 0;
    do
    {
        iCount++;
        pHead = pHead->pNext;
    }while(pHead != pTail->pNext);
    return iCount;
}
void ReverseDisplay(struct Node *pHead , struct Node *pTail)
{
    if(NULL == pHead)
    {
        printf("List is Empty..\n");
        return;
    }

    PhysicalReverse(&pHead , &pTail);
    Display(pHead , pTail);
    PhysicalReverse(&pHead , &pTail);
}
void PhysicalReverse(struct Node **ppHead , struct Node **ppTail)
{
    struct Node *pPre = *ppTail;
    struct Node *pCurrent = *ppHead;
    struct Node *pNext = NULL;

    if(NULL == *ppHead)
        return;
    
    while(1)
    {
        pNext = pCurrent->pNext;
        pCurrent->pPrev = pNext;
        pCurrent->pNext = pPre;
        pPre = pCurrent;

        if(pCurrent == *ppTail)
            break;
        pCurrent = pNext;
    }
    *ppHead = *ppTail;
    *ppTail = pNext;
}
void ConcatList(struct Node **ppHead1 , struct Node **ppTail1 , struct Node **ppHead2 , struct Node **ppTail2)
{
    if(NULL == *ppHead1)
    {
        *ppHead1 = *ppHead2;
        *ppTail1 = *ppTail2;
    }
    else
    {
    (*ppTail1)->pNext = *ppHead2;
    (*ppHead2)->pPrev = *ppTail1;
    (*ppTail2)->pNext = *ppHead1;
    (*ppHead1)->pPrev = *ppTail2;
    *ppTail1 = *ppTail2;
    }
    *ppTail2 = NULL;
    *ppHead2 = NULL;
}
void ConcatAtPosition(struct Node **ppHead1 , struct Node **ppTail1 , struct Node **ppHead2 , struct Node **ppTail2 , int iPos)
{
    int iCount;
    
    struct Node *pTemp = NULL;

    iCount = CountNode(*ppHead1,*ppTail1);

    if(iPos <= 0 || iPos > iCount+1)
    {
        printf("Position is invalid\n");
        return;
    }
    if(1 == iPos)
    {
        ConcatList(ppHead2,ppTail2,ppHead1,ppTail1);
        *ppHead1 = *ppHead2;
        *ppTail1 = *ppTail2;
        return;
    }
    if(iPos == iCount+1)
    {
        ConcatList(ppHead1,ppTail1,ppHead2,ppTail2);
        return;
    }

    iCount = 1;
    pTemp = *ppHead1;
    while(iCount < iPos-1)
    {
        pTemp = pTemp->pNext;
        iCount++;
    }
    (*ppTail2)->pNext = pTemp->pNext;
    (*ppHead2)->pPrev = pTemp;
    pTemp->pNext->pPrev = *ppTail2;
    pTemp->pNext = *ppHead2;

    *ppTail2 = NULL;
    *ppHead2 = NULL;
}
void DeleteAll(struct  Node **ppHead , struct Node **ppTail)
{    
    struct Node *pTemp = NULL;
    (*ppTail)->pNext = NULL;
    
    while(*ppHead != NULL)
    {
       pTemp = *ppHead;
       *ppHead = pTemp->pNext;
       pTemp->pNext = NULL;
       pTemp->pPrev = NULL;
       free(pTemp); 
       pTemp = NULL;
    }
}
void Display(struct Node *pHead , struct Node *pTail)
{
    if(NULL == pHead)
    {
        printf("List is empty...\n");
        return;
    }
    do
    {
        printf("|%d|->",pHead->iData);
        pHead = pHead->pNext;
    } while(pHead != pTail->pNext);
    printf("\n");
}