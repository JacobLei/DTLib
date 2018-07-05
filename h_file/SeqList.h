#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class SeqList : public List<T>
{
protected:
    T* m_array;     // 顺序存储空间：由子类分配空间
    int m_length;   // 当前线性表长度
public:
    bool insert(int i, const T& e);
    bool remove(int i);
    bool set(int i, const T& e);
    bool get(int i, T& e) const;
    int length() const;
    void clear();
    /* 顺序存储线性表的数组访问方式 */
    T& operator[] (int i);
    T operator [] (int i) const;
    virtual int capcity() const = 0;
};

template< typename T >
bool SeqList<T>::insert(int i, const T& e)
{
    bool ret = (i >= 0) && (i <= m_length);
    ret = ret && ((m_length) < capcity());

    if( ret )
    {
        for(int pos=m_length; pos > i; --pos)
        {
            m_array[pos] = m_array[pos-1];
        }

        m_array[i] = e;
        ++m_length;
    }

    return ret;
}

template< typename T >
bool SeqList<T>::remove(int i)
{
    bool ret = (i >= 0) && (i < m_length);

    if( ret )
    {
        for(int pos=i; pos<m_length-1; ++pos)
        {
            m_array[pos] = m_array[pos+1];
        }

        --m_length;
    }

    return ret;
}

template< typename T >
bool SeqList<T>::set(int i, const T& e)
{
    bool ret = (i >= 0) && (i < m_length);

    if( ret )
    {
        m_array[i] = e;
    }

    return ret;
}

template< typename T >
bool SeqList<T>::get(int i, T& e) const
{
    bool ret = (i >= 0) && (i < m_length);

    if( ret )
    {
        e = m_array[i];
    }

    return ret;
}

template< typename T >
int SeqList<T>::length() const
{
    return m_length;
}

template< typename T >
T& SeqList<T>::operator[] (int i)
{
    if( (i >= 0) && (i < m_length) )
    {
        return m_array[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalild...");
    }
}

template< typename T >
T SeqList<T>::operator [] (int i) const
{
    return (const_cast<SeqList<T>&>(*this))[i]; // 去掉const属性，调用非const[]重载函数
}


template< typename T >
void SeqList<T>::clear()
{
    m_length = 0;
}

}


#endif // SEQLIST_H
