#include <iostream>
#include "header.h"

int main(void)
{
    int iHold;
    CList obj1;
    CList obj2;
    int iPos = 0;
    int iValue = 0;
    int iChoice = 0;

    while(iValue != -1)
    {
        std::cout << ("\n\n**********************************************************************************************************************\n\n");
                std::cout << "|->  1.Insert\n";
                std::cout << "|->  2.Delete\n";
                std::cout << "|->  3.Search\n";
                std::cout << "|->  4.Count\n";
                std::cout << "|->  5.Reverse\n";
                std::cout << "|->  6.Concat\n";
                std::cout << "|->  7.Exit\n";
            std::cout << "Enter the Choice :- ";
            std::cin >> iChoice;
           
        if(iChoice > 7 || iChoice <= 0)
        {
            std::cout << ("Your Choice is Wrong...\n");
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
                    std::cout << ("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    std::cout << "|->  1.Insert First\n";
                    std::cout << "|->  2.Insert Last\n";
                    std::cout << "|->  3.Insert At Position\n";
                    std::cout << "|->  4.Back\n";

                std::cout << "Enter Your Choice :- ";
                std::cin >> iChoice;
                
                    if(iChoice > 4 || iChoice <= 0)
                    {
                        std::cout << "Your Choice is Wrong...\n";
                        continue;
                    }
                switch(iChoice)
                {
                    case 1:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "\nEnter the Data :- ";
                            std::cin >> iValue;
                            if(iValue > 0)
                            {
                                obj1.InsertFirst(iValue);
                                obj1.Display();
                            }
                    break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";        
                        std::cout << "\nEnter Your Data :- ";
                                std::cin >> iValue;
                                if(iValue > 0)
                                {
                                    obj1.InsertLast(iValue);
                                    obj1.Display();
                                }
                        break;

                        case 3:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        std::cout << "\nEnter The Position :- ";
                                std::cin >> iPos;
                                iHold = obj1.CountNode();
                                if(iPos < 0 || iPos > iHold+1)
                                {
                                    std::cout << ("Position is invalid\n");
                                    continue;
                                }
                                std::cout << "Enter Your Data :- ";
                                std::cin >> iValue;
                                if(iValue > 0)
                                {
                                    obj1.InsertAtPosition(iValue , iPos);
                                    obj1.Display();
                                }
                            break;
                        case 4:
                            iValue = -2;
                    }
                }
                break;
               
            case 2:     
                iValue = 1;
            iHold = obj1.ListEmpty();
                if(iHold != 1)
                {
                while(iValue != -2)
                {
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "|->1.Delete First\n";
                    std::cout << "|->2.Delete Last\n";
                    std::cout << "|->3.Delete At Position\n";
                    std::cout << "|->4.Back\n";
                    std::cout << "Enter Your Choice :- ";
                    std::cin >> iChoice;
                    
                    if(iChoice > 4)
                    {
                        std::cout << "Your Choice is Wrong...\n";
                        continue;
                    }
                    
                    switch(iChoice)
                    {
                    case 1:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        iValue = obj1.DeleteFirst();
                        if(iValue != -1)
                            std::cout << "Deleted Data is " << iValue << std::endl;
                        else    
                            break;
                        obj1.Display();
                        break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    iValue = obj1.DeleteLast();
                        if(iValue != -1)
                            std::cout << "Deleted Data is : " << iValue << std::endl;
                        else
                            break;
                        obj1.Display();
                        break;

                    case 3:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        std::cout << "Enter Your Position :- ";
                        std::cin >> iPos;
                        iValue = obj1.ListEmpty();
                        if(iValue == 1)
                        {
                            std::cout << "List is Empty...\n";
                            break;
                        }
                        iValue = obj1.CountNode();
                            if(iPos <= 0 || iPos > iValue)
                            {   
                                std::cout << iPos << " Position is invalid\n";
                                continue;
                            }
                            iValue = obj1.DeleteAtPosition(iPos);
                            if(iValue != -1)
                                std::cout << "Deleted Data is : " << iValue << std::endl;
                            obj1.Display();
                        break;

                    case 4:
                        iValue = -2;
                    }
                }
            }
            else
                obj1.Display();
            break;
            
            case 3:  
            iValue = 1; 
            iHold = obj1.ListEmpty();
            if(iHold != 1)
            {
            while(iValue != -2)
            {
            std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                std::cout << "|->1.Seach First Occurence\n";
                std::cout << "|->2.Search Last Occurence\n";
                std::cout << "|->3.Search All Occurence\n";
                std::cout << "|->4.Back\n";
                std::cout << "Enter Your Choice :- ";
                std::cin >> iChoice;
                
                if(iChoice > 4)
                {
                    std::cout << "Your Choice is Wrong...\n";
                    continue;
                }
                switch(iChoice)
                {
                case 1:
            std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "Enter Data To Search :- ";
                    std::cin >> iValue;
     
                    if(iValue != 0)
                    {
                    iValue = obj1.SearchFirstOccurence(iValue);
                        if(iValue == -1)
                        {
                            std::cout << "List is Empty..\n";
                            break;
                        }
                        if(iValue == 0)
                            std::cout << "Data Not Found\n";
                        else
                            std::cout << "Position of Data is " << iValue << std::endl;
                    }    
                    break;

                    case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "Enter Data to Search :- ";
                    std::cin >> iValue;

                    if(iValue != 0)
                    {
                    iValue = obj1.SearchLastOccurence(iValue);
                        if(iValue == -1)
                        {
                            std::cout << ("List is Empty...\n");
                            break;
                        }
                        if(iValue == 0)
                            std::cout << ("Data Not Found\n");
                        else
                            std::cout << "Position of Data is " << iValue << std::endl;
                    }     
                    break;

                    case 3:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                        std::cout << "Enter Data To Search :- ";
                        std::cin >> iValue;

                    if(iValue != 0)
                    {
                    iValue = obj1.SearchAllOccurence(iValue);
                        if(iValue == -1)
                            {
                                std::cout << ("List is Empty...\n");
                                break;
                            }
                        std::cout << "Data Found " << iValue << "times\n";
                    }
                    break;

                    case 4:
                        iValue = -2;    
                } 
            }
            }
            else
                obj1.Display();
            break;

            case 4:
                    std::cout << ("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");
                    iValue = obj1.CountNode();
                    std::cout << "Count Of Node is " << iValue << std::endl << std::endl;
                break;
            
            case 5:
            iValue = 1;
            iHold = obj1.ListEmpty();
            if(iHold != 1)
            {
            while(iValue != -2)
                {
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                    std::cout << "|->1.Reverse Display\n";
                    std::cout << "|->2.Physical Reverse\n";
                    std::cout << "|->3.Back\n";
                    std::cout << "Enter Your Choice :- ";
                    std::cin >> iChoice;

                        if(iChoice > 3)
                        {
                            std::cout << "Your Choice is Wrong...\n";
                            continue;
                        }

                    switch(iChoice)
                    {
                        case 1:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                            obj1.ReverseDisplay();
                            break;
                        case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                            obj1.PhysicalReverse();
                            obj1.Display();
                            break;
                        case 3:
                            iValue = -2;
                    }
                }
            }
            else
                obj1.Display();
            break;
            
            case 6:     //concat
            iValue = 1;
            while(iValue != -2)
            {
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                std::cout << "|->1.Concat List\n";
                std::cout << "|->2.Concat At Position\n";
                std::cout << "|->3.Back\n";
                std::cout << "Enter Your Choice :- ";
                std::cin >> iChoice;
                
                if(iChoice > 3)
                {
                    std::cout << "Your Choice is Wrong...\n";
                    continue;
                }

                if(iChoice == 2)
                {
                    iValue = obj1.CountNode();
                    
                    while(iValue != -1)
                    {
                        std::cout << "Enter Your Position :- ";
                        std::cin >> iHold;

                    if(iHold <= 0 || iHold > iValue+1)
                    {
                        printf("Position is Invalid\n");
                        continue;
                    }
                    break;
                    }
                }

                switch(iChoice)
                {
                case 1:
                    iValue = 0;
                    iHold = obj2.CountNode();
                    if(iHold == 0)
                    {
                        while(iValue != -1)
                        {
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                            std::cout << "|->  1.Insert First\n";
                            std::cout << "|->  2.Insert Last\n";
                            std::cout << "|->  3.Insert At Position\n";
                            std::cout << "|->  4.Back\n";
                        std::cout << "Enter Your Choice :- ";
                        std::cin >> iChoice;
                        
                        if(iChoice > 4)
                            {
                                std::cout << "Your Choice is Wrong...\n";
                                continue;
                            }
                        switch(iChoice)
                        {
                            case 1:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                std::cout << "\nEnter Your Data :- ";
                                std::cin >> iValue;
                                
                                if(iValue > 0)
                                {
                                    obj2.InsertFirst(iValue);
                                    obj2.Display();
                                }
                            break;

                            case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                std::cout << "\nEnter Your Data :- ";
                                std::cin >> iValue;
                                
                                if(iValue > 0)
                                {
                                    obj2.InsertLast(iValue);
                                    obj2.Display();
                                }
                                break;

                                case 3:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter The Position :- ";
                                    std::cin >> iPos;
            
                                    iValue = obj2.CountNode();
                                    if(iPos < 0 || iPos > iValue+1)
                                    {
                                        std::cout << ("Position is invalid\n");
                                        continue;
                                    }

                                    std::cout << "Enter Your Data :- ";
                                    std::cin >> iValue;
                                    
                                    if(iValue > 0)
                                    {
                                        obj2.InsertAtPosition(iValue , iPos);
                                        obj2.Display();
                                    }                                    
                                break;

                                case 4:
                                    iValue = -1;
                            }
                    }        
                obj1.ConcatList(obj2);
                obj1.Display();
                }
                break;
    
                case 2:
                std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                iValue = obj1.CountNode();
                    
                    if(iValue == 0)
                        {
                            std::cout << "Your First List is Empty...\n";
                            break;
                        }
                iValue = obj2.CountNode();

                if(iValue == 0)
                {
                        while(iValue != -1)
                        {
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                            std::cout << "|->  1.Insert First\n";
                            std::cout << "|->  2.Insert Last\n";
                            std::cout << "|->  3.Insert At Position\n";
                            std::cout << "|->  4.Back\n";

                        std::cout << "Enter Your Choice :- ";
                        std::cin >> iChoice;

                            if(iChoice > 4)
                            {
                                std::cout << "Your Choice is Wrong...\n";
                                continue;
                            }        

                        switch(iChoice)
                        {
                            case 1:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter Your Data :- ";
                                    std::cin >> iValue;

                                    if(iValue > 0)
                                    {
                                        obj2.InsertFirst(iValue);
                                        obj2.Display();
                                    }
                            break;

                            case 2:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter Your Data :- ";
                                    std::cin >> iValue;
                                    
                                    if(iValue > 0)
                                    {
                                        obj2.InsertLast(iValue);
                                        obj2.Display();
                                    }
                                break;

                                case 3:
                    std::cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";
                                    std::cout << "\nEnter The Position :- ";
                                    std::cin >> iPos;
                                    
                                   iValue = obj2.CountNode();
                                    if(iPos < 0 || iPos > iValue+1)
                                    {
                                        std::cout << ("Position is invalid\n");
                                        continue;
                                    }

                                    std::cout << "Enter Your Data :- ";
                                    std::cin >> iValue;

                                    if(iValue > 0)
                                    {
                                        obj2.InsertAtPosition(iValue  , iPos);
                                        obj2.Display();
                                    }
                                break;
                                case 4:
                                    iValue = -1;
                        }
                    }        
                    obj1.ConcatAtPosition(obj2 ,iHold);
                    obj1.Display();
                }
                break;

                case 3:
                    iValue = -2;
                }
            }
            break;

            case 7:
                std::cout << "exiting....\n";
                iValue = -1;
        }
        break;
    }
    }

    std::cout << obj1 << obj2;

    return 0;
}