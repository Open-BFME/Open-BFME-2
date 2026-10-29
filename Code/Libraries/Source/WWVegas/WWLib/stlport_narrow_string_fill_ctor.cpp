// cl: /DNDEBUG /MD /EHsc /Od /Ob2
// stlport46
//
// STLport 4.5.3 basic_string<char>::basic_string(size_type, char, const
// allocator &) - the fill constructor. 177-byte body at 0x000271E0
// calls the two callees this TU reaches: _M_allocate_block at 0x00007460 and
// the fill body at 0x000237C0. The two-argument _String_base constructor and
// the fill_n chain below are what reach those addresses; the char overload
// of fill_n ends at the existing fill body.
//
// Donor: the BFME1 reconstruction of the same upstream constructor.
// Bind allocation directly to the BFME2 basic_string-scope owner at 0x7460;
// the native unwind call uses the shared one-byte allocator-proxy destructor.

namespace _STL
{

template <class T>
class allocator
{
public:
	allocator(void) __declspec(nothrow) {}
	allocator(const allocator &) __declspec(nothrow) {}
	~allocator(void) __declspec(nothrow) {}
};

template <class T>
class char_traits
{
};

struct true_type
{
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	_STLP_alloc_proxy(const Alloc &a, Pointer p) : Alloc(a), _M_data(p) {}

	// Native constructor unwind calls the shared one-byte destructor.
	~_STLP_alloc_proxy();

	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc> class basic_string;

template <class T, class Alloc>
class _String_base
{
public:
	typedef allocator<T> allocator_type;

	_String_base(const allocator_type &a)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (T *)0) {}

	_String_base(const allocator_type &a, unsigned n)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (T *)0)
	{
		// The retail call lands on the existing basic_string-scope row.
		((basic_string<T, char_traits<T>, Alloc> *)this)->_M_allocate_block(n);
	}

	~_String_base(void)
	{
		_M_deallocate_block();
	}

	void _M_allocate_block(unsigned n);
	void _M_deallocate_block(void);

	T *_M_start;
	T *_M_finish;
	_STLP_alloc_proxy<T *, T, allocator_type> _M_end_of_storage;
};

void __declspec(nothrow) fill(char *first, char *last, const char &value);

template <class Size>
__declspec(nothrow) inline char *fill_n(char *first, Size n, const char &value)
{
	fill(first, first + n, value);
	return first + n;
}

template <class Size>

__declspec(nothrow) inline char *uninitialized_fill_n(char *first, Size n, const char &value,
	const true_type &)
{
	return fill_n(first, n, value);
}

template <class Size>
__declspec(nothrow) inline char *uninitialized_fill_n(char *first, Size n, const char &value)
{
	return uninitialized_fill_n(first, n, value, true_type());
}

template <class CharT, class Traits, class Alloc>
class basic_string : protected _String_base<CharT, Alloc>
{
	template <class T, class A> friend class _String_base;
	void _M_allocate_block(unsigned n);

public:
	typedef allocator<CharT> allocator_type;
	typedef unsigned size_type;

	basic_string(size_type n, CharT c, const allocator_type &a);

private:
	void __declspec(nothrow) _M_terminate_string_aux(const true_type &)
	{
		*(this->_M_finish) = 0;
	}

	void __declspec(nothrow) _M_terminate_string()
	{
		_M_terminate_string_aux(true_type());
	}
};

// ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@IDABV?$allocator@D@1@@Z
template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(
	size_type n, CharT c, const allocator_type &a)
	: _String_base<CharT, Alloc>(a, n + 1)
{
	this->_M_finish = uninitialized_fill_n(this->_M_start, n, c);
	_M_terminate_string();
}

template basic_string<char, char_traits<char>, allocator<char> >::basic_string(
	unsigned, char, const allocator<char> &);

}
