#ifndef STACKTOQUEUE_H
#define STACKTOQUEUE_H

#include "LinkStack.h"
#include "Queue.h"

namespace DTLib
{

template < typename T >
class StackToQueue : public Queue<T>
{
protected:
    mutable LinkStack<T> m_stack_in;
    mutable LinkStack<T> m_stack_out;
    void move() const;      // O(n)
public:
    void add(const T& e);   // O(1)
    void remove();          // O(n)
    T front() const;        // O(n)
    void clear();           // O(n)
    int length() const;     // O(1)
};

template < typename T >
void StackToQueue<T>::move() const
{
    if( m_stack_out.size() == 0)
    {
        while( m_stack_in.size() > 0 )
        {
            m_stack_out.push(m_stack_in.top());
            m_stack_in.pop();
        }
    }
}

template < typename T >
void StackToQueue<T>::add(const T& e)
{
    m_stack_in.push(e);
}

template < typename T >
void StackToQueue<T>::remove()
{
    move();

    if( m_stack_out.size() > 0 )
    {
        m_stack_out.pop();
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current queue...");
    }
}

template < typename T >
T StackToQueue<T>::front() const
{
    move();

    if( m_stack_out.size() > 0 )
    {
        return m_stack_out.top();
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current queue...");
    }
}

template < typename T >
void StackToQueue<T>::clear()
{
    m_stack_in.clear();
    m_stack_out.clear();
}

template < typename T >
int StackToQueue<T>::length() const
{
    return m_stack_in.size() + m_stack_out.size();
}

}
#endif // STACKTOQUEUE_H
