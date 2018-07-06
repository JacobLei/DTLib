#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class List : public Object
{
protected:
    List(const List&);
    List& operator= (const List& obj);
public:
    List() {}
    virtual bool insert(const T& e) = 0;      // 线性表尾部插入元素
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e) const = 0;
    virtual int find(const T& e) const = 0;     // 查找元素是否在List中，有返回元素第一次出现的位置，无返回-1
    virtual int length() const = 0;
    virtual void clear() = 0;
};

}

#endif // LIST_H
