#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace DTLib
{

template < typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    int mod(int i) const;
    Node* last() const;  // 获取尾结点的next指针
    void last_to_first() const;      // 用于将单链表的首尾相连

public:
    bool insert(const T& e);
    bool insert(int i, const T& e);
    bool remove(int i);
    bool set(int i, const T& e);
    T get(int i) const;
    bool get(int i, T& e) const;
    int find(const T& e) const;      // 重新实现查找操作
    void clear();
    bool move(int i, int step = 1);
    bool end();
    ~CircleList();
};

template < typename T >
int CircleList<T>::mod(int i) const
{
    return ( (this->m_length == 0) ? 0 : (i % this->m_length) );
}

template < typename T >
typename LinkList<T>::Node* CircleList<T>::last() const
{
    return this->position(this->m_length - 1)->next;
}

template < typename T >
void CircleList<T>::last_to_first() const
{
    last()->next = this->m_header.next;
}

template < typename T >
bool CircleList<T>::insert(const T& e)
{
    return insert(this->m_length, e);
}

template < typename T >
bool CircleList<T>::insert(int i, const T& e)
{
    bool ret = true;

    i = i % (this->m_length + 1);

    // 先用LinkList中的insert()插入将元素插入，
    // 然后判断插入元素是否成功且位置是否为首结点，
    // 如果为首结点，则将尾结点指向首结点
    ret = LinkList<T>::insert(i, e);

    if( ret && (i == 0) )
    {
        last_to_first();
    }

    return ret;
}

template < typename T >
bool CircleList<T>::remove(int i)
{
    bool ret = true;

    i = mod(i);

    if( i == 0 )    // 判断删除位置是否为首结点
    {
        Node* toDel = this->m_header.next;

        if( toDel != NULL)
        {
            this->m_header.next = toDel->next;
            --(this->m_length);

            if( this->m_length > 0 )
            {
                last_to_first();

                if( this->m_current == toDel )
                {
                    this->m_current = toDel->next;
                }
            }
            else    // 当m_length为0时，链表为空
            {
                this->m_header.next = NULL;
                this->m_current = NULL;
            }

            this->destroy(toDel);

        }
        else    //  如果toDel为空，则链表为空，删除失败
        {
            ret = false;
        }

    }
    else
    {
        ret = LinkList<T>::remove(i);
    }

    return ret;
}

template < typename T >
bool CircleList<T>::set(int i, const T& e)
{
    return LinkList<T>::set(mod(i), e);
}

template < typename T >
T CircleList<T>::get(int i) const
{
    return LinkList<T>::get(mod(i));
}

template < typename T >
bool CircleList<T>::get(int i, T& e) const
{
    return LinkList<T>::get(mod(i), e);
}

template < typename T >
int CircleList<T>::find(const T& e) const
{
    // 通过slider指针来遍历链表中的每个元素的value，
    // 若找到，返回i，若没找到，返回-1.
    int ret = -1;
    Node* slider = this->m_header.next;

    for(int i=0; i<this->m_length; ++i)
    {
        if( slider->value == e )
        {
            ret = i;
            break;
        }

        slider = slider->next;
    }

    return ret;
}

template < typename T >
void CircleList<T>::clear()
{
    // 将下标为1的结点循环删除，直到链表中只有一个结点为止，
    // 然后再删除链表中的最后一个结点。
    // 循环删除下标为1的结点而不是循环删除下标为0的结点的原因是：
    // 循环删除下标为0的结点会导致头结点指针和尾结点指针的大量移动
    while(this->m_length > 1)
    {
        remove(1);
    }

    if( this->m_length == 1 )
    {
        Node* toDel = this->m_header.next;

        this->m_header.next = NULL;
        this->m_current = NULL;
        this->m_length = 0;

        this->destroy(toDel);
    }
}

template < typename T >
bool CircleList<T>::move(int i, int step)
{
    return LinkList<T>::move(mod(i), step);
}

template < typename T >
bool CircleList<T>::end()
{
    return (this->m_length == 0) || (this->m_current == NULL);
}

template < typename T >
CircleList<T>::~CircleList()
{
    clear();
}


}
#endif // CIRCLELIST_H
