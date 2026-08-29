#include "string_base.h"

#define _DLL
#include <string.h>

template <typename T>
void StringBase<T>::concat(T c)
{
    concat(&c, 1);
}

template <typename T>
int StringBase<T>::getLength() const
{
    return m_data ? m_data->length : 0;
}

template <typename T>
const T *StringBase<T>::str() const
{
    return m_data ? &m_data->data[0] : (const T *)"";
}

template <typename T>
void StringBase<T>::set(T c)
{
    set(&c, 1);
}

template class StringBase<char>;
template void StringBase<wchar_t>::set(wchar_t c);
template void StringBase<wchar_t>::concat(wchar_t c);
template const wchar_t *StringBase<wchar_t>::str() const;
