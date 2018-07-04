#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"

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

/* -----测试异常类----- */
void test_exception()
{
    try
    {
        THROW_EXCEPTION(InvalidParameterExcetion, "test");
    }
    catch(const InvalidParameterExcetion& e)
    {
        cout << "catch(const InvalidParameterExcetion& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch(const NoEnoughMemoryExcetion& e)
    {
        cout << "catch(const NoEnoughMemoryExcetion& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch(const IndexOutOfBoundsException& e)
    {
        cout << "catch(const IndexOutOfBoundsException& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch(const NullPointerException& e)
    {
        cout << "catch(const NullPointerException& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch(const ArithmeticException& e)
    {
        cout << "catch(const ArithmeticException& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

    catch(const Exception e)
    {
        cout << "catch(const Exception& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
}

int main()
{
//    test_smart_pointer();
    test_exception();

    return 0;
}
