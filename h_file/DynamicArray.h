#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class DynamicArray : public Array<T>
{
protected:
    int m_length;
public:
    DynamicArray(int length)
    {
        this->m_array = new T[length];

        if ( this->m_array != NULL )
        {
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create DynamicArray Object...");
        }
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        this->m_array = new T[obj.m_length];

        if ( this->m_array != NULL )
        {
            for(int i=0; i<obj.m_length; ++i)
            {
                this->m_array[i] = obj.m_array[i];
            }

            this->m_length = obj.m_length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to create DynamicArray Object...");
        }
    }

    DynamicArray<T>& operator= (const DynamicArray<T>& obj)
    {
        if( this != &obj )
        {
            T* array = new T[obj.m_length];

            if ( array != NULL )
            {
                for(int i=0; i<obj.m_length; ++i)
                {
                    array[i] = obj.m_array[i];
                }

                T* temp = this->m_array;

                this->m_array = array;
                this->m_length = obj.m_length;

                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to copy object...");
            }
        }

        return *this;
    }

    int length() const
    {
        return this->m_length;
    }

    void resize(int length)
    {
        if( this->m_length != length )
        {
            T* array = new T[length];

            if( array != NULL )
            {
                int len = ( (this->m_length < length) ? m_length : length );

                for(int i=0; i<len; ++i)
                {
                    array[i] = this->m_array[i];
                }

                T* temp = this->m_array;

                this->m_array = array;
                this->m_length = length;

                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryExcetion, "No memory to resize object...");
            }


        }
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};

}

#endif // DYNAMICARRAY_H
