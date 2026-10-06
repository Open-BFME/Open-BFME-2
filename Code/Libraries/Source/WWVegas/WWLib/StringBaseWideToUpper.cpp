// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME2 1.06 StringBase<wchar_t>::toUpper, RVA 0x000375E0 251B.
// Wide twin of ?toLower@?$StringBase@G@@QAEXXZ at 0x000374E0, per-char towupper via IAT.
// Copy-on-write duplicate via rowed byte allocator tagged rts 0x737472 then
// per-char towupper via IAT. Model/flags donor TU
// Code/Libraries/Source/WWVegas/WWLib/StringBaseWideToLower.cpp // cl: /O2
// Evidence: ghidra toUpper size 251,
// allocator 0x000307F0, releaseBuffer 0x00036E70, towupper IAT 0x00BBA5B0,
// prev toLower 0x000374E0 and next removeLastChar 0x000376E0 share // cl: /O2.
#include <string.h>

typedef unsigned short wchar_t;

extern "C" __declspec(dllimport) unsigned short __cdecl towupper(unsigned short c);

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
void StringBase<wchar_t>::toUpper()
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
    wchar_t *start = &m_data->data[0];
    wchar_t *end = start + m_data->length;
    while (start != end) {
        wchar_t c = *start;
        *start = towupper(c);
        ++start;
    }
}
