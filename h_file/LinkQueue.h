#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "LinuxList.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class LinkQueue : public Queue<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    int m_length;

public:
    LinkQueue();            // O(1)
    void add(const T& e);   // O(1)
    void remove();          // O(1)
    T front() const;        // O(1)
    void clear();           // O(n)
    int length() const;     // O(1)
    ~LinkQueue();           // O(n)
};

template < typename T >
LinkQueue<T>::LinkQueue()
{
    INIT_LIST_HEAD(&m_header);
    m_length = 0;
}

template < typename T >
void LinkQueue<T>::add(const T& e)
{
    Node* node = new Node();

    if( node != NULL)
    {
        node->value = e;
        list_add_tail(&(node->head), &m_header);
        ++m_length;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to add new element in LinkQueue...");
    }
}

template < typename T >
void LinkQueue<T>::remove()
{
    if( m_length > 0)
    {
        list_head* toDel = m_header.next;
        list_del(toDel);
        --m_length;
        delete list_entry(toDel, Node, head);
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current list queue ...");
    }
}

template < typename T >
T LinkQueue<T>::front() const
{
    if( m_length > 0)
    {
        return list_entry(m_header.next, Node, head)->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No element in current list queue ...");
    }
}

template < typename T >
void LinkQueue<T>::clear()
{
    while( m_length > 0)
    {
        remove();
    }
}

template < typename T >
int LinkQueue<T>::length() const
{
    return m_length;
}

template < typename T >
LinkQueue<T>::~LinkQueue()
{
    clear();
}

}

#endif // LINKQUEUE_H
