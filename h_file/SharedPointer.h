#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "cstdlib"
#include "Exception.h"
#include "Pointer.h"

namespace DTLib
{

template < typename T >
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;     // 计数机制成员指针
    void assign(const SharedPointer<T>& obj);
public:
    SharedPointer(T* p = NULL);
    SharedPointer(const SharedPointer<T>& obj);
    SharedPointer<T>& operator= (const SharedPointer<T>& obj);
    void clear();   // 将当前指针置为空
    ~SharedPointer();
};

template < typename T >
SharedPointer<T>::SharedPointer(T* p) : m_ref(NULL)
{
    if( p )
    {
        this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));

        if( this->m_ref )
        {
            *(this->m_ref) = 1;
            this->m_pointer = p;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create sharedpointer obj...");
        }
    }
}

template < typename T >
void SharedPointer<T>::assign(const SharedPointer<T>& obj)
{
    this->m_ref = obj.m_ref;
    this->m_pointer = obj.m_pointer;

    if( this->m_ref )
    {
        ++(*this->m_ref);
    }
}

template < typename T >
SharedPointer<T>::SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
{
    assign(obj);
}

template < typename T >
SharedPointer<T>& SharedPointer<T>::operator= (const SharedPointer<T>& obj)
{
    if( this != &obj )
    {
        clear();
        assign(obj);
    }

    return *this;
}

template < typename T >
void SharedPointer<T>::clear()
{
    T* toDel = this->m_pointer;
    int* ref = this->m_ref;

    this->m_pointer = NULL;
    this->m_ref = NULL;

    if( ref )
    {
        --(*ref);

        if( *ref == 0 )
        {
            free(ref);

            delete toDel;
        }
    }
}

template < typename T >
SharedPointer<T>::~SharedPointer()
{
    clear();
}

/* 通过全局函数重载 == 操作符*/
template < typename T >
bool operator== (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return l.get() == r.get();
}

/* 通过全局函数重载 != 操作符*/
template < typename T >
bool operator!= (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return !(l == r);
}

}

#endif // SHAREDPOINTER_H
