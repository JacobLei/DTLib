#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace DTLib
{

template < typename T >
class GTree : public Tree<T>
{
protected:
    LinkQueue<GTreeNode<T>*> m_queue;



    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if( node != NULL )
        {
            if( node->value == value )
            {
                return node;
            }
            else
            {
                for(node->child.move(0);
                    !node->child.end() && (ret == NULL);
                    node->child.next())
                {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if( node == obj )
        {
            return node;
        }
        else
        {
            if( node != NULL )
            {
                for(node->child.move(0);
                    !node->child.end() && (ret == NULL);
                    node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }

    void free(GTreeNode<T>* node)
    {
        if( node != NULL )
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }

            if( node->flag() )      // 添加判断条件，如果flag为真，即在堆空间中创建对象，则需要delete空间
            {
                delete node;
            }

        }
    }

    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();

        if( ret != NULL )
        {
            if( root() != node )    // 当node结点不为root()结点时
            {
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;   // 父结点的孩子链表

                child.remove(child.find(node)); // 删除链表中的node结点

                node->parent = NULL;    // 将node结点的parent指针置为空
            }
            else                    // 当node结点为root()结点时
            {
                this->m_root = NULL;
            }

            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create a new tree ...");
        }

    }

    int count(GTreeNode<T>* node) const     // 计算树的结点的功能函数
    {
        int ret = 0;

        if(node != NULL )
        {
            ret = 1;

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int h = height(node->child.current());

                if( ret < h )
                {
                    ret = h;
                }
            }

            ++ret;
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            ret = node->child.length();

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int d = degree(node->child.current());

                if( ret < d )
                {
                    ret = d;
                }
            }
        }

        return ret;
    }

public:
    GTree()
    {

    }

    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        if( node != NULL )
        {
            if( this->m_root == NULL )
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* np = find(node->parent);

                if( np != NULL )
                {
                    // 查找该结点node是否已经在树中
                    // 若已经在树中，则不需要插入node结点
                    // 查找方法为：在node的父结点np中的子链表中查找(这个方法高效)

                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);

                    if( np->child.find(n) < 0 )  // 如果没有在链表中没有找到，则插入该链表中
                    {
                        np->child.insert(n);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterExcetion, "Invalid parent tree node ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter node cannot be NULL ...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;

        GTreeNode<T>* node = GTreeNode<T>::NewNode();   // 使用工厂方法

        if( node != NULL )
        {
            node->value = value;
            node->parent = parent;

            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create new GTreeNode...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
         GTree<T>* ret;
         GTreeNode<T>* node = find(value);

         if( node != NULL )
         {
             remove(node, ret);

             m_queue.clear();
         }
         else
         {
             THROW_EXCEPTION(InvalidParameterExcetion, "Can not find node via value...");
         }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret;

        if( find(node) != NULL )
        {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);

            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter node invalid...");
        }

       return ret;
    }

    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }
    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());

        this->m_root = NULL;

        m_queue.clear();
    }

    bool begin()
    {
        bool ret = ( root() != NULL );      // 判断根结点不为空

        if( ret )
        {
            m_queue.clear();        // 先清空队列

            m_queue.add(root());    // 将根结点添加到队列中
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if( ret )
        {
            GTreeNode<T>* node = m_queue.front();   // 取出对头元素

            m_queue.remove();

            for(node->child.move(0); !node->child.end(); node->child.next())    // 将对头元素的子结点压入队列中
            {
                m_queue.add(node->child.current());
            }
        }

        return ret;
    }

    T current()
    {
        if( !end() )
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationExcetion, "No value at current position...");
        }

    }

    ~GTree()
    {
        clear();
    }

};

}

#endif // GTREE_H
