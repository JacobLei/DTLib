#ifndef DTSTRING_H
#define DTSTRING_H

#include <cstring>
#include <cstdlib>
#include "Object.h"
#include "Exception.h"

using namespace std;

namespace DTLib
{

class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* l, const char* r, int len) const;

    static int* make_pmt(const char* p);
    static int kmp(const char* s, const char* p);
public:
    String();
    String(char c);
    String(const char* s);
    String(const String& s);
    int length() const;
    const char* str() const;

    /* 操作符重载相关函数 */
    bool operator == (const String& s) const;
    bool operator == (const char* s) const;
    bool operator != (const String& s) const;
    bool operator != (const char* s) const;
    bool operator > (const String& s) const;
    bool operator > (const char* s) const;
    bool operator < (const String& s) const;
    bool operator < (const char* s) const;
    bool operator >= (const String& s) const;
    bool operator >= (const char* s) const;
    bool operator <= (const String& s) const;
    bool operator <= (const char* s) const;

    String operator + (const String& s) const;
    String operator + (const char* s) const;
    String& operator += (const String& s);
    String& operator += (const char* s);

    String operator - (const String& s) const;
    String operator - (const char* s) const;
    String& operator -= (const String& s);
    String& operator -= (const char* s);

    String& operator = (const String& s);
    String& operator = (const char* s);
    String& operator = (char c);

    /* 数组操作符的重载函数 */
    char& operator[](int i);
    char operator [](int i) const;

    /* 判断是否以指定字符串开始或结束 */
    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;

    /* 在指定位置处插入字符串:i代表在i之前插入字符串s */
    String& insert(int i, const char* s);
    String& insert(int i, const String& s);

    /* 去掉字符串两端的空白字符 */
    String& trim();

    /* 子串查找 */
    int indexOf(const char* s) const;
    int indexOf(const String& s) const;

    /* 删除指定下标指定长度的字符串 */
    String& remove(int i, int len);
    /* 在字符串中将指定的子串删除 */
    String& remove(const char* s);
    String& remove(const String& s);

    /* 字符串中的子串替换 */
    String& replace(const char* t, const char* s);
    String& replace(const String& t, const char* s);
    String& replace(const char *t, const String& s);
    String& replace(const String& t, const String& s);

    String sub(int i, int len) const;

    ~String();
};

int* String::make_pmt(const char* p)
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if( ret )
    {
        ret[0] = 0;
        int ll = 0;

        for(int i=1; i<len; ++i)
        {
            while( (ll > 0) && (p[i] != p[ll]) )
            {
                ll = ret[ll - 1];
            }

            if(p[i] == p[ll])
            {
                ++ll;
            }

            ret[i] = ll;
        }
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create pmt...");
    }

    return ret;
}

int String::kmp(const char* s, const char* p)
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int* pmt = make_pmt(p);

    if( (pmt != NULL) && (pl > 0) && (pl <= sl) )
    {
        for(int i=0, j=0; i<sl; ++i)
        {
            while((j > 0) && (s[i] != p[j]))
            {
                j = pmt[j-1];
            }

            if(s[i] == p[j])
            {
                ++j;
            }

            if(j == pl)
            {
                ret = i + 1 - pl;
                break;
            }
        }
    }

    free(pmt);

    return ret;
}

void String::init(const char *s)
{
    m_str = strdup(s);      // 复制一份字符串给m_str

    if( m_str )
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryExcetion, "no memory to create String object...");
    }
}

String::String()
{
    init("");
}

String::String(char c)
{
    char s[] = {c, '\0'};

    init(s);
}

String::String(const char* s)
{
    init(s ? s : "");
}

String::String(const String& s)
{
    init(s.m_str);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

bool String::operator == (const String& s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}

bool String::operator == (const char* s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator != (const String& s) const
{
    return !(*this == s);
}

bool String::operator != (const char* s) const
{
    return !(*this == s);
}

bool String::operator > (const String& s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}

bool String::operator > (const char* s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator < (const String& s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}

bool String::operator < (const char* s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool String::operator >= (const String& s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}

bool String::operator >= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool String::operator <= (const String& s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}

bool String::operator <= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

String String::operator + (const String& s) const
{
    return (*this + s.m_str);
}

String String::operator + (const char* s) const
{
    String ret;

    int len = m_length + strlen(s ? s : "");
    char* str = reinterpret_cast<char*>(malloc(len + 1));

    if( str )
    {
        strcpy(str, m_str);
        strcat(str, s ? s : "");

        free(ret.m_str);

        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryExcetion, "No Memory to add String value...");
    }

    return ret;
}

String& String::operator += (const String& s)
{
    return (*this = *this + s);
}

String& String::operator += (const char* s)
{
    return (*this = *this + s);
}

String String::operator - (const String& s) const
{
    return String(*this).remove(s);         // 通过拷贝构造函数构造一个新的字符串对象
}

String String::operator - (const char* s) const
{
    return String(*this).remove(s);
}

String& String::operator -= (const String& s)
{
    return remove(s);
}

String& String::operator -= (const char* s)
{
    return remove(s);
}


String& String::operator = (const String& s)
{
    return (*this = s.m_str);
}

String& String::operator = (const char* s)
{
    if( m_str != s )
    {
        char* str = strdup(s ? s : "");

        if( str != NULL )
        {
            free(m_str);

            m_str = str;
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to assign a new String value...");
        }
    }

    return *this;
}

String& String::operator = (char c)
{
    char s[] = {c , '\0'};

    return (*this = s);
}

char& String::operator[](int i)
{
    if( (i >= 0) && (i < m_length) )
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }
}

char String::operator [](int i) const
{
    return (const_cast<String&>(*this))[i];
}

bool String::equal(const char* l, const char* r, int len) const
{
    bool ret = true;

    for(int i=0; (i<len) && ret; ++i)
    {
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}

bool String::startWith(const char* s) const
{
    bool ret = (s != NULL);

    if( ret )
    {
        int len = strlen(s);

        ret = (len < m_length) && (equal(m_str, s, len));
    }

    return ret;
}
bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}

bool String::endOf(const char* s) const
{
    bool ret = (s != NULL);

    if( ret )
    {
        int len = strlen(s);
        char* str = m_str + (m_length - len);       // 移动起始位置

        ret = (len < m_length) && (equal(str, s, len));
    }

    return ret;
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

String& String::insert(int i, const char* s)
{
    if( (i>=0) && (i<=m_length) )   // 判断i的位置是否合法
    {
        if( (s != NULL ) && (s[0] != '\0') )    // 判断s不为空指针且不为空字符串
        {
            int len = strlen(s);

            char* str = reinterpret_cast<char*>(malloc(m_length + len + 1));

            if( str != NULL )
            {
                strncpy(str, m_str, i);
                strncpy(str+i, s, len);
                strncpy(str+i+len, m_str+i, m_length-i);

                str[m_length + len] = '\0';

                free(m_str);
                m_str = str;
                m_length = m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to assign a new String value...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }

    return *this;
}

String& String::insert(int i, const String& s)
{
    return insert(i, s.m_str);
}

String& String::trim()
{
    int b = 0;
    int e = m_length - 1;

    while( m_str[b] == ' ' ) ++b;
    while( m_str[e] == ' ' ) --e;

    if( b == 0 )
    {
        m_str[e + 1] = '\0';

        m_length = e + 1;
    }
    else
    {
        for(int i=0, j=b; j<=e; ++i, ++j)
        {
            m_str[i] = m_str[j];
        }

        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
    }

    return *this;
}

int String::indexOf(const char* s) const
{
    return kmp(m_str, s ? s : "");
}

int String::indexOf(const String& s) const
{
    return kmp(m_str, s.m_str);
}

String& String::remove(int i, int len)
{
    if( (i>=0) && (i<m_length) )
    {
        int n = i;
        int m = i + len;

        while((n < m) && (m < m_length))
        {
            m_str[n++] = m_str[m++];
        }

        m_str[n] = '\0';
        m_length = n;
    }

    return *this;
}

String& String::remove(const char* s)
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}

String& String::remove(const String& s)
{
    return remove(indexOf(s), s.length());
}

String& String::replace(const char* t, const char* s)
{
    int index = indexOf(t);

    if( index >= 0 )
    {
        remove(t);
        insert(index, s);
    }

    return *this;
}

String& String::replace(const String& t, const char* s)
{
    return replace(t.m_str, s);
}

String& String::replace(const char *t, const String& s)
{
    return replace(t, s.m_str);
}

String& String::replace(const String& t, const String& s)
{
    return replace(t.m_str, s.m_str);
}

String String::sub(int i, int len) const
{
    String ret;

    if( (i >= 0) && (i < m_length) )
    {
        if(len < 0) len = 0;
        if(i + len > m_length) len = m_length - i;

        char* substr = reinterpret_cast<char*>(malloc(len));

        if( substr != NULL )
        {
            strncpy(substr, m_str+i, len);

            ret = substr;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create sub string ...");
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }


    return ret;
}

String::~String()
{
    free(m_str);
}

}

#endif // DTSTRING_H
