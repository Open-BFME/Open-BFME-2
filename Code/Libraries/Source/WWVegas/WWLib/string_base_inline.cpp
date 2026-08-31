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

#define _DLL
#include <string.h>

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
template <typename T>
bool StringBase<T>::isNotEmpty() const
{
    return !isEmpty();
}

// An empty prefix always matches, and a string shorter than the prefix never
// does; /Oi turns the remaining memcmp into a rep cmpsb rather than a call.
template <typename T>
bool StringBase<T>::startsWith(const T *str, int len) const
{
    if (*str == 0) {
        return true;
    }

    if ((m_data ? m_data->length : 0) < len) {
        return false;
    }

    return memcmp(&m_data->data[0], str, len) == 0;
}

template <typename T>
bool StringBase<T>::endsWith(const T *str, int len) const
{
    if (*str == 0) {
        return true;
    }

    if ((m_data ? m_data->length : 0) < len) {
        return false;
    }

    return memcmp(&m_data->data[0] + ((m_data ? m_data->length : 0) - len), str, len) == 0;
}

template <typename T>
bool StringBase<T>::startsWith(const StringBase<T> &str) const
{
    return startsWith(str.m_data ? &str.m_data->data[0] : "", str.m_data ? str.m_data->length : 0);
}

template <typename T>
bool StringBase<T>::endsWith(const StringBase<T> &str) const
{
    return endsWith(str.m_data ? &str.m_data->data[0] : "", str.m_data ? str.m_data->length : 0);
}

// 0x0002C459 stays unclaimed: retail keeps the character parameter as a memory
// operand and loads the string byte into the register, while MSVC 7.1 hoists the
// parameter into the register before the loop and compares against memory. Four
// loop shapes all produce the hoisted form.
template <typename T>
const T *StringBase<T>::find(T c) const
{
    const T *p = m_data ? &m_data->data[0] : "";
    const T *end = p + (m_data ? m_data->length : 0);

    do {
        if (*p == c) {
            return p;
        }
        ++p;
    } while (p != end);

    return 0;
}

template bool StringBase<wchar_t>::isNotEmpty() const;
template bool StringBase<char>::startsWith(const StringBase<char> &str) const;
template bool StringBase<char>::startsWith(const char *str, int len) const;
template bool StringBase<char>::endsWith(const StringBase<char> &str) const;
template bool StringBase<char>::endsWith(const char *str, int len) const;
template const char *StringBase<char>::find(char c) const;
template char StringBase<char>::getCharAt(int index) const;
template wchar_t StringBase<wchar_t>::getCharAt(int index) const;
template bool StringBase<wchar_t>::isEmpty() const;
template StringBase<char>::StringBase(char character);
template StringBase<char>::StringBase(const char *str, int len);
template StringBase<char>::StringBase(const CharSource<char> &source);
template StringBase<wchar_t>::StringBase(wchar_t character);
template StringBase<wchar_t>::StringBase(const wchar_t *str, int len);
template StringBase<wchar_t>::StringBase(const CharSource<wchar_t> &source);
