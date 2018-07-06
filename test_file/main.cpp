#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "SeqList.h"


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

    catch(const Exception& e)
    {
        cout << "catch(const Exception& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
}

/* -----测试抽象SeqList类----- */
void test_seq_list()
{
//    SeqList<int>* q;       // 由于抽象类中含有virtual函数，可定义一个指针指向SeqList<int>
                           // 来测试SeqList.h是否编译通过
}

#include "StaticList.h"
#include "Exception.h"

/* -----测试StaticList类----- */
void test_static_list()
{
    StaticList<int, 5> sl;

    for( int i=0; i<sl.capacity(); ++i)
    {
        sl.insert(i+1);
//        sl[i] = i + 1;    // error: IndexOutOfBoundsException
    }

    for( int i=0; i<sl.capacity(); ++i)  // 4， 3， 2， 1， 0
    {
        cout << sl[i] << endl;
    }

    sl[0] *= sl[0];

    for( int i=0; i<sl.capacity(); ++i)  // 16， 3， 2， 1， 0
    {
        cout << sl[i] << endl;
    }

    try
    {
        sl[5];
    }
    catch(Exception& e)
    {
        cout << e.location() << "----" << e.message() << endl;  // SeqList.h:108----Parameter i is invalid...
    }
}

#include "DynamicList.h"
/* -----测试DynamicList类----- */
void test_dynamic_list()
{
    DynamicList<int> sl(5);

    for( int i=0; i<sl.capacity(); ++i)
    {
        sl.insert(0, i);
    }

    for( int i=0; i<sl.capacity(); ++i)  // 4， 3， 2， 1， 0
    {
        cout << sl[i] << endl;
    }

    sl[0] *= sl[0];

    for( int i=0; i<sl.capacity(); ++i)  // 16， 3， 2， 1， 0
    {
        cout << sl[i] << endl;
    }

    sl.resize(10);

    cout << sl.capacity() << endl;       // 10

}

# include "StaticList.h"
/* -----测试StaticList类中赋值操作----- */
void test_copy_assignment_in_static_list()
{
    StaticList<int*, 5> s1;
    StaticList<int*, 5> s2;

    for(int i=0; i<s1.capacity(); ++i)
    {
        s1.insert(0, new int(i));
    }

//    s2 = s1;

    for(int i=0; i<s1.length(); ++i)
    {
        delete s1[i];
        delete s2[i];   // error:释放类同一块内存空间，因此最好禁用赋值操作
    }
}

#include "DynamicList.h"
/* -----测试DynamicList中拷贝构造----- */
void test_copy_ctor_in_dynamic_list()
{
    DynamicList<int> d1(5);
//    DynamicList<int> d2 = d1;   // error:d1和d2为潜拷贝，两个对象操作同一块内存地址
                                //       当调用析构函数时，会释放同一块内存空间。
                                //       因此，最好禁用拷贝构造。
}

#include "StaticArray.h"
/* -----测试StaticArray函数----- */
void test_static_array()
{
    StaticArray<int, 5> s1;

    for(int i=0; i<s1.length(); ++i)
    {
        s1[i] = i * i;
    }

    for(int i=0; i<s1.length(); ++i)
    {
        cout << s1[i] << " ";           // 0 1 4 9 16
    }

    cout << endl;

    StaticArray<int, 5> s2;

    s2 = s1;

    for(int i=0; i<s2.length(); ++i)
    {
        cout << s2[i] << " ";           // 0 1 4 9 16
    }
    cout << endl;

    s2[6] = 100;            // error: IndexOutOfBoundsException
                            // 越界后报异常
}

#include "DynamicArray.h"
/* -----测试DynamicArray函数----- */
void test_dynamic_array()
{
    DynamicArray<int> s1(5);
    DynamicArray<int> s2(10);

    for(int i=0; i<s1.length(); ++i)
    {
        s1[i] = i * i;
    }

    for(int i=0; i<s1.length(); ++i)
    {
        cout << s1[i] << " ";           // 0 1 4 9 16
    }
    cout << endl;

    s2 = s1;
    s2.resize(8);

    for(int i=0; i<s2.length(); ++i)
    {
        cout << s2[i] << " ";           // 0 1 4 9 16 随机数 随机数 随机数
    }

    cout << endl;

//   s2[11] = 100;                       // error: IndexOutOfBoundsException
}

#include "LinkList.h"
/* -----测试LinkList函数----- */
void test_link_list()
{
    LinkList<int> l;

    for(int i=0; i<5; ++i)
    {
        l.insert(i * i);
    }

    for(int i=0; i<l.length(); ++i)
    {
        cout << l.get(i) << ", ";       // 0, 1, 4, 9, 16,
    }
    cout << endl;

    l.remove(2);

    for(int i=0; i<l.length(); ++i)
    {
        cout << l.get(i) << ", ";       // 0, 1, 9, 16,
    }
    cout << endl;

    l.clear();

    cout << l.length() << endl;         // 0
}

int main()
{
//    test_smart_pointer();
//    test_exception();
//    test_seq_list();
//    test_static_list();
//    test_dynamic_list();
//    test_copy_assignment_in_static_list();
//    test_copy_assignment_in_static_list();
//    test_static_array();
//    test_dynamic_array();
    test_link_list();
    return 0;
}
