#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "LinkList.h"

namespace DTLib
{

template < typename T >
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> m_list;
public:
    void push (const T& e);     // O(1)
    void pop();                 // O(1)
    T top() const;              // O(1)
    void clear();               // O(n)
    int size() const;           // O(1)
};

template < typename T >
void LinkStack<T>::push (const T& e)
{
    m_list.insert(0, e);
}

template < typename T >
void LinkStack<T>::pop()
{
    if( m_list.length() > 0 )
    {
        m_list.remove(0);
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current stack ...");
    }
}

template < typename T >
T LinkStack<T>::top() const
{
    if( m_list.length() > 0 )
    {
        return m_list.get(0);
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current stack ...");
    }
}

template < typename T >
void LinkStack<T>::clear()
{
    m_list.clear();
}

template < typename T >
int LinkStack<T>::size() const
{
    return m_list.length();
}

}

#endif // LINKSTACK_H
