// cl: /O2
// BFME2 1.06 StringBase<char>::toLower, RVA 0x00036A70 233B.
// Pinned explicit export ?toLower@?$StringBase@D@@QAEXXZ, alias pin ?toLower@AsciiString@@QAEXXZ.
// Copy-on-write duplicate via rowed byte allocator tagged rts 0x737472 then per-char tolower via IAT.
// Evidence: export table narrow toLower, AsciiString callers at 0x000B6E8D 0x001361A1, releaseBuffer 0x00036410,
// allocator 0x000307F0, wide twin toUpper at 0x00036B60. Model/flags donor TU
// Code/Libraries/Source/WWVegas/WWLib/StringBaseNarrowRemoveLastChar.cpp // cl: /O2.
#include <string.h>

extern "C" __declspec(dllimport) int __cdecl tolower(int c);

namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
    static char *allocate(unsigned int n, const void *hint);
};
}

template <typename T>
class StringBase {
public:
    void toLower();
private:
    void releaseBuffer();
    struct Header {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };
    Header *m_data;
};

template <>
void StringBase<char>::toLower()
{
    if (!m_data) {
        return;
    }
    int len = m_data->length;
    if (m_data->capacity > len && m_data->ref_count == 1) {
        m_data->data[m_data->length] = 0;
    } else {
        int total = len + 9;
        if (total > 0x7fff) {
            throw 1;
        }
        int aligned = (total + 3) / 4 * 4;
        Header *fresh = (Header *)_STL::allocator<char>::allocate(aligned, (const void *)0x737472);
        fresh->ref_count = 1;
        fresh->capacity = (unsigned short)(aligned - 8);
        if (m_data) {
            memcpy(fresh->data, m_data->data, m_data->length);
            fresh->length = m_data->length;
        } else {
            fresh->length = 0;
        }
        fresh->data[fresh->length] = 0;
        releaseBuffer();
        m_data = fresh;
    }
    char *start = &m_data->data[0];
    char *end = start + m_data->length;
    while (start != end) {
        *start = (char)tolower(*start);
        ++start;
    }
}
