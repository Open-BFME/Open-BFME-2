// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// list<AsciiString>::_M_create_node, retail 0x001FD682 (34 bytes, frameless).
// Hand-written explicit specialization, mirroring the dedicated
// AsciiStringUninitializedCopy.cpp precedent: the node comes from the rowed
// raw byte allocator at 0x000307F0 (12 bytes, null hint) and the element is
// built by the opaque StringBase _Construct helper pinned at 0x0002C485,
// whose true _STL mangling is spent at 0x00142CC0. A whole-class
// instantiation instead routes _Construct through the inline copy ctor and
// wraps the body in a try region (93 bytes), so it cannot reproduce this
// out-of-line-helper flavor.
#include <list>

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	__forceinline ~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	BfmeStringData<T> *m_data;

public:
	const T *str() const { return m_data ? &m_data->text[0] : (const T *)""; }
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString();
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);
	~AsciiString();
};

bool operator==(const AsciiString &a, const AsciiString &b);
bool operator<(const AsciiString &a, const AsciiString &b);

// Opaque helper pinned at 0x0002C485 (StringBase _Construct flavor, whose
// true _STL mangling is spent at 0x00142CC0). Declared with copy-construct
// shape so this body emits the retail 2-push call to 0x2C485.
void __cdecl AsciiStringCopyConstructAtRva0002C485(AsciiString *dest, const AsciiString &src);

template <>
_STL::_List_node<AsciiString> *_STL::list<AsciiString, _STL::allocator<AsciiString> >::_M_create_node(const AsciiString &__x)
{
	_STL::_List_node<AsciiString> *__p =
		(_STL::_List_node<AsciiString> *)_STL::allocator<char>::allocate(12, 0);
	AsciiStringCopyConstructAtRva0002C485(&__p->_M_data, __x);
	return __p;
}

// Explicit instantiation so the class's inline callers (insert) odr-use the
// specialization above and cl emits its body; explicit-instantiation-only
// members are invisible to find_declared_unmatched.
template class _STL::list<AsciiString, _STL::allocator<AsciiString> >;
