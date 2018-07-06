#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct : public Object {
        char reserved[sizeof(T)];
        Node* next;
    } m_header;      // mutable突破const的限制
    int m_length;

    Node* position(int i) const  // 定位元素， 返回i的前一个结点的指针
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int pos=0; pos<i; ++pos)
        {
            ret = ret->next;
        }

        return ret;
    }

public:
    LinkList();
    bool insert(const T& e);
    bool insert(int i, const T& e);
    bool remove(int i);
    bool set(int i, const T& e);
    T get(int i) const;
    bool get(int i, T& e) const;
    int length() const;
    void clear();
    ~LinkList();
};

template < typename T >
LinkList<T>::LinkList()        // 构造函数, 设置成员初始状态
{
    m_header.next = NULL;
    m_length = 0;
}

template <typename T >
bool LinkList<T>::insert(int i, const T& e)
{
    bool ret = ((i >= 0) && (i <= m_length));

    if( ret )
    {
        Node* node = new Node();

        if( node != NULL )
        {
            Node* current = position(i);

            node->value = e;
            node->next = current->next;
            current->next = node;

            ++m_length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to insert new element...");
        }
    }

    return ret;
}

template <typename T>
bool LinkList<T>::insert(const T& e)
{
    return insert(m_length, e);
}

template <typename T>
bool LinkList<T>::remove(int i)
{
    bool ret = ((i >= 0) && (i < m_length));

    if( ret )
    {
        Node* current = position(i);

        Node* toDel = current->next;
        current->next = toDel->next;
        delete toDel;

        --m_length;
    }

    return ret;
}

template < typename T >
bool LinkList<T>::set(int i, const T& e)
{
    bool ret = ((i >= 0) && (i < m_length));

    if( ret )
    {
        position(i)->next->value = e;       // i的位置为current的next
    }

    return ret;
}

template < typename T >
T LinkList<T>::get(int i) const
{
    T ret;

    if( get(i, ret) )
    {
        return ret;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Invaild parameter i to get element...");
    }

    return ret;
}

template < typename T >
bool LinkList<T>::get(int i, T& e) const
{
    bool ret = ((i >= 0) && (i < m_length));

    if( ret )
    {
        e = position(i)->next->value;
    }

    return ret;
}

template < typename T >
int LinkList<T>::length() const
{
    return m_length;
}

template < typename T >
void LinkList<T>::clear()
{
    while( m_header.next )
    {
        Node* toDel = m_header.next;
        m_header.next = toDel->next;
        delete toDel;
    }

    m_length = 0;
}

template < typename T >
LinkList<T>:: ~LinkList()
{
    clear();
}

}

#endif // LINKLIST_H
