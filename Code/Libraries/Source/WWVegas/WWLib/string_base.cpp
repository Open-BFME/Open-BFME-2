// cl: /O1

#include "string_base.h"

#define _DLL
#include <string.h>

template <>
int StringBase<char>::compare(const StringBase<char> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    return compare(data, len);
}

template <>
void StringBase<char>::concat(const StringBase<char> &str)
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    concat(data, len);
}

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
