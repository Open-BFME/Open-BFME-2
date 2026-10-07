// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<AsciiString>::insert calls the out-of-line create_node (pinned at
// 0x001FD682 from the retail REL32), mirroring
// stlport_list_objectptr_insert.cpp. Retail 0x001FD72C (37 bytes) is the
// insert worker; the node is 12 bytes (8 links + 4-byte StringBase-model
// AsciiString) and create delegates per element to the matched StringBase
// _Construct helper at 0x0002C485, which names the element type.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#pragma optimize("sy", on)
template <class T> class StringBase
{
    void *m_data;
    StringBase(const StringBase<T> &);
public:
    int compare(const StringBase<T> &) const;
    void set(const StringBase<T> &);
    friend class AsciiString;
};

// class-gate: allow AsciiString Retail list erase at 0x000BC67A calls the dtor thunk at 0x0048BA39.
class AsciiString
{
public:
    AsciiString() : m_text(0) {}
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
    }
    AsciiString &operator=(const AsciiString &that)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
        return *this;
    }
    ~AsciiString();
    int compare(const AsciiString &that) const throw();
private:
    char *m_text;
};

inline bool operator==(const AsciiString &a, const AsciiString &b) { return a.compare(b) == 0; }
inline bool operator!=(const AsciiString &a, const AsciiString &b) { return a.compare(b) != 0; }
inline bool operator<(const AsciiString &a, const AsciiString &b) { return a.compare(b) < 0; }
#pragma optimize("", on)

template class _STL::list<AsciiString, _STL::allocator<AsciiString> >;

// Retail comparison spelling names the verified worker at RVA 0x69D6.
#pragma comment(linker, "/alternatename:?compare@AsciiString@@QBEHABV1@@Z=?compare@?$StringBase@D@@QBEHABV1@@Z")

class Rva001FD42B
{
public:
	~Rva001FD42B();
};

class Rva001FD85E
{
public:
	void rva001FD85E();
};

void Rva001FD85E::rva001FD85E()
{
	((Rva001FD42B *)this)->~Rva001FD42B();
}

class Rva001FD458
{
public:
	~Rva001FD458();
};

class Rva001FD863
{
public:
	void rva001FD863();
};

void Rva001FD863::rva001FD863()
{
	((Rva001FD458 *)this)->~Rva001FD458();
}
