#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace DTLib
{
template < typename T >
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL);
    SmartPointer(const SmartPointer<T>& obj);
    SmartPointer<T>& operator= (const SmartPointer<T>& obj);
    ~SmartPointer();
};

template < typename T >
SmartPointer<T>::SmartPointer(T* p) : Pointer<T>(p)
{

}

/* 拷贝构造函数：一片堆空间最多由智能一个指针标识，防止堆空间重复释放 */
template < typename T >
SmartPointer<T>::SmartPointer(const SmartPointer<T>& obj)
{
    this->m_pointer = obj.m_pointer;           // 将当前对象的指针指向obj对象指针

    /* 为了将一片堆空间最多由一个智能指针标识，需要将obj.m_pointer置空 */
    const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
}

/* 重载赋值操作符：一片堆空间最多由智能一个指针标识，防止堆空间重复释放 */
template < typename T >
SmartPointer<T>& SmartPointer<T>::operator= (const SmartPointer<T>& obj)
{
    if( this != &obj )  // 排除自赋值
    {
        /* 先创建一个指针指向*this中的pointer,
           然后将obj中的pointer赋值给*this的pointer，
           然后将obj中的pointer置为NULL，
           删除临时指针p（保证类异常安全）*/
        T* p = this->m_pointer;
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

        delete p;
    }

    return *this;
}

template < typename T>
SmartPointer<T>::~SmartPointer()
{
    delete this->m_pointer;
}

}

#endif // SMARTPOINTER_H
