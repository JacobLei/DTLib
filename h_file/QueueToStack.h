#ifndef QUEUETOSTACK_H
#define QUEUETOSTACK_H

#include "Stack.h"
#include "LinkQueue.h"

namespace DTLib
{

template < typename T >
class QueueToStack : public Stack<T>
{
protected:
    LinkQueue<T> m_queue_1;
    LinkQueue<T> m_queue_2;
    LinkQueue<T>* m_pIn;        // 进队列指针
    LinkQueue<T>* m_pOut;       // 出队列指针
    void move() const;          // O(n)
    void swap();                // O(1)

public:
    QueueToStack();             // O(1)
    void push (const T& e);     // O(1)
    void pop();                 // O(n)
    T top() const;              // O(n)
    void clear();               // O(n)
    int size() const;           // O(1)
};

template < typename T >
QueueToStack<T>::QueueToStack()
{
    m_pIn = &m_queue_1;
    m_pOut = &m_queue_2;
}

template < typename T >
void QueueToStack<T>::move() const
{
    int n = m_pIn->length() - 1;

    for(int i=0; i<n; ++i)
    {
        m_pOut->add(m_pIn->front());
        m_pIn->remove();
    }
}

template < typename T >
void QueueToStack<T>::swap()
{
    LinkQueue<T>* temp = NULL;

    temp = m_pIn;
    m_pIn = m_pOut;
    m_pOut = temp;
}

template < typename T >
void QueueToStack<T>::push (const T& e)
{
    m_pIn->add(e);
}

template < typename T >
void QueueToStack<T>::pop()
{
    if( m_pIn->length() > 0 )
    {
        move();

        m_pIn->remove();

        swap();
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current stack");
    }
}

template < typename T >
T QueueToStack<T>::top() const
{
    if( m_pIn->length() > 0 )
    {
        move();

        return m_pIn->front();
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current stack");
    }
}

template < typename T >
void QueueToStack<T>::clear()
{
    m_pIn->clear();
    m_pOut->clear();
}

template < typename T >
int QueueToStack<T>::size() const
{
    return m_pIn->length() + m_pOut->length();
}


}


#endif // QUEUETOSTACK_H
