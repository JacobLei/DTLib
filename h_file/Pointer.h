#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* p = NULL);

    T* operator-> ();
    T* operator* ();
    bool isNull();
    T* get();
};

template < typename T >
Pointer<T>::Pointer(T* p)
{
    m_pointer = p;
}

template < typename T >
T* Pointer<T>::operator-> ()
{
    return m_pointer;
}

template < typename T >
T* Pointer<T>::operator* ()
{
    return *m_pointer;
}

template < typename T >
bool Pointer<T>::isNull()
{
    return (m_pointer == NULL);
}

template < typename T >
T* Pointer<T>::get()
{
    return m_pointer;
}

}


#endif // POINTER_H
