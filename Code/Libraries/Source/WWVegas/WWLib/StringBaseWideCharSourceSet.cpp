// cl: /O2
// ?set@?$StringBase@G@@QAEXABV?$CharSource@G@@@Z @0x00037330 220B
// Wide StringBase CharSource setter: reuse when capacity allows else allocate
// via the rowed byte allocator with the 0x737472 tag. Evidence: pinned name,
// callers at 0x000374D2 concat and 0x00037E7E CharSource ctor, vtable slot 0
// length plus slot 8 copy, releaseBuffer 0x00036E70, allocator 0x000307F0.
typedef unsigned short wchar_t;

namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
    static char *allocate(unsigned int n, const void *hint);
};
}

template <typename T>
class CharSource {
public:
    virtual int getLength() const = 0;
    virtual void _gap() const = 0;
    virtual int getChars(T *dest) const = 0;
};

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
    void ensureUniqueBufferOfSize(int newLen, bool keepData, const CharSource<T> *src1, const CharSource<T> *src2);
public:
    void set(const CharSource<T> &source);
    void concat(const CharSource<T> &source);
};

template <>
void StringBase<wchar_t>::set(const CharSource<wchar_t> &source)
{
    int len = source.getLength();
    if (len != 0) {
        if (m_data && m_data->capacity > len && m_data->ref_count == 1) {
            wchar_t *dest = &m_data->data[0];
            m_data->length = (unsigned short)source.getChars(dest);
            m_data->data[m_data->length] = 0;
            return;
        }
        int bytes = len * 2 + 10;
        if (bytes > 0x7fff)
            throw 1;
        bytes = ((bytes + 3) / 4) * 4;
        Header *fresh = (Header *)_STL::allocator<char>::allocate(bytes, (const void *)0x737472);
        fresh->ref_count = 1;
        fresh->capacity = (unsigned short)((unsigned int)(bytes - 8) / 2u);
        fresh->length = 0;
        int got = source.getChars(&fresh->data[0]);
        fresh->length = (unsigned short)got;
        fresh->data[fresh->length] = 0;
        releaseBuffer();
        m_data = fresh;
        return;
    }
    releaseBuffer();
}

template <>
void StringBase<wchar_t>::concat(const CharSource<wchar_t> &source)
{
    int len = source.getLength();
    if (len == 0)
        return;
    if (m_data != 0) {
        ensureUniqueBufferOfSize(m_data->length + len, true, 0, &source);
        return;
    }
    set(source);
}
