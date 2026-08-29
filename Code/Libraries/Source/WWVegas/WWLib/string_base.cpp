#include "string_base.h"

#define _DLL
#include <string.h>

template <typename T>
void StringBase<T>::concat(T c)
{
    concat(&c, 1);
}

template <typename T>
void StringBase<T>::set(T c)
{
    set(&c, 1);
}

template class StringBase<char>;
template void StringBase<wchar_t>::set(wchar_t c);
