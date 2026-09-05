// ?do_put@?$money_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@_NAAVios_base@2@DO@Z
// partial score=0.95 date=2026-09-05
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 money_put<char>::do_put over long double, retail 0x0000BDA0,
// 174 bytes. vendor/stlport/stl/_monetary.h's base-class implementation
// ignores the units value entirely and formats nothing:
//
//   locale __loc = __str.getloc();
//   _CharT __buf[64];
//   return do_put(__s, __intl, __str, __fill, __buf + 0);
//
// __buf is uninitialized; its address decays through basic_string's
// converting constructor into a temporary string, and that temporary is
// handed by const reference to the do_put(string) overload through the
// vtable. Retail never overrides either do_put, so this really is what it
// puts on the wire for the long-double overload -- whatever garbage bytes
// happen to be on the stack, until the first NUL.
//
// 174 bytes against retail's 174, and all but five load/store displacements
// identical. Three things got it this far, each already established
// elsewhere in this codebase:
//
//   * free() needs C++ linkage, not extern "C" -- the mangled declaration is
//     what makes the caller emit the byte EH-state store before the call
//     (reverse/symbols.csv's note on ?free@@YAXPAX@Z).
//   * allocator<CharT> needs a user-declared default constructor, or the
//     string ctor's defaulted allocator argument is VALUE-initialised and
//     costs an extra zero-store MSVC 7.1 has no dead slot to absorb
//     (the same trap stlport_locale_impl_ctor.cpp records).
//   * the string temporary's _STLP_alloc_proxy member has to be dropped
//     entirely, not just emptied -- keeping it (even as an empty-base
//     member costing nothing by EBO) pads the frame by 4 bytes and knocks
//     every later local four bytes out of place. That one variable is what
//     took this from "shape wrong, sizes wrong" to "byte-identical except
//     which stack slot `__loc` lands in."
//
// What is left: retail reuses the incoming `str` parameter's now-dead slot
// (offset 0x74 off entry) for `__loc`'s storage -- the same dead-parameter
// reuse seen throughout this codebase -- while this body gives `__loc` a
// fresh slot at offset 0x08 and shifts the digits temporary from 0x10 to
// 0x14 to make room. Declaration order (loc/buf either way) does not move
// it; the lever is presumably something about how many other locals compete
// for that first dead slot.

void __cdecl free(void *block);

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator
{
public:
	allocator() {}
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string(const CharT *first, const Alloc &alloc = Alloc());

	~basic_string()
	{
		if (_M_start != 0)
			free(_M_start);
	}

private:
	CharT *_M_start;
	CharT *_M_finish;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

class _Locale_impl;

class locale
{
public:
	class facet
	{
	public:
		virtual ~facet();
	};

	__declspec(dllimport) __forceinline locale(_Locale_impl *impl);
	__declspec(dllimport) __forceinline ~locale();

private:
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

__forceinline locale::locale(_Locale_impl *impl)
{
	impl->_M_incr();
	_M_impl = impl;
}

__forceinline locale::~locale()
{
	_M_impl->_M_decr();
}

class ios_base
{
public:
	locale getloc() const;
};

template <class CharT, class Traits>
class ostreambuf_iterator
{
private:
	void *_M_buf;
	bool _M_ok;
};

template <class CharT, class OutputIter>
class money_put : public locale::facet
{
public:
	typedef basic_string<CharT, char_traits<CharT>, allocator<CharT> > string_type;

protected:
	virtual OutputIter do_put(OutputIter s, bool intl, ios_base &str,
			CharT fill, long double /* units */) const
	{
		locale loc = str.getloc();
		CharT buf[64];
		return do_put(s, intl, str, fill, buf + 0);
	}

	virtual OutputIter do_put(OutputIter s, bool intl, ios_base &str,
			CharT fill, const string_type &digits) const;
};

typedef ostreambuf_iterator<char, char_traits<char> > narrow_output_iterator;

template narrow_output_iterator money_put<char, narrow_output_iterator>::do_put(
		narrow_output_iterator, bool, ios_base &, char, long double) const;

}
