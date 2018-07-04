#include <iostream>
#include "SmartPointer.h"

using namespace std;
using namespace DTLib;

/* -----测试智能指针----- */
class Test
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }
};

void test_smart_pointer()
{
    SmartPointer<Test> sp = new Test();
    SmartPointer<Test> nsp = new Test();
    nsp = sp;
    cout << sp.isNull() << endl;
    cout << nsp.isNull() << endl;

    /*
      输出结果：
      Test()
      Test()
      ~Test()
      1
      0
      ～Test()
      */
    // 输出结果说明：
    // 1. 测试程序中只new了对象，没有delete对象，但没有造成内存泄漏，
    //    因为智能指针结束时，析构函数中delete类对象；
    // 2. 将nsp = sp时，释放类sp并将sp的指向的对象赋值给了nsp，
    //    因此sp.isNULL为1，nsp.isNULL为0。证明类同一片堆空间最多智能由一个指针标识，
}


int main()
{
    test_smart_pointer();

    return 0;
}

