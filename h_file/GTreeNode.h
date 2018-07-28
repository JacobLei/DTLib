#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

    static GTreeNode<T>* NewNode()  // 工厂方法
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if( ret != NULL )

        {
            ret->m_flag = true;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create new GTreeNode...");
        }

        return ret;
    }
};

}

#endif // GTREENODE_H
