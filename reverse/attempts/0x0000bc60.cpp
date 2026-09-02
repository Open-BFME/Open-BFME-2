// ?_Stl_global@_STL@@YA?AVlocale@1@ABV21@@Z
// partial score=0.9 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 locale::global. It takes a reference on the impl that is about
// to be replaced, installs the new one under the spin lock at 0x00007690, and
// hands the old one back by value; a named locale also reaches setlocale.
//
// Shapes already settled here:
//
//   * the old impl is a real `locale` LOCAL, not a raw pointer. As a pointer
//     there is nothing for the unwind funclet to destroy and the body loses
//     both the spill and a frame slot - fifteen bytes.
//   * the lock is 0x00DDEB1C and it is released by storing zero, inline; only
//     the acquire is the call at 0x00007690.
//   * the name comparison is INLINED here (size test then repe cmpsb), unlike
//     locale::operator== at 0x0000BB10 which calls the string operator!= at
//     0x000077B0.
//
// STILL OPEN: 283 bytes against 314, and the whole gap is one register swap -
// retail keeps the old impl in ebp and the argument in ebx, MSVC 7.1 does the
// reverse, so every read through the argument pays ebp's displacement byte.
// Naming the new impl as its own local does not move it.

extern "C" void __cdecl free(void *block);
extern "C" __declspec(dllimport) char *__cdecl setlocale(int category, const char *locale);

typedef long __stl_atomic_t;

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;

	~basic_string()
	{
		if (_M_start != 0)
			free(_M_start);
	}

	const CharT *data() const { return _M_start; }
	size_type size() const { return (size_type)(_M_finish - _M_start); }

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);
#pragma intrinsic(memcmp)

inline bool operator==(const string &x, const string &y)
{
	return x.size() == y.size() && memcmp(x.data(), y.data(), x.size()) == 0;
}

inline bool operator!=(const string &x, const string &y)
{
	return !(x == y);
}

class _Locale_impl;

class locale
{
public:
	class facet {};

	locale(_Locale_impl *impl);
	~locale();

	string name() const;

	_Locale_impl *_M_impl;
};

class _Locale_impl
{
public:
	virtual ~_Locale_impl();
	virtual void _M_incr();
	virtual void _M_decr();

	locale::facet **_M_facets;
	unsigned int _M_count;
};

__declspec(dllimport) __forceinline _Locale_impl *_M_add_ref(_Locale_impl *impl)
{
	impl->_M_incr();
	return impl;
}

__forceinline locale::locale(_Locale_impl *impl)
{
	_M_impl = _M_add_ref(impl);
}

__forceinline locale::~locale()
{
	_M_impl->_M_decr();
}

template <int __inst>
struct _STLP_mutex_spin
{
	static void __cdecl _M_do_lock(volatile __stl_atomic_t *lock);
};

class _STLP_mutex_base
{
public:
	__forceinline void _M_acquire_lock()
	{
		_STLP_mutex_spin<0>::_M_do_lock(&_M_lock);
	}

	__forceinline void _M_release_lock() { _M_lock = 0; }

	volatile __stl_atomic_t _M_lock;
};

_Locale_impl *_Stl_classic_locale_impl;
_STLP_mutex_base _Stl_locale_lock;
extern const string _Nameless;

locale __cdecl _Stl_global(const locale &L)
{
	locale old(_Stl_classic_locale_impl);

	_M_add_ref(L._M_impl);

	_Stl_locale_lock._M_acquire_lock();
	_Stl_classic_locale_impl->_M_decr();
	_Stl_classic_locale_impl = L._M_impl;
	_Stl_locale_lock._M_release_lock();

	if (L.name() != _Nameless)
		setlocale(0, L.name().data());

	return old;
}

}
