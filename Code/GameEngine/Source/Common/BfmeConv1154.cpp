// cl: /Od /Ob1
// Open-BFME5 conversions.

extern "C" void __cdecl bfmeCopy1154(char *d0, char *d1, const char *s0, const char *s1);

class BfmeS1154
{
public:
	void bfmeReplace1154(unsigned int pos, unsigned int n, const char *s, unsigned int len);
	void bfmeThrow1154(void);
	char *m_bfme00;
	char *m_bfme04;
};

void BfmeS1154::bfmeReplace1154(unsigned int pos, unsigned int n, const char *s, unsigned int len)
{
	const unsigned int *n1;
	int n2;
	int n3;
	int n4;
	unsigned int n5;
	int n6;

	if (pos > (unsigned int)(m_bfme04 - m_bfme00))
		bfmeThrow1154();

	n5 = (unsigned int)(m_bfme04 - m_bfme00) - pos;
	n1 = (n5 < n) ? &n5 : &n;
	bfmeCopy1154(m_bfme00 + pos, m_bfme00 + pos + *n1, s, s + len);
}

// STLport 4.5.3 _string.h at BFME1 968ca36c3265 supplies the constructor.
// Retail 000269D0..00026A40 independently proves the two-argument ABI,
// the three pointer members, and the call to _M_allocate_block (00007460).
// FuncInfo 00CFE0E4 unwinds the proxy at this+8 through the shared empty
// proxy destructor at 0069E440. The source structure is _String_base; the
// original constructor name is unproved and its optimized STL copy differs.
namespace _STL
{
template <class T> class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	__forceinline _STLP_alloc_proxy(const Alloc&, Pointer value)
		: _M_data(value) {}
	~_STLP_alloc_proxy();
	Pointer _M_data;
};

template <class T> class char_traits {};
template <class CharT, class Alloc> class Rva000269D0StringBase;
template <class CharT, class Traits, class Alloc>
class basic_string
{
	template <class T, class A> friend class Rva000269D0StringBase;
	void _M_allocate_block(unsigned int count);
};

template <class CharT, class Alloc>
class Rva000269D0StringBase
{
public:
	Rva000269D0StringBase(const Alloc& alloc, unsigned int count);
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT*, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Alloc>
Rva000269D0StringBase<CharT, Alloc>::Rva000269D0StringBase(const Alloc& alloc, unsigned int count)
	: _M_start(0), _M_finish(0), _M_end_of_storage(alloc, (CharT*)0)
{
	reinterpret_cast<basic_string<CharT, char_traits<CharT>, Alloc>*>(this)->_M_allocate_block(count);
}

template Rva000269D0StringBase<char, allocator<char> >::Rva000269D0StringBase(const allocator<char>&, unsigned int);
}
