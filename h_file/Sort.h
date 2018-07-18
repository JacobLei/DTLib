#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"

namespace DTLib
{

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort& s);
    Sort& operator= (const Sort& s);

    template < typename T >
    static void Swap(T& a, T& b)
    {
        T temp(a);
        a = b;
        b = temp;
    }

    template < typename T >
    static void Merge(T scr[], T helper[], int begin, int mid, int end, bool min2max)
    {
        int i = begin;
        int j = mid + 1;
        int k = begin;

        while( (i<=mid) && (j<=end) )
        {
            if( min2max ? (scr[i] < scr[j]) : (scr[i] > scr[j]))
            {
                helper[k++] = scr[i++];
            }
            else
            {
                helper[k++] = scr[j++];
            }
        }

        while(i <= mid)
        {
            helper[k++] = scr[i++];
        }

        while(j <= end)
        {
            helper[k++] = scr[j++];
        }

        for(i=begin; i<=end; ++i)
        {
            scr[i] = helper[i];
        }

    }

    template < typename T >
    static void Merge(T scr[], T helper[], int begin, int end, bool min2max=true)
    {
        if( begin < end )
        {
            int mid = (begin + end) / 2;

            Merge(scr, helper, begin, mid, min2max);
            Merge(scr, helper, mid+1, end, min2max);
            Merge(scr, helper, begin, mid, end, min2max);
        }

    }

    template < typename T >
    static int partition(T array[], int begin, int end, bool min2max)
    {
        T pv = array[begin];

        while( begin < end )
        {
            while( (begin < end) && (min2max ? (array[end] > pv) : (array[end] < pv)) )
            {
                --end;
            }

            if( begin != end )
            {
                Swap(array[begin], array[end]);
            }

            while( (begin < end) && (min2max ? (array[begin] <= pv) : (array[begin] >= pv)) )
            {
                ++begin;
            }

            if( begin != end )
            {
                Swap(array[begin], array[end]);
            }
        }

        array[begin] = pv;

        return begin;
    }

    template < typename T >
    static void Quick(T array[], int begin, int end, bool min2max)
    {
        if( begin < end )
        {
            int pivot = partition(array, begin, end, min2max);

            Quick(array, begin, pivot-1, min2max);
            Quick(array, pivot+1, end, min2max);
        }
    }

public:
    template < typename T >
    static void Select(T array[], int len, bool min2max = true)
    {
        for(int i=0; i<len; ++i)
        {
            int min = i;

            for(int j=i; j<len; ++j)
            {
                if( min2max ? (array[min] > array[j]) : (array[min] < array[j]) )
                {
                    min = j;
                }
            }

            if( min != i )
            {
                Swap(array[min], array[i]);
            }
        }
    }

    template < typename T >
    static void Insert(T array[], int len, bool min2max = true) // O(n^2)
    {
        for(int i=1; i<len; ++i)
        {
            int pos = i;
            T value = array[i];

            for(int j=i-1;
                (j>=0) && (min2max ? (array[j] > value) : (array[j] < value));
                --j)
            {
                array[j+1] = array[j];
                pos = j;
            }

            if(pos != i)
            {
                array[pos] = value;
            }
        }
    }

    template < typename T >
    static void Bubble(T array[], int len, bool min2max = true) // O(n^2)
    {
        bool exchange = true;

        for(int i=0; (i<len) && exchange; ++i)
        {
            exchange = false;

            for(int j=len-1; j>i; --j)
            {
                if((min2max) ? (array[j] < array[j-1]) :(array[j] > array[j-1]))
                {
                    Swap(array[j], array[j-1]);
                    exchange = true;
                }
            }
        }
    }

    template < typename T >
    static void Shell(T array[], int len, bool min2max = true)
    {
        int d = len;

        do
        {
            d = d / 3 + 1;

            for(int i=d; i<len; i+=d)
            {
                int pos = i;
                T value = array[i];

                for(int j=i-d;
                    (j >= 0)&&(min2max) ? (array[j] > value) : (array[j] < value);
                    j-=d)
                {
                    array[j+d] = array[j];
                    pos = j;
                }

                if( pos != i)
                {
                    array[pos] = value;
                }
            }

        }while(d > 1);
    }

    template < typename T >
    static void Shell_By_Bubble(T array[], int len, bool min2max = true)
    {
        int d = len;

        do
        {
            d = d / 3 + 1;
            bool exchange = true;

            for(int i=0; (i<len) && exchange; i+=d)
            {
                exchange = false;

                for(int j=len-1; j>i; j-=d)
                {
                    if(min2max ? (array[j] < array[j-d]) : (array[j] > array[j-d]))
                    {
                            Swap(array[j],array[j-d]);
                            exchange = true;
                    }
                }
            }

        }while(d > 1);
    }

    template < typename T >
    static void Merge(T array[], int len, bool min2max = true)
    {
        T* helper = new T[len];

        if( helper != NULL )
        {
            Merge(array, helper, 0, len-1, min2max);
        }

        delete[] helper;
    }

    template < typename T >
    static void Quick(T array[], int len, bool min2max = true)
    {
        Quick(array, 0, len-1, min2max);
    }

    template < typename T >
    static void Select(Array<T>& array, bool min2max = true)
    {
        Select(array.array(), array.length(), min2max);
    }

    template < typename T >
    static void Insert(Array<T>& array, bool min2max = true)
    {
        Insert(array.array(), array.length(), min2max);
    }

    template < typename T >
    static void Bubble(Array<T>& array, bool min2max = true)
    {
        Bubble(array.array(), array.length(), min2max);
    }

    template < typename T >
    static void Shell(Array<T>& array, bool min2max = true)
    {
        Shell(array.array(), array.length(), min2max);
    }

    template < typename T >
    static void Merge(Array<T>& array, bool min2max = true)
    {
        Merge(array.array(), array.length(), min2max);
    }

    template < typename T >
    static void Quick(Array<T>& array, bool min2max = true)
    {
        Quick(array.array(), array.length(), min2max);
    }

};


}


#endif // SORT_H
