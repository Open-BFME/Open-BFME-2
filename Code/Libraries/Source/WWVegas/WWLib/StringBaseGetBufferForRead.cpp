// cl: /EHsc
// ?getBufferForRead@?$StringBase@D@@QAEPADH@Z @0x00036640 173B
// ?getBufferForRead@?$StringBase@G@@QAEPAGH@Z @0x000370A0 174B
// Narrow/wide StringBase getBufferForRead: keep a unique buffer with spare
// capacity, otherwise allocate a fresh empty one (rowed byte allocator, 0x737472
// tag, throw 1 over 0x7fff bytes) and release the old; then set the length.
// Evidence: BFME2 exports and symbols.csv pins for both names; BFME1 donor
// reference/open-bfme-1/game/Libraries/Source/string/StringBase.cpp
// (StringBase<T>::getBufferForRead) with BFME2's allocator call and size
// arithmetic from the rowed set(const T *, int) twins; rowed releaseBuffer
// 0x00036410/0x00036E70, allocator 0x000307F0.
// Model/flags donor TUs Code/Libraries/Source/WWVegas/WWLib/StringBaseNarrowStrLenSet.cpp
// and StringBaseWideStrLenSet.cpp (// cl: /O2 /EHsc).
typedef unsigned short wchar_t;

namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
    static char *allocate(unsigned int n, const void *hint);
};
}

// The allocation hint is the string heap's four-character id ('str'), the
// same id Rva002253C2Init registers the heap under; it is not an address.
enum { STRING_HEAP_TAG = ('s' << 16) | ('t' << 8) | 'r' };

template <typename T>
class StringBase {
private:
    struct Header {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };
    Header *m_data;
    void releaseBuffer();
public:
    T *getBufferForRead(int len);
};

template <>
char *StringBase<char>::getBufferForRead(int len)
{
    if (m_data == 0 || m_data->capacity <= len || m_data->ref_count != 1) {
        int bytes = len + 9;
        if (bytes > 0x7fff)
            throw 1;
        bytes = ((bytes + 3) / 4) * 4;
        Header *fresh = (Header *)_STL::allocator<char>::allocate(bytes, (const void *)STRING_HEAP_TAG);
        ((volatile int *)&fresh->ref_count)[0] = 1;
        ((volatile unsigned short *)&fresh->capacity)[0] = (unsigned short)(bytes - 8);
        ((volatile unsigned short *)&fresh->length)[0] = 0;
        ((volatile char *)&fresh->data[0])[0] = 0;
        releaseBuffer();
        m_data = fresh;
    } else {
        m_data->data[m_data->length] = 0;
    }
    if (m_data) {
        m_data->length = (unsigned short)len;
        m_data->data[len] = 0;
    }
    return &m_data->data[0];
}

template <>
wchar_t *StringBase<wchar_t>::getBufferForRead(int len)
{
    if (m_data == 0 || m_data->capacity <= len || m_data->ref_count != 1) {
        int bytes = len * 2 + 10;
        if (bytes > 0x7fff)
            throw 1;
        bytes = ((bytes + 3) / 4) * 4;
        Header *fresh = (Header *)_STL::allocator<char>::allocate(bytes, (const void *)STRING_HEAP_TAG);
        ((volatile int *)&fresh->ref_count)[0] = 1;
        ((volatile unsigned short *)&fresh->capacity)[0] = (unsigned short)((unsigned int)(bytes - 8) / 2u);
        ((volatile unsigned short *)&fresh->length)[0] = 0;
        ((volatile wchar_t *)&fresh->data[0])[0] = 0;
        releaseBuffer();
        m_data = fresh;
    } else {
        m_data->data[m_data->length] = 0;
    }
    if (m_data) {
        m_data->length = (unsigned short)len;
        m_data->data[len] = 0;
    }
    return &m_data->data[0];
}
