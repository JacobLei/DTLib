#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib
{

template < typename T, int N >
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;
public:
    StaticStack();              // O(1)
    void push (const T& e);     // O(1)
    void pop();                 // O(1)
    T top() const;              // O(1)
    void clear();               // O(1)
    int size() const;           // O(1)
    int capacity() const;       // O(1)
};

template < typename T, int N >
StaticStack<T,N>::StaticStack()
{
    m_top = -1;
    m_size = 0;
}

template < typename T, int N >
void StaticStack<T,N>::push (const T& e)
{
    if( m_size < N )
    {
        m_space[m_top + 1] = e;     // 异常安全：保证赋值完全正确后，将m_top自增
        ++ m_top;
        ++m_size;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No space in current stack ...");
    }
}

template < typename T, int N >
void StaticStack<T,N>::pop()
{
    if( m_size > 0)
    {
        --m_top;
        --m_size;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current stack ...");
    }
}

template < typename T, int N >
T StaticStack<T,N>::top() const
{
    if( m_size > 0)
    {
        return m_space[m_top];
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current stack ...");
    }
}

template < typename T, int N >
void StaticStack<T,N>::clear()
{
    m_top = -1;
    m_size = 0;
}

template < typename T, int N >
int StaticStack<T,N>::size() const
{
    return m_size;
}

template < typename T, int N >
int StaticStack<T,N>::capacity() const
{
    return N;
}

}

#endif // STATICSTACK_H
