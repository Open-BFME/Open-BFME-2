// cl: /O2
// BFME2 1.06 StringBase<char>::removeLastChar, RVA 0x00036C50 228B.
// Pinned explicit export ?removeLastChar@?$StringBase@D@@QAEXXZ.
// Copy-on-write tail trim: fast in-place when unique with spare capacity
// else duplicate via the rowed byte allocator tagged rts 0x737472 then
// decrement length or clear. ZH AsciiString::removeLastChar role.
// Caller trim at 0x00037D76 in StringBaseNarrowTrim.cpp.
#include <string.h>

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
void StringBase<char>::removeLastChar()
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
    int cur = m_data->length;
    int dec = cur - 1;
    if (dec > 0) {
        m_data->data[dec] = 0;
        m_data->length = (unsigned short)dec;
    } else {
        releaseBuffer();
    }
}
