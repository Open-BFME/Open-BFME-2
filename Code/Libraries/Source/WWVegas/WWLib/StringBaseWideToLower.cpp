// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME2 1.06 StringBase<wchar_t>::toLower, RVA 0x000374E0 251B.
// Wide twin of pinned narrow ?toLower@?$StringBase@D@@QAEXXZ at 0x00036A70.
// Copy-on-write duplicate via rowed byte allocator tagged rts 0x737472 then
// per-char towlower via IAT. Model/flags donor TUs
// Code/Libraries/Source/WWVegas/WWLib/StringBaseNarrowToLower.cpp // cl: /O2
// plus Code/Libraries/Source/WWVegas/WWLib/StringBaseWideRemoveLastChar.cpp // cl: /O2
// for the unsigned capacity divide. Evidence: ghidra toLower size 251,
// allocator 0x000307F0, releaseBuffer 0x00036E70, towlower IAT 0x00BBA68C,
// prev concat 0x000374A0 and next removeLastChar 0x000376E0 share // cl: /O2.
#include <string.h>

typedef unsigned short wchar_t;

extern "C" __declspec(dllimport) unsigned short __cdecl towlower(unsigned short c);

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
void StringBase<wchar_t>::toLower()
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
        *start = towlower(c);
        ++start;
    }
}
