#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class TreeNode : public Object
{
protected:
    bool m_flag;

    TreeNode(const TreeNode<T>& obj);
    TreeNode<T>& operator = (const TreeNode<T>& obj);

    void* operator new(unsigned int size) throw()   // 将new设置为保护成员函数
    {
        return Object::operator new(size);
    }

public:
    T value;
    TreeNode<T>* parent;

    TreeNode()
    {
        m_flag = false;
        parent = NULL;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template < typename T >
TreeNode<T>::~TreeNode()
{

}

}


#endif // TREENODE_H
