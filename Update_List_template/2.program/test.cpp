#include <iostream>

class demo
{
    int iNo1;
    int iNo2;
    public:
    demo(int No1 = 10 , int No2 = 20)
	{
		iNo1 = No1;
		iNo2 = No2;
	}

    void Display()
    {
        std::cout << iNo1 << std::endl;
        std::cout << iNo2 << std::endl;
    }

    demo& operator ++()
    {
        std::cout << "In pre-increment operator\n" << iNo1 << iNo2 << std::endl;
        ++iNo1;
        ++iNo2;
        return *this;	
    } 

    demo operator ++(int)
    {
        std::cout << "In Post-increment operator\n" << iNo1 << iNo2 << std::endl;
        demo temp(iNo1 , iNo2);
        std::cout << "In Post-increment operator\n" << iNo1 << iNo2 << std::endl;
        ++iNo1;
        ++iNo2;
        return temp;
    }
};

int main(void)
{
    demo obj(10,20);
    ++obj;
    obj.Display();
    obj++;
    obj.Display();
    return 0;
}