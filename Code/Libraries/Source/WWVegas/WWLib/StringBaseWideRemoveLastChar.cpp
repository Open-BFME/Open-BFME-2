// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME2 1.06 StringBase<wchar_t>::removeLastChar, RVA 0x000376E0 241B.
// Pinned ?removeLastChar@?$StringBase@G@@QAEXXZ (wide twin of pinned narrow
// ?removeLastChar@?$StringBase@D@@QAEXXZ at 0x00036C50).
// Copy-on-write tail trim: fast in-place when unique with spare capacity
// else duplicate via the rowed byte allocator tagged rts 0x737472 then
// decrement length or clear. Model/flags donor TU
// Code/Libraries/Source/WWVegas/WWLib/StringBaseNarrowRemoveLastChar.cpp // cl: /O2.
// Evidence: pinned wide name, callers trim at 0x00037FE2 in StringBaseWideTrim.cpp
// plus MapMetaData base-name and Bfme callers, releaseBuffer 0x00036E70,
// allocator 0x000307F0.
#include <string.h>

typedef unsigned short wchar_t;

namespace _STL {
template <typename T> class allocator;
template <> class allocator<char> {
public:
    static char *allocate(unsigned int n, const void *hint);
};
}

template <typename T>
class StringBase {
public:
    void removeLastChar();
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
void StringBase<wchar_t>::removeLastChar()
{
    if (!m_data) {
        return;
    }
    int len = m_data->length;
    if (m_data->capacity > len && m_data->ref_count == 1) {
        m_data->data[m_data->length] = 0;
    } else {
        int total = len * 2 + 10;
        if (total > 0x7fff) {
            throw 1;
        }
        int aligned = (total + 3) / 4 * 4;
        Header *fresh = (Header *)_STL::allocator<char>::allocate(aligned, (const void *)'str');
        fresh->ref_count = 1;
        fresh->capacity = (unsigned short)((unsigned)(aligned - 8) / 2u);
        if (m_data) {
            memcpy(fresh->data, m_data->data, m_data->length * 2);
            fresh->length = m_data->length;
        } else {
            fresh->length = 0;
        }
        fresh->data[fresh->length] = 0;
        releaseBuffer();
        m_data = fresh;
    }
    int cur = m_data->length;
    int dec = cur - 1;
    if (dec > 0) {
        m_data->data[dec] = 0;
        m_data->length = (unsigned short)dec;
    } else {
        releaseBuffer();
    }
}
