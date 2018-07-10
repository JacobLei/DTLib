#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
        Node* pre;
    };

    mutable struct : public Object {
        char reserved[sizeof(T)];
        Node* next;
        Node* pre;
    } m_header;      // mutable突破const的限制
    int m_length;
    Node* m_current;    // 定义游标 m_current
    int m_step;
    Node* position(int i) const;  // 定位元素， 返回i的前一个结点的指针
    virtual Node* create();      // 内部进行create封装
    virtual void destroy(Node* pn);     // 内部进行destroy封装

public:
    DualLinkList();
    bool insert(const T& e);               // O(n)
    bool insert(int i, const T& e);        // O(n)
    bool remove(int i);                    // O(n)
    bool set(int i, const T& e);           // O(n)
    virtual T get(int i) const;            // O(n)
    bool get(int i, T& e) const;           // O(n)
    int find(const T &e) const;            // O(n)
    int length() const;                    // O(1)
    void clear();                          // O(n)

    /* 游标遍历相关函数 */
    virtual bool move(int i, int step);
    virtual bool end();
    virtual bool next();
    virtual bool pre();
    virtual T current();
    ~DualLinkList();
};

template < typename T >
DualLinkList<T>::DualLinkList()        // 构造函数, 设置成员初始状态
{
    m_header.next = NULL;
    m_header.pre = NULL;
    m_length = 0;
    m_step = 1;
    m_current = NULL;
}

template < typename T>
typename DualLinkList<T>::Node* DualLinkList<T>::position(int i) const
{
    Node* ret = reinterpret_cast<Node*>(&m_header);

    for(int pos=0; pos<i; ++pos)
    {
        ret = ret->next;
    }

    return ret;
}

template < typename T >
typename DualLinkList<T>::Node* DualLinkList<T>::create()
{
    return new Node();
}

template < typename T >
void DualLinkList<T>::DualLinkList::destroy(Node* pn)
{
    delete pn;
}

template <typename T >
bool DualLinkList<T>::insert(int i, const T& e)
{
    bool ret = ((i >= 0) && (i <= m_length));

    if( ret )
    {
        Node* node = create();

        if( node != NULL )
        {
            Node* current = position(i);
            Node*  next = current->next;

            node->value = e;
            node->next = next;
            current->next = node;

            if( current != reinterpret_cast<Node*>(&m_header) ) // 判断current结点是否为头结点
            {
                node->pre = current;    // 如果不是头结点，则将node->pre = current
            }
            else
            {
                node->pre = NULL;   // 如果是头结点，则node->pre = NULL
            }

            if( next != NULL )
            {
                next->pre = node;   // 如果next不为空，将next->pre = node；如果next为空，则什么也不用做
            }

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
bool DualLinkList<T>::insert(const T& e)
{
    return insert(m_length, e);
}

template <typename T>
bool DualLinkList<T>::remove(int i)
{
    bool ret = ((i >= 0) && (i < m_length));

    if( ret )
    {
        Node* current = position(i);
        Node* toDel = current->next;
        Node* next = toDel->next;

        if(  m_current == toDel )       // 如果游标指针指向要删除的指针
        {
            m_current = toDel->next;    // 移动游标指针
        }

        current->next = next;
        if( next != NULL )
        {
            next->pre = toDel->pre;
        }

        --m_length;                     // 先将length-1
        destroy(toDel);                 // 然后再destroy对象，因为如果destroy如果出现异常，此时的length信息还是正确的
    }

    return ret;
}

template < typename T >
bool DualLinkList<T>::set(int i, const T& e)
{
    bool ret = ((i >= 0) && (i < m_length));

    if( ret )
    {
        position(i)->next->value = e;       // i的位置为current的next
    }

    return ret;
}

template < typename T >
T DualLinkList<T>::get(int i) const
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
bool DualLinkList<T>::get(int i, T& e) const
{
    bool ret = ((i >= 0) && (i < m_length));

    if( ret )
    {
        e = position(i)->next->value;
    }

    return ret;
}

template < typename T >
int DualLinkList<T>::find(const T &e) const
{
    int ret = -1;
    int pos = 0;
    Node* node = m_header.next;

    while( node )
    {
        if( node->value == e )
        {
            ret = pos;
            break;
        }
        else
        {
            node = node->next;
            ++pos;
        }
    }

    return ret;
}

template < typename T >
int DualLinkList<T>::length() const
{
    return m_length;
}

template < typename T >
void DualLinkList<T>::clear()
{
    while( this->m_length > 0 )
    {
        remove(0);
    }
}

template < typename T >
bool DualLinkList<T>::move(int i, int step = 1)
{
    bool ret = (i >= 0) && (i < m_length) && (step > 0);

    if( ret )
    {
        m_current =position(i)->next;
        m_step = step;
    }

    return ret;
}

template < typename T >
bool DualLinkList<T>::end()
{
    return m_current == NULL;
}

template < typename T >
bool DualLinkList<T>::next()
{
    int i = 0;

    while( ( i<m_step ) && ( !end() ) )
    {
        m_current = m_current->next;
        ++i;
    }

    return (i == m_step);
}

template < typename T >
bool DualLinkList<T>::pre()
{
    int i = 0;

    while( ( i<m_step ) && ( !end() ) )
    {
        m_current = m_current->pre;
        ++i;
    }

    return (i == m_step);
}

template < typename T >
T DualLinkList<T>::current()
{
    if( !end() )
    {
        return m_current->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationExcetion, "No value at current position...");
    }
}

template < typename T >
DualLinkList<T>:: ~DualLinkList()
{
    clear();
}

}


#endif // DUALLINKLIST_H
