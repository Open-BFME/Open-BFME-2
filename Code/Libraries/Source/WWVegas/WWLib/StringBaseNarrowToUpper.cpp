// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME2 1.06 StringBase<char>::toUpper, RVA 0x00036B60 233B.
// Copy-on-write duplicate via rowed byte allocator tagged rts 0x737472 then per-char toupper via IAT.
// Evidence: ghidra toUpper, sibling toLower 0x00036A70 233B same shape/flags, releaseBuffer 0x00036410,
// allocator 0x000307F0, narrow toLower donor TU StringBaseNarrowToLower.cpp // cl: /O2.
#include <string.h>

extern "C" __declspec(dllimport) int __cdecl toupper(int c);

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
    void toUpper();
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
void StringBase<char>::toUpper()
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
        Header *fresh = (Header *)_STL::allocator<char>::allocate(aligned, (const void *)'str');
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
        *start = (char)toupper(*start);
        ++start;
    }
}
