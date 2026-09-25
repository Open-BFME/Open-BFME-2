// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow-string range constructions that retail keeps as
// small out-of-line bodies next to the string TU's own emissions.
//
// WHAT THE BYTES SHOW. Five unclaimed bodies in the 0x000177E0-0x00019D30
// band share one shape: an SEH prolog, three zeroed dwords into the
// destination, then a single call into the ledger's matched narrow 2-arg
// range initialiser at 0x00008D00, returning the destination:
//
// - 0x000177E0 (80B): genuine thiscall over (first, last, alloc); the
//   allocator is stateless so the third parameter is ignored. Same
//   signature as the template range ctor rowed at 0x00017830, but retail
//   keeps the 2-arg initialiser out of line here instead of inlining down
//   to the 3-arg tag overload, so this address is a dup_ of that name.
// - 0x00017890 (82B): hidden-pointer shape (this unused) over two range
//   parameters; a method returning a string by value whose temporary
//   range ctor range-initialises directly into the hidden result.
// - 0x00017A40 / 0x00017AA0 / 0x00019D30 (85B each): hidden-pointer shape
//   over no parameters; methods returning a copy of a static empty narrow
//   string. The copy constructor zeroes first and only then reads the
//   static's start/finish, which is why the global loads sit below the
//   zeroing (a temporary would evaluate its arguments first). Each static
//   is 16 zero bytes in .data, pinned below.
//
// WHY THIS MODEL. The TU mirrors the Code/WWLib/stlport_narrow_string_cstr_ctor.cpp
// precedent: minimal _STL replicas with an inline base (so the zeroing is
// inlined) and a declared-only 2-arg range initialiser (so the call stays
// out of line and resolves by name to 0x00008D00). The temporary/copy
// constructions inline into the hidden result exactly like retail.

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
	_STLP_alloc_proxy(const Alloc &a, Pointer data) : Alloc(a), _M_data(data) {}

	Pointer _M_data;
};

template <class CharT, class Alloc>
class _String_base
{
public:
	_String_base(const Alloc &a) : _M_start(0), _M_finish(0), _M_end_of_storage(a, 0) {}
	~_String_base();

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	typedef Alloc allocator_type;

	template <class InputIter>
	basic_string(InputIter f, InputIter l, const Alloc &a) : _String_base<CharT, Alloc>(a)
	{
		_M_range_initialize(f, l);
	}

	basic_string(const basic_string &src) : _String_base<CharT, Alloc>(allocator_type())
	{
		_M_range_initialize(src._M_start, src._M_finish);
	}

	const allocator_type &get_allocator() const;

	template <class InputIter>
	void _M_range_initialize(InputIter f, InputIter l);
};

typedef basic_string<char, char_traits<char>, allocator<char> > NStr;

// 0x000177E0: the out-of-line template range ctor (dup_ of the name rowed
// at 0x00017830, whose TU inlines down to the 3-arg tag overload instead).
template NStr::basic_string(char *, char *, const allocator<char> &);

}

// Static empty narrow strings copied by the three no-parameter inits below.
// Each is 16 zero bytes in .data; the copy reads start at +0 and finish at +4.
extern const _STL::NStr g_00DDEF08StaticEmpty;
extern const _STL::NStr g_00DDEEFCStaticEmpty;
extern const _STL::NStr g_00DDEF38StaticEmpty;

class Rva00017890StringInit
{
public:
	_STL::NStr init(char *first, char *last);
};

// 0x00017890: build a narrow string from an explicit pointer range.
_STL::NStr Rva00017890StringInit::init(char *first, char *last)
{
	_STL::allocator<char> al;
	return _STL::NStr(first, last, al);
}

class Rva00017A40StringInit
{
public:
	_STL::NStr init();
};

// 0x00017A40: copy of the static empty at 0x00DDEF08.
_STL::NStr Rva00017A40StringInit::init()
{
	return g_00DDEF08StaticEmpty;
}

class Rva00017AA0StringInit
{
public:
	_STL::NStr init();
};

// 0x00017AA0: copy of the static empty at 0x00DDEEFC.
_STL::NStr Rva00017AA0StringInit::init()
{
	return g_00DDEEFCStaticEmpty;
}

class Rva00019D30StringInit
{
public:
	_STL::NStr init();
};

// 0x00019D30: copy of the static empty at 0x00DDEF38.
_STL::NStr Rva00019D30StringInit::init()
{
	return g_00DDEF38StaticEmpty;
}
