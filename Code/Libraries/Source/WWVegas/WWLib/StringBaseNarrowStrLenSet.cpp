// cl: /O2 /EHsc
// ?set@?$StringBase@D@@QAEXPBDH@Z @0x00036780 320B
// Narrow StringBase (ptr,len) setter: alias check then length branch, wrapper
// CharSource on the stack for the copy, fast in-place when unique with spare
// capacity else allocate via the rowed byte allocator with the 0x737472 tag.
// Evidence: pinned name, callers at 0x00005610 0x00005621 0x000065DC
// 0x00036A10 0x00036D78, wrapper vtable 0x00BBE78C slots, releaseBuffer 0x00036410,
// allocator 0x000307F0. Model/flags donor TU
// Code/Libraries/Source/WWVegas/WWLib/StringBaseWideStrLenSet.cpp // cl: /O2 /EHsc
// plus char-size bytes len+9 and capacity bytes-8 (no divide).
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
    void set(const T *str, int len);
    void set(const CharSource<T> &source);
    void concat(const T *str, int len);
};

class NarrowStrLenSource : public CharSource<char> {
    const char *m_str;
    int m_len;
public:
    NarrowStrLenSource(const char *s, int l) : m_str(s), m_len(l) {}
    ~NarrowStrLenSource() {}
    virtual int getLength() const { return m_len; }
    virtual void _gap() const {}
    virtual int getChars(char *dest) const {
        for (int i = 0; i < m_len; i++)
            dest[i] = m_str[i];
        return m_len;
    }
};

// ?getLength@NarrowStrLenSource@@UBEHXZ present-unmatched
// ?_gap@NarrowStrLenSource@@UBEXXZ present-unmatched
// ?getChars@NarrowStrLenSource@@UBEHPAD@Z present-unmatched
// ??0NarrowStrLenSource@@QAE@PBDH@Z present-unmatched
// ??1NarrowStrLenSource@@QAE@XZ present-unmatched
template <>
void StringBase<char>::set(const char *str, int len)
{
    if (m_data != 0 && str == &m_data->data[0])
        return;
    if (len != 0) {
        NarrowStrLenSource src(str, len);
        const CharSource<char> &ref = src;
        if (m_data != 0 && m_data->capacity > len && m_data->ref_count == 1) {
            int got = ref.getChars(&m_data->data[0]);
            m_data->length = (unsigned short)got;
            m_data->data[m_data->length] = 0;
            return;
        }
        int bytes = len + 9;
        if (bytes > 0x7fff)
            throw 1;
        bytes = ((bytes + 3) / 4) * 4;
        Header *fresh = (Header *)_STL::allocator<char>::allocate(bytes, (const void *)0x737472);
        fresh->ref_count = 1;
        fresh->capacity = (unsigned short)(bytes - 8);
        fresh->length = 0;
        int got = ref.getChars(&fresh->data[0]);
        fresh->length = (unsigned short)got;
        fresh->data[fresh->length] = 0;
        releaseBuffer();
        m_data = fresh;
        return;
    }
    releaseBuffer();
}

template <>
void StringBase<char>::concat(const char *str, int len)
{
    if (len == 0)
        return;
    if (m_data != 0) {
        NarrowStrLenSource src(str, len);
        ensureUniqueBufferOfSize(m_data->length + len, true, 0, &src);
        return;
    }
    set(str, len);
}

template <>
void StringBase<char>::set(const CharSource<char> &source)
{
    int len = source.getLength();
    if (len != 0) {
        if (m_data && m_data->capacity > len && m_data->ref_count == 1) {
            char *dest = &m_data->data[0];
            int got = source.getChars(dest);
            m_data->length = (unsigned short)got;
            m_data->data[m_data->length] = 0;
            return;
        }
        int bytes = len + 9;
        if (bytes > 0x7fff)
            throw 1;
        bytes = ((bytes + 3) / 4) * 4;
        Header *fresh = (Header *)_STL::allocator<char>::allocate(bytes, (const void *)0x737472);
        fresh->ref_count = 1;
        fresh->capacity = (unsigned short)(bytes - 8);
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
