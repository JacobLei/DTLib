#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>

namespace DTLib
{

class Object
{
public:
    void* operator new (unsigned int size) throw(); // throw()表示当前的函数不会抛出任何异常, 即申请内存失败时，返回空值
    void operator delete (void* p);
    void* operator new[] (unsigned int size)  throw();
    void operator delete[] (void* p);

    virtual ~Object() = 0;
};

void* Object::operator new (unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete (void* p)
{
    free(p);
}

void* Object::operator new[] (unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete[] (void* p)
{
    free(p);
}

Object::~Object()
{

}

}


#endif // OBJECT_H
