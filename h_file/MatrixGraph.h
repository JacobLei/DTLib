#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace DTLib
{

template < int N, typename V, typename E >
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;
public:
    MatrixGraph()
    {
        for(int i=0; i<vCount(); ++i)
        {
            m_vertexes[i] = NULL;

            for(int j=0; j<vCount(); ++j)
            {
                m_edges[i][j] = NULL;
            }
        }

        m_eCount = 0;
    }

    V getVertex(int i)
    {
        V ret;

        if( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Index i is invalid ...");
        }

        return ret;
    }

    bool getVertex(int i, V& value)
    {
        bool ret = ( (0 <= i) && (i < vCount()) );

        if( ret )
        {
            if( m_vertexes[i] != NULL )     // 顶点有绑定数据元素
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationExcetion, "No value assigned to this vertex...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = ( (0 <= i) && (i < vCount()) );

        if( ret )
        {
            V* data = m_vertexes[i];    // 用临时遍历data来保证异常安全

            if( data == NULL )
            {
                data = new V();
            }

            if( data != NULL )
            {
                *data = value;          // 如果data发生异常，则异常返回，不会影响到m_vertexes[i]

                m_vertexes[i] = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to store new vertex value...");
            }

        }

        return ret;
    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret = NULL;

        if( (0 <= i) && (i < vCount()) )
        {
            // 记录有多少个顶点与之相连
            int count = 0;
            for(int j=0; j<vCount(); ++j)
            {
                if( m_edges[i][j] != NULL )
                {
                    ++count;
                }
            }

            ret = new DynamicArray<int>(count);

            if( ret != NULL )
            {
                for(int j=0, k=0; j<vCount(); ++j)  // 记录顶点的位置
                {
                    if( m_edges[i][j] != NULL )
                    {
                        ret->set(k++, j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create a dynamic array...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Index i is invalid ...");
        }

        return ret;
    }

    E getEdge(int i, int j)
    {
        E ret;

        if( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Index <i,j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)
    {
        bool ret = (((0 <= i) && (i < vCount()))
                    && ((0 <= i) && (i < vCount())));

        if( ret )
        {
            if( m_edges[i][j] != NULL )     // 顶点之间有边
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationExcetion, "No value assigned to this edge...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        bool ret = (((0 <= i) && (i < vCount()))
                    && ((0 <= i) && (i < vCount())));

        if( ret )
        {
            E* ne = m_edges[i][j];

            if( ne == NULL )
            {
                ne = new E();

                if( ne != NULL )
                {
                    *ne = value;

                    m_edges[i][j] = ne;

                    ++m_eCount;
                }
                else
                {
                     THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to store new edge value...");
                }
            }
            else
            {
                *ne = value;
            }

        }

        return ret;
    }

    bool removeEdge(int i, int j)
    {
        bool ret = (((0 <= i) && (i < vCount()))
                    && ((0 <= i) && (i < vCount())));

        if( ret )
        {
            E* toDel = m_edges[i][j];

            m_edges[i][j] = NULL;

            if( toDel != NULL )
            {
                --m_eCount;

                delete toDel;
            }
        }

        return ret;
    }

    int vCount()
    {
        return N;
    }

    int eCount()
    {
        return m_eCount;
    }

    int OD(int i)
    {
        int ret = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            for(int j=0; j<vCount(); ++j)
            {
                if( m_edges[i][j] != NULL )
                {
                    ++ret;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Index i is invalid ...");
        }

        return ret;
    }

    int ID(int i)
    {
        int ret = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            for(int j=0; j<vCount(); ++j)
            {
                if( m_edges[j][i] != NULL )
                {
                    ++ret;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Index i is invalid ...");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for(int i=0; i<vCount(); ++i)
        {
            for(int j=0; j<vCount(); ++j)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }
    }

};

}

#endif // MATRIXGRAPH_H
