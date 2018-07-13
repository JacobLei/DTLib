#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace DTLib
{

template < typename T, int N >
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_length;
public:
    StaticQueue();
    void add(const T& e);
    void remove();
    T front() const;
    void clear();
    int length() const;
    int capacity() const;
};

template <typename T, int N >
StaticQueue<T, N>::StaticQueue()
{
    m_rear = 0;
    m_front = 0;
    m_length = 0;
}

template <typename T, int N >
void StaticQueue<T, N>::add(const T& e)
{
    if( m_length < N )
    {
        m_space[m_rear] = e;
        m_rear = ( m_rear + 1 ) % N;
        ++m_length;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "Not space add queue...");
    }
}

template <typename T, int N >
void StaticQueue<T, N>::remove()
{
    if( m_length > 0 )
    {
        m_front = (m_front + 1) % N;
        --m_length;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "Not element remove queue...");
    }
}

template <typename T, int N >
T StaticQueue<T, N>::front() const
{
    if( m_length > 0 )
    {
        return m_space[m_front];
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "Not element remove queue...");
    }
}

template <typename T, int N >
void StaticQueue<T, N>::clear()
{
    m_rear = 0;
    m_front = 0;
    m_length = 0;
}

template <typename T, int N >
int StaticQueue<T, N>::length() const
{
    return m_length;
}

template <typename T, int N >
int StaticQueue<T, N>::capacity() const
{
    return N;
}


}

#endif // STATICQUEUE_H
