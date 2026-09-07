// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Modified STLport 4.5.3 locale::global reconstruction, retail RVA 0xBC60.
// Install a new global implementation while holding the locale mutex, update
// the C locale for named locales, and return a reference-counted old handle.
// The explicit copy constructor is essential: the return value must acquire
// its own reference before the local handle is destroyed. Its complete
// lifetime also reproduces the retail saved-register allocation naturally.
//
// This uses the primary source's static-member and global-object identities.
// _M_incr/_M_decr retain the existing repository's recovered virtual spellings
// for the original private _Locale_impl header's incr/decr methods.
// The complete 314-byte body ends at 0xBD9A; alignment bytes are excluded.
//
/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
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

	locale();
	static locale __cdecl global(const locale&);
	locale(const locale&);
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
	string _M_name;
};

__forceinline _Locale_impl *_M_add_ref(_Locale_impl *impl)
{
	impl->_M_incr();
	return impl;
}

extern _Locale_impl *_Stl_loc_global_impl;

__forceinline locale::locale()
{
	_M_impl = 0;
	_M_impl = _M_add_ref(_Stl_loc_global_impl);
}

__forceinline locale::locale(const locale& that) {
 _M_impl = 0;
 _Locale_impl* impl = that._M_impl;
 impl->_M_incr();
 _M_impl = impl;
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

// The mutex reference also owns the lock release on exception unwinding.
struct _STLP_auto_lock
{
	_STLP_mutex_base &_M_lock;

	_STLP_auto_lock(_STLP_mutex_base &lock) : _M_lock(lock)
		{ _M_lock._M_acquire_lock(); }
	~_STLP_auto_lock() { _M_lock._M_release_lock(); }

private:
	void operator=(const _STLP_auto_lock &);
	_STLP_auto_lock(const _STLP_auto_lock &);
};

extern _STLP_mutex_base _Stl_loc_global_locale_lock;
extern string _Nameless;

locale __cdecl locale::global(const locale &L)
{
	locale old;

	_M_add_ref(L._M_impl);

	{
		_STLP_auto_lock lock(_Stl_loc_global_locale_lock);
		_Stl_loc_global_impl->_M_decr();
		_Stl_loc_global_impl = L._M_impl;
	}

	if (L.name() != _Nameless)
		setlocale(0, L.name().data());

	return old;
}

}
