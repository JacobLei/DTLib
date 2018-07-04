#include "Exception.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

namespace DTLib
{

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
        m_location = strcpy(m_location, file);
        m_location = strcat(m_location, ":");
        m_location = strcat(m_location, sl);
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
