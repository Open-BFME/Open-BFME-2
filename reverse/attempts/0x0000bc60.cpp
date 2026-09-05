// ?_Stl_global@_STL@@YA?AVlocale@1@ABV21@@Z
// partial score=0.76 date=2026-09-05
﻿// ?_Stl_global@_STL@@YA?AVlocale@1@ABV21@@Z
// partial score=0.76 date=2026-09-05
//
// STLport 4.5.3 locale::global. It takes a reference on the impl that is about
// to be replaced, installs the new one under the spin lock at 0x00007690, and
// hands the old one back by value; a named locale also reaches setlocale.
//
// Shapes already settled by the 2026-09-02 attempt, keep them:
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
// TWO THINGS THIS PASS ADDED. The 2026-09-02 note read the whole remaining gap
// as one register swap; it was not. The body was also 31 bytes SHORT, and that
// shortfall had two separate causes, both now fixed:
//
//   1. `locale old;` through the DEFAULT constructor, not `locale old(impl)`.
//      stlport_locale.cpp already carries that constructor and it opens with
//      `_M_impl = 0;` before the add-ref. That null store is not dead code --
//      it is retail's `xor esi,esi` / `mov [esp+0xc],esi` pair at +0x1B, and a
//      pointer-taking constructor has nothing to emit there. Fixing this took
//      the exact prefix to 43 bytes, through the whole prologue and the first
//      _M_incr.
//
//   2. The lock is held by an _STLP_auto_lock GUARD OBJECT, not by a bare
//      _M_acquire_lock/_M_release_lock pair. vendor/stlport/stl/_threads.h:489
//      shows the guard holds `_STLP_STATIC_MUTEX& _M_lock` -- a reference --
//      and that reference is what retail spills at +0x4B as
//      `c7 44 24 3c 1c eb dd 00`: the address the unwind funclet needs to
//      release the lock if the guarded body throws. The bare pair gives the
//      funclet no object to hold, so MSVC drops that store, the two extra
//      unwind states (`c6 44 24 2c 02` at +0x63 and `c6 44 24 30 01` at +0x7A)
//      and the funclet with them. Adding the guard recovered all of it:
//      283 -> 301 bytes of 314, similarity 0.637 -> 0.758.
//
// THE ONE REMAINING GAP is the register swap the earlier note described, and it
// is now the ONLY difference in the first 300 bytes. Retail keeps the old impl
// in ebp and the argument in ebx; MSVC 7.1 does the reverse:
//
//   retail   +0x2A  8b e9        mov ebp, ecx     ... 8b 5c 24 38  mov ebx,[esp+0x38]
//   this     +0x2A  8b d9        mov ebx, ecx     ... 8b 6c 24 38  mov ebp,[esp+0x38]
//
// Everything downstream is the mirror image of retail, instruction for
// instruction, and every dereference of the argument then pays ebp's
// displacement byte (`8b 4d 00` where retail has `8b 0b`).
//
// Ruled out for the swap, do not re-try: naming the new impl as its own local;
// hoisting L._M_impl into a named local (retail re-reads [ebx] at +0x37 and
// +0x6B, so it is not hoisted); reordering the two add-refs (retail's global
// incr provably precedes L's, so that order is fixed by the bytes).
//
// Untried ideas for the next pass, in the order worth trying: give `old` a
// longer live range so the allocator ranks it above the parameter; try the
// body as a member `locale::global` (__cdecl static) rather than the free
// _Stl_global, which changes how the parameter is ranked; and try moving the
// whole body into stlport_locale.cpp, whose locale/_Locale_impl declarations
// this file duplicates, in case the shared declarations change the ranking.
//
// Measured this pass:
//   variant                                    bytes   exact prefix  similarity
//   locale old(impl), bare lock  (2026-09-02)   283         43          0.637
//   locale old, _STLP_auto_lock  (this stash)   301         43          0.758
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 locale::global. It takes a reference on the impl that is about
// to be replaced, installs the new one under the spin lock at 0x00007690, and
// hands the old one back by value; a named locale also reaches setlocale.

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

_Locale_impl *_Stl_classic_locale_impl;

// The default constructor, spelled exactly as stlport_locale.cpp already
// carries it: the null store is not dead code here, it is retail's
// `xor esi,esi` / `mov [esp+0xc],esi` pair at +0x1B, and constructing `old`
// through this constructor rather than through a pointer-taking one is what
// puts the old impl in ebp and leaves ebx for the argument.
__forceinline locale::locale()
{
	_M_impl = 0;
	_M_impl = _M_add_ref(_Stl_classic_locale_impl);
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

// STLport 4.5.3 stl/_threads.h: the guard holds a REFERENCE to the mutex, and
// that reference is what retail spills to [esp+0x3c] as
// `c7 44 24 3c 1c eb dd 00` -- the address the unwind funclet needs to release
// the lock if the body throws. A bare _M_acquire_lock/_M_release_lock pair has
// no object for the funclet to hold and loses that store, the extra unwind
// state and the funclet with it.
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

_STLP_mutex_base _Stl_locale_lock;
extern const string _Nameless;

locale __cdecl _Stl_global(const locale &L)
{
	locale old;

	_M_add_ref(L._M_impl);

	{
		_STLP_auto_lock lock(_Stl_locale_lock);
		_Stl_classic_locale_impl->_M_decr();
		_Stl_classic_locale_impl = L._M_impl;
	}

	if (L.name() != _Nameless)
		setlocale(0, L.name().data());

	return old;
}

}
