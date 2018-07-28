#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"
#include "Exception.h"

namespace DTLib
{

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template< typename T >
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode()
    {
        left = NULL;
        right = NULL;
    }

    static BTreeNode<T>* NewNode()  // 工厂方法
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

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


#endif // BTREENODE_H
