// cl: /O2

// The StringBase members that retail emits as COMDATs from a translation unit
// built for speed rather than size. They sit together at 0x00035720, 0x00035740
// and 0x00035760, and every one of them differs from string_base.cpp's own
// bodies in exactly the ways /O2 differs from /O1: `mov eax, 1` instead of
// xor/inc for a true, a duplicated ret in each arm instead of a jump to a shared
// epilogue, and a full-width movsx/movzx of the character instead of an 8-bit
// move. Under /O1 all three miss by those two or three bytes; under /O2 all
// three land, while eighteen of string_base.cpp's own bodies stop matching.
//
// The narrow isEmpty is the control: it is a separate body at 0x00001E2F with
// the /O1 shape, already claimed out of AsciiString.cpp.

typedef unsigned short wchar_t;

#include "string_base.h"

// The three private constructors. Each one null-clears the buffer pointer and
// then hands the work to the matching set overload; the character one takes the
// address of its own by-value parameter and passes a length of 1.
template <typename T>
StringBase<T>::StringBase(T character)
{
    m_data = 0;
    set(&character, 1);
}

template <typename T>
StringBase<T>::StringBase(const T *str, int len)
{
    m_data = 0;
    set(str, len);
}

template <typename T>
StringBase<T>::StringBase(const CharSource<T> &source)
{
    m_data = 0;
    set(source);
}

template <typename T>
T StringBase<T>::getCharAt(int index) const
{
    return m_data ? m_data->data[index] : 0;
}

template <typename T>
bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

template <typename T>
StringBase<T> &StringBase<T>::operator=(const StringBase<T> &str)
{
    set(str);

    return *this;
}

template StringBase<char> &StringBase<char>::operator=(const StringBase<char> &str);
template StringBase<wchar_t> &StringBase<wchar_t>::operator=(const StringBase<wchar_t> &str);
template char StringBase<char>::getCharAt(int index) const;
template wchar_t StringBase<wchar_t>::getCharAt(int index) const;
template bool StringBase<wchar_t>::isEmpty() const;
template StringBase<char>::StringBase(char character);
template StringBase<char>::StringBase(const char *str, int len);
template StringBase<char>::StringBase(const CharSource<char> &source);
template StringBase<wchar_t>::StringBase(wchar_t character);
template StringBase<wchar_t>::StringBase(const wchar_t *str, int len);
template StringBase<wchar_t>::StringBase(const CharSource<wchar_t> &source);
