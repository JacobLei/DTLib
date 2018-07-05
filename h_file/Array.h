#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class Array : public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int i, const T& e)
    {
        bool ret = (i >= 0) && (i < length());

        if( ret )
        {
            m_array[i] = e;
        }

        return ret;
    }

    virtual bool get(int i, T& e) const
    {
        bool ret = (i >= 0) && (i < length());

        if( ret )
        {
            e = m_array[i];
        }

        return ret;
    }

    T& operator[] (int i)
    {
        if( (i >= 0) && (i < length()) )
        {
            return m_array[i];
        }
        else        // 访问越界，抛出“IndexOutOfBoundsException”异常
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invaild...");
        }
    }

    T operator [](int i) const
    {
        return (const_cast<Array<T>&>(*this))[i];
    }

    virtual int length() const = 0;
};


}

#endif // ARRAY_H
