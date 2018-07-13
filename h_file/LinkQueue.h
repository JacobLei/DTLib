#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "queue"
#include "LinkList.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class LinkQueue : public LinkList<T>
{
protected:
    LinkList<T> m_list;
public:
    LinkQueue();            // O(1)
    void add(const T& e);   // O(n)
    void remove();          // O(1)
    T front() const;        // O(1)
    void clear();           // O(n)
    int length() const;     // O(1)
};

template < typename T >
LinkQueue<T>::LinkQueue()
{
}

template < typename T >
void LinkQueue<T>::add(const T& e)
{
    m_list.insert(e);
}

template < typename T >
void LinkQueue<T>::remove()
{
    if( m_list.length() > 0)
    {
        m_list.remove(0);
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current list queue ...");
    }
}

template < typename T >
T LinkQueue<T>::front() const
{
    if( m_list.length() > 0)
    {
        return m_list.get(0);
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current list queue ...");
    }
}

template < typename T >
void LinkQueue<T>::clear()
{
    m_list.clear();
}

template < typename T >
int LinkQueue<T>::length() const
{
    return m_list.length();
}

}

#endif // LINKQUEUE_H
