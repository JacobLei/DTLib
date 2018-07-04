#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

namespace DTLib
{
template < typename T >
class SmartPointer : public Object
{
protected:
    T* m_pointer;

public:
    SmartPointer(T* p = NULL)
    {
        m_pointer = p;
    }

    /* 拷贝构造函数：一片堆空间最多由智能一个指针标识，防止堆空间重复释放 */
    SmartPointer(const SmartPointer<T>& obj)
    {
        m_pointer = obj.m_pointer;           // 将当前对象的指针指向obj对象指针

        /* 为了将一片堆空间最多由一个智能指针标识，需要将obj.m_pointer置空 */
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    /* 重载赋值操作符：一片堆空间最多由智能一个指针标识，防止堆空间重复释放 */
    SmartPointer<T>& operator= (const SmartPointer<T>& obj)
    {
        if( this != &obj )  // 排除自赋值
        {
            /* 先删除*this中的pointer, 然后将obj中的pointer赋值*this的pointer */
            delete m_pointer;

            m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }

        return *this;
    }

    T* operator->()
    {
        return m_pointer;
    }

    T& operator*()
    {
        return *m_pointer;
    }

    bool isNull()
    {
        return m_pointer == NULL;
    }

    T* get()
    {
        return m_pointer;
    }

    ~SmartPointer()
    {
        delete m_pointer;
    }
};

}


#endif // SMARTPOINTER_H
