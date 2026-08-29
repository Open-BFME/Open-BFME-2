#include "string_base.h"

template <typename T>
void StringBase<T>::set(T c)
{
    set(&c, 1);
}

template class StringBase<char>;
