#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace DTLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception
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

    virtual ~Exception();
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

}


#endif // EXCEPTION_H
