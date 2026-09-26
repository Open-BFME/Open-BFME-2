// ?getBufferForRead@?$StringBase@G@@QAEPAGH@Z
// partial score=0.93 date=2026-09-26
// ?getBufferForRead@?$StringBase@G@@QAEPAGH@Z
// partial score=0.93 date=2026-09-26
// cl: /O2 /EHsc
// ?set@?$StringBase@G@@QAEXPBGH@Z @0x000371E0 321B
// ?concat@?$StringBase@G@@QAEXPBGH@Z @0x00037410 134B
// Wide StringBase (ptr,len) setter: alias check then length branch, wrapper
// CharSource on the stack for the copy, fast in-place when unique with spare
// capacity else allocate via the rowed byte allocator with the 0x737472 tag.
// Wide (ptr,len) concat: empty length returns, null buffer forwards to the
// 2-arg set, else wraps (str,len) and grows via ensureUniqueBufferOfSize.
// Evidence: pinned names, set callers at 0x00005679 0x0000568A 0x000066A2
// 0x00037818 0x00037E25 0x00037ED8, concat callers at 0x000056AE 0x000056BF
// 0x000066D2 0x00006A4C, wrapper vtable 0x00BBE798 slots getLength
// 0x00144010 copy-mid 0x00035E70 getChars 0x00035EA0, releaseBuffer 0x00036E70,
// ensure 0x00036F00, allocator 0x000307F0. Model/flags donor TU
// Code/Libraries/Source/WWVegas/WWLib/StringBaseWideCharSourceSet.cpp // cl: /O2
// plus /EHsc for the handler 0x0075CD08 scope unwind of the stack source.
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
    void set(const T *str, int len);
    void concat(const T *str, int len);
    T *getBufferForRead(int len);
};

class WideStrLenSource : public CharSource<wchar_t> {
    const wchar_t *m_str;
    int m_len;
public:
    WideStrLenSource(const wchar_t *s, int l) : m_str(s), m_len(l) {}
    ~WideStrLenSource() {}
    virtual int getLength() const { return m_len; }
    virtual void _gap() const {}
    virtual int getChars(wchar_t *dest) const {
        for (int i = 0; i < m_len; i++)
            dest[i] = m_str[i];
        return m_len;
    }
};

// ?getLength@WideStrLenSource@@UBEHXZ present-unmatched
// ?_gap@WideStrLenSource@@UBEXXZ present-unmatched
// ?getChars@WideStrLenSource@@UBEHPAG@Z present-unmatched
// ??0WideStrLenSource@@QAE@PBGH@Z present-unmatched
// ??1WideStrLenSource@@QAE@XZ present-unmatched
template <>
void StringBase<wchar_t>::set(const wchar_t *str, int len)
{
    if (m_data != 0 && str == &m_data->data[0])
        return;
    if (len != 0) {
        WideStrLenSource src(str, len);
        const CharSource<wchar_t> &ref = src;
        if (m_data != 0 && m_data->capacity > len && m_data->ref_count == 1) {
            int got = ref.getChars(&m_data->data[0]);
            m_data->length = (unsigned short)got;
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
void StringBase<wchar_t>::concat(const wchar_t *str, int len)
{
    if (len == 0)
        return;
    if (m_data != 0) {
        WideStrLenSource src(str, len);
        ensureUniqueBufferOfSize(m_data->length + len, true, 0, &src);
        return;
    }
    set(str, len);
}
// ?getBufferForRead@?$StringBase@G@@QAEPAGH@Z present-unmatched
template <>
wchar_t *StringBase<wchar_t>::getBufferForRead(int len)
{
	if (m_data != 0 && m_data->capacity > len && m_data->ref_count == 1) {
		m_data->data[m_data->length] = 0;
	} else {
		int bytes = len * 2 + 10;
		if (bytes > 0x7FFF)
			throw 1;
		bytes = ((bytes + 3) / 4) * 4;
		Header *fresh = (Header *)_STL::allocator<char>::allocate(bytes, (const void *)0x737472);
		fresh->ref_count = 1;
		fresh->capacity = (unsigned short)((unsigned int)(bytes - 8) / 2u);
		fresh->length = 0;
		fresh->data[0] = 0;
		releaseBuffer();
		m_data = fresh;
	}
	if (m_data != 0) {
		m_data->length = (unsigned short)len;
		m_data->data[len] = 0;
	}
	return m_data->data;
}
