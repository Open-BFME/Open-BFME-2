// cl: /Od /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport46

// STLport 4.5.3 narrow-string reserve-tag constructor, 0x00027150 / 129B.
// The first argument is an empty tag; native callers 0x001F94D2/0x001F9569
// pass capacity separately. Adapt the vendor _String_base allocator call to
// the existing basic_string-scope owner at 0x00007460 and declare the shared
// one-byte allocator-proxy destructor used by the native unwind graph.
// The constructor, layout and empty termination follow STLport _string.h.

// Preserve the vendor header's original linker directives.
#pragma comment(lib, "stlport_vc7_static.lib")
#pragma comment(lib, "msvcprt")

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
class char_traits {};

struct true_type {};
struct _String_reserve_t {};

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
	void _M_allocate_block(unsigned n);

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

	void _M_deallocate_block(void);

	T *_M_start;
	T *_M_finish;
	_STLP_alloc_proxy<T *, T, allocator_type> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : protected _String_base<CharT, Alloc>
{
	template <class T, class A> friend class _String_base;
	void _M_allocate_block(unsigned n);

public:
	typedef allocator<CharT> allocator_type;

	basic_string(_String_reserve_t, unsigned n, const allocator_type &a);

	void __declspec(nothrow) _M_terminate_string_aux(const true_type &)
	{
		*(this->_M_finish) = 0;
	}

	void __declspec(nothrow) _M_terminate_string(void)
	{
		_M_terminate_string_aux(true_type());
	}
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(_String_reserve_t, unsigned n, const allocator_type &a)
	: _String_base<CharT, Alloc>(a, n + 1)
{
	_M_terminate_string();
}

}

namespace _STL {
template basic_string<char, char_traits<char>, allocator<char> >::basic_string(
    _String_reserve_t, unsigned, const allocator<char> &);
}
