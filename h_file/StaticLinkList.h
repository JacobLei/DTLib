#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DTLib
{

template < typename T, int N >      // N 为预留空间大小
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    struct SNode : public Node      // 实现new操作符重载函数
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;
            return loc;
        }
    };

    unsigned char m_space[sizeof(Node) * N];    // 在栈中申请连续的所需空间大小
    int m_used[N];          // 标记数组，与m_space空间一一对应，

    Node* create()
    {
        SNode* ret = NULL;

        for(int i=0; i<N; ++i)
        {
            if( !m_used[i] )
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                ret = new(ret)SNode();
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }

    void destroy(Node *pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);
        SNode* psn = dynamic_cast<SNode*>(pn);

        for(int i=0; i<N; ++i)
        {
            if( psn == (space + i) )
            {
                m_used[i] = 0;
                psn->~SNode();       // 调用析构函数
                break;
            }
        }
    }
public:
    StaticLinkList()    // 构造函数：标记每个内存单元可用
    {
        for(int i=0; i<N; ++i)
        {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }
};

}

#endif // STATICLINKLIST_H
