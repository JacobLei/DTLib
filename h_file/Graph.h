#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"

namespace DTLib
{

template < typename E >
struct Edge : public Object
{
    int b;      // 起点
    int e;      // 终点
    E data;     // 权值

    Edge(int i = -1, int j = -1)
    {
        b = i;
        e = j;
    }

    Edge(int i, int j, const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator == (const Edge<E>& obj)
    {
        return (this->b == obj.b) && (this->e == obj.e);
    }

    bool operator != (const Edge<E>& obj)
    {
        return !( *this == obj );
    }
};

template < typename V, typename E >
class Graph : public Object
{
protected:
    template < typename T >
    DynamicArray<T>* toArray(LinkQueue<T>& queue)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(queue.length());

        if( ret != NULL )
        {
            for(int i=0; i<ret->length(); ++i, queue.remove())
            {
                ret->set(i, queue.front());
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create a ret object ... ");
        }

        return ret;
    }

public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E& value) = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;

    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }

    SharedPointer< Array<int> > BFS(int i)
    {
        DynamicArray<int>* ret = NULL;

        if( (i <= 0) && (i < vCount()) )
        {
            LinkQueue<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visted(vCount());

            // 初始化设置，标记数组中的每一个都没有被访问
            for(int j=0; j<visted.length(); ++j)
            {
                visted[j] = false;
            }

            q.add(i);

            while( q.length() > 0 )
            {
                int v = q.front();      // 拿出队列头部的顶点

                q.remove();

                if( !visted[v] )        // 判断是否被访问
                {
                    SharedPointer< Array<int> > aj = getAdjacent(v);

                    for(int j=0; j<aj->length(); ++j)
                    {
                        q.add((*aj)[j]);
                    }

                    r.add(v);
                    visted[v] = true;
                }
            }

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Index i is invalid ... ");
        }

        return ret;
    }

};

}

#endif // GRAPH_H
