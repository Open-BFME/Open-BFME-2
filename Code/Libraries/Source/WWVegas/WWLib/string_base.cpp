// cl: /O1

#include "string_base.h"

#define _DLL
#include <string.h>

class Debug
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual Debug &operator<<(const char *value);
    virtual Debug &operator<<(int value);
    virtual Debug &operator<<(unsigned int value);
    virtual Debug &operator<<(unsigned char value);
    virtual Debug &operator<<(short value);
    virtual Debug &operator<<(unsigned short value);
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual Debug &operator<<(float value);
};

// A translation-unit mirror of StringBase's private header block, so the
// streamer below can inline the str() test the way retail does without opening
// the member up in string_base.h.
struct StringBaseHeader
{
    int ref_count;
    unsigned short length;
    unsigned short capacity;
    char data[1];
};

// exports.csv names 0x000028E8 ??$?6D@@YAAAVDebug@@AAV0@ABV?$StringBase@D@@@Z -
// the decoration says a function TEMPLATE specialization, not a plain overload.
// It inlines str() and hands the result to the const char * overload, which
// MSVC 7.1 places at vtable slot 0x38: the overload run is emitted in reverse
// declaration order from the first overload's slot, so the float one declared
// last lands at 0x20 and this one, declared first, last of all at 0x38.
template <typename T>
Debug &operator<<(Debug &debug, const StringBase<T> &str)
{
    const StringBaseHeader *header = *(const StringBaseHeader *const *)&str;

    debug << (header ? &header->data[0] : "");

    return debug;
}

template Debug &operator<<(Debug &debug, const StringBase<char> &str);

// The four (const T *, int) comparison members hand five arguments to a shared
// worker: this string's data and length, the argument's data and length, and a
// one-byte trait object the callers zero with a lea/stosb pair. Neither narrow
// worker reads that object - only the wide pair takes its address - so it stays
// an opaque byte here.
struct CharCompare
{
    char m_unused;
};

int compareRange(const char *a, int alen, const char *b, int blen, CharCompare tag)
{
    // Retail selects the shorter length with cmovge; MSVC 7.1 will only emit
    // cmp/jl here, which is the one instruction keeping 0x00005816 and
    // 0x00005841 unclaimed. The ternary is not cosmetic: written as an if
    // statement cl also picks the other length for esi, so three more bytes
    // move. As written, the only difference from retail is the select -
    // 42 of 43 bytes and 43 of 44. See reverse/attempts/0x00005816.cpp.
    const int len = alen < blen ? alen : blen;
    const int result = memcmp(a, b, len);
    if (result != 0)
        return result;
    return alen - blen;
}

int compareRangeNoCase(const char *a, int alen, const char *b, int blen, CharCompare tag)
{
    // Retail selects the shorter length with cmovge; MSVC 7.1 will only emit
    // cmp/jl here, which is the one instruction keeping 0x00005816 and
    // 0x00005841 unclaimed. The ternary is not cosmetic: written as an if
    // statement cl also picks the other length for esi, so three more bytes
    // move. As written, the only difference from retail is the select -
    // 42 of 43 bytes and 43 of 44. See reverse/attempts/0x00005816.cpp.
    const int len = alen < blen ? alen : blen;
    const int result = _memicmp(a, b, len);
    if (result != 0)
        return result;
    return alen - blen;
}

template <>
int StringBase<char>::compare(const char *str, int len) const
{
    return compareRange(m_data ? &m_data->data[0] : "", m_data ? m_data->length : 0, str, len,
        CharCompare());
}

template <>
int StringBase<char>::compareNoCase(const char *str, int len) const
{
    return compareRangeNoCase(m_data ? &m_data->data[0] : "", m_data ? m_data->length : 0, str, len,
        CharCompare());
}

// The wide pair at 0x0000586D and 0x00005898 is the same worker shape against
// StringBase<wchar_t>, except that both of them do read the trait object: each
// takes its address and calls through it, so the comparison is a member of the
// trait rather than memcmp. Both now match in string_base_compare_range.cpp,
// which is where the /arch:SSE the cmovge needs lives; only the declarations
// are needed here.
int compareRange(const wchar_t *a, int alen, const wchar_t *b, int blen, CharCompare tag);
int compareRangeNoCase(const wchar_t *a, int alen, const wchar_t *b, int blen, CharCompare tag);

template <>
int StringBase<wchar_t>::compare(const wchar_t *str, int len) const
{
    return compareRange(m_data ? &m_data->data[0] : L"", m_data ? m_data->length : 0, str, len,
        CharCompare());
}

template <>
int StringBase<wchar_t>::compareNoCase(const wchar_t *str, int len) const
{
    return compareRangeNoCase(m_data ? &m_data->data[0] : L"", m_data ? m_data->length : 0, str,
        len, CharCompare());
}

// Both take the argument's length with strlen, guarding the null the same way
// the compare overloads do, and hand it to the length-bounded form in the
// speed-built unit.
template <>
bool StringBase<char>::startsWithNoCase(const StringBase<char> &str) const
{
    return startsWithNoCase(str.m_data ? &str.m_data->data[0] : "",
        str.m_data ? str.m_data->length : 0);
}

template <>
bool StringBase<char>::startsWith(const char *str) const
{
    return startsWith(str, str ? (int)strlen(str) : 0);
}

template <>
bool StringBase<char>::endsWith(const char *str) const
{
    return endsWith(str, str ? (int)strlen(str) : 0);
}

template <>
int StringBase<char>::compare(const char *str) const
{
    return compare(str, str ? (int)strlen(str) : 0);
}

template <>
int StringBase<wchar_t>::compare(const wchar_t *str) const
{
    return compare(str, str ? (int)wcslen(str) : 0);
}

template <>
int StringBase<char>::compare(const StringBase<char> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    return compare(data, len);
}

template <>
int StringBase<wchar_t>::compare(const StringBase<wchar_t> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.m_data ? &str.m_data->data[0] : L"";
    return compare(data, len);
}

template <>
int StringBase<char>::compareNoCase(const StringBase<char> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    return compareNoCase(data, len);
}

template <>
int StringBase<wchar_t>::compareNoCase(const StringBase<wchar_t> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.m_data ? &str.m_data->data[0] : L"";
    return compareNoCase(data, len);
}

template <>
void StringBase<char>::concat(const StringBase<char> &str)
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    concat(data, len);
}

template <>
void StringBase<wchar_t>::concat(const StringBase<wchar_t> &str)
{
    const int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.m_data ? &str.m_data->data[0] : L"";
    concat(data, len);
}

template <typename T>
void StringBase<T>::concat(T c)
{
    concat(&c, 1);
}

template <typename T>
void StringBase<T>::concat(const T *str)
{
    concat(str, str ? (int)strlen(str) : 0);
}

template <>
void StringBase<wchar_t>::concat(const wchar_t *str)
{
    concat(str, str ? (int)wcslen(str) : 0);
}

template <typename T>
bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

template <typename T>
bool StringBase<T>::isNotEmpty() const
{
    return !isEmpty();
}

// "None" is the INI sentinel for an unset asset name, and both tests go through
// the case-insensitive comparison rather than a length check.
template <>
bool StringBase<char>::isNone() const
{
    return compareNoCase("None") == 0;
}

template <>
bool StringBase<wchar_t>::isNone() const
{
    return compareNoCase(L"None") == 0;
}

template <>
bool StringBase<char>::isNotNone() const
{
    return compareNoCase("None") != 0;
}

template <>
bool StringBase<wchar_t>::isNotNone() const
{
    return compareNoCase(L"None") != 0;
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

template <typename T>
void StringBase<T>::set(const T *str)
{
    set(str, str ? (int)strlen(str) : 0);
}

template <>
void StringBase<wchar_t>::set(const wchar_t *str)
{
    set(str, str ? (int)wcslen(str) : 0);
}


template <typename T>
const T *StringBase<T>::find(T c) const
{
    const T *p = m_data ? &m_data->data[0] : (const T *)"";
    const T *end = p + (m_data ? m_data->length : 0);

    while (p != end) {
        if (*p == c) {
            return p;
        }
        ++p;
    }

    return 0;
}

template <typename T>
void StringBase<T>::swap(StringBase<T> &other)
{
    Header *tmp = m_data;
    m_data = other.m_data;
    other.m_data = tmp;
}

template class StringBase<char>;
template void StringBase<wchar_t>::set(wchar_t c);
template void StringBase<wchar_t>::concat(wchar_t c);
template const wchar_t *StringBase<wchar_t>::str() const;
template bool StringBase<wchar_t>::isEmpty() const;
