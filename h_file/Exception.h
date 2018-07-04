#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "Object.h"

using namespace std;

namespace DTLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
protected:
    char* m_message;    // 指向一个字符串，字符串用于说明当前异常的详细信息
    char* m_location;   // 指向一个字符串，字符串用于说明当前异常发生的地点

    void init(const char* message, const char* file, int line);  // 辅助构造函数进行初始化
public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator= (const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0;
};

class ArithmeticException : public Exception
{
public:
    ArithmeticException()
        : Exception(0)
    {

    }

    ArithmeticException(const char* message)
        : Exception(message)
    {

    }

    ArithmeticException(const char *file, int line)
        : Exception(file, line)
    {

    }

    ArithmeticException(const char* message, const char* file, int line)
        : Exception(message, file, line)
    {

    }

    ArithmeticException(const ArithmeticException& e)
        : Exception(e)
    {

    }

    ArithmeticException& operator =(const ArithmeticException& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class NullPointerException : public Exception
{
public:
    NullPointerException()
        : Exception(0)
    {

    }

    NullPointerException(const char* message)
        : Exception(message)
    {

    }

    NullPointerException(const char *file, int line)
        : Exception(file, line)
    {

    }

    NullPointerException(const char* message, const char* file, int line)
        : Exception(message, file, line)
    {

    }

    NullPointerException(const NullPointerException& e)
        : Exception(e)
    {

    }

    NullPointerException& operator =(const NullPointerException& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException()
        : Exception(0)
    {

    }

    IndexOutOfBoundsException(const char* message)
        : Exception(message)
    {

    }

    IndexOutOfBoundsException(const char *file, int line)
        : Exception(file, line)
    {

    }

    IndexOutOfBoundsException(const char* message, const char* file, int line)
        : Exception(message, file, line)
    {

    }

    IndexOutOfBoundsException(const IndexOutOfBoundsException& e)
        : Exception(e)
    {

    }

    IndexOutOfBoundsException& operator =(const IndexOutOfBoundsException& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class NoEnoughMemoryExcetion : public Exception
{
public:
    NoEnoughMemoryExcetion()
        : Exception(0)
    {

    }

    NoEnoughMemoryExcetion(const char* message)
        : Exception(message)
    {

    }

    NoEnoughMemoryExcetion(const char *file, int line)
        : Exception(file, line)
    {

    }

    NoEnoughMemoryExcetion(const char* message, const char* file, int line)
        : Exception(message, file, line)
    {

    }

    NoEnoughMemoryExcetion(const NoEnoughMemoryExcetion& e)
        : Exception(e)
    {

    }

    NoEnoughMemoryExcetion& operator =(const NoEnoughMemoryExcetion& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class InvalidParameterExcetion : public Exception
{
public:
    InvalidParameterExcetion()
        : Exception(0)
    {

    }

    InvalidParameterExcetion(const char* message)
        : Exception(message)
    {

    }

    InvalidParameterExcetion(const char *file, int line)
        : Exception(file, line)
    {

    }

    InvalidParameterExcetion(const char* message, const char* file, int line)
        : Exception(message, file, line)
    {

    }

    InvalidParameterExcetion(const InvalidParameterExcetion& e)
        : Exception(e)
    {

    }

    InvalidParameterExcetion& operator =(const InvalidParameterExcetion& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class InvalidOperationExcetion : public Exception
{
public:
    InvalidOperationExcetion()
        : Exception(0)
    {

    }

    InvalidOperationExcetion(const char* message)
        : Exception(message)
    {

    }

    InvalidOperationExcetion(const char *file, int line)
        : Exception(file, line)
    {

    }

    InvalidOperationExcetion(const char* message, const char* file, int line)
        : Exception(message, file, line)
    {

    }

    InvalidOperationExcetion(const InvalidOperationExcetion& e)
        : Exception(e)
    {

    }

    InvalidOperationExcetion& operator =(const InvalidOperationExcetion& e)
    {
        Exception::operator =(e);

        return *this;
    }
};


void Exception::init(const char *message, const char *file, int line)
{
    /*
     * m_message = message; // 这样赋值是不安全的，参数 message 指向的字符串位置不缺定，
     *                      // 可能位于栈空间、可能位于堆空间、也可能位于静态存储区，
     *                      // 无法知道message的生命周期。
     *                      // 解决方案：使用strdup函数，在堆空间中申请内存，拷贝字符串。
     */
    m_message = strdup(message);

    if ( file != NULL )
    {
        char sl[16] = {0};

        sprintf(sl, "%d", line); // 将line从int转换为字符数组，并且存储于sl中。
                                 // 在Linux环境下没有itoa函数，因此需要用sprintf函数替代，并包含<cstdio>头文件
        /* 接下来将异常的文件名和行号拼接
            通过malloc申请一片内存空间，
            大小为strlen(file)+strlen(sl)+2
         */
        m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) +2));

        /* 判断malloc是否申请成功 */
        if( m_location != NULL )
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, sl);
        }
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char* message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char* file, int line)
{
    init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
    init(message, file , line);
}

Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception& Exception::operator= (const Exception& e)
{
    if( this != &e )
    {
        free(m_message);
        free(m_location);

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    return *this;
}

const char* Exception::message() const
{
    return m_message;
}
const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}


#endif // EXCEPTION_H
