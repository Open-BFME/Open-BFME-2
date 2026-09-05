// ??$__put_integer@V?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@YA?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@0@PAD0V10@AAVios_base@0@HD@Z
// partial score=0.97 date=2026-09-05
//
// 214 bytes against retail's 214, and 208 of them identical.  All six that
// differ are stack displacement bytes in two spill slots, listed at the end.
//
// Three corrections to the previous version of this stash, each of which moved
// the body closer:
//
//   * the callee at 0x000179B0 takes FOUR arguments, not three.  The stack
//     cleanup after it is `83 c4 10`.  reverse/functions.csv already claims
//     that address as ?__copy_trivial@_STL@@YAPAXPBX0PAX@Z and
//     reverse/symbols.csv pins the same address as
//     ??$__copy_aux@PADPAD@_STL@@YAPADPAD00ABU__true_type@0@@Z: the two are
//     identical-code-folded, and it is the four-argument __copy_aux spelling
//     that retail calls here, with __true_type passed by const reference.
//     Declaring the three-argument __copy_trivial at this site was what kept
//     the earlier version structurally apart.
//   * the tag argument must be DEFAULT-initialised, not value-initialised.
//     `_Ret()` makes MSVC emit `c6 44 24 6c 00` to zero the empty object;
//     retail has no such store, and a named `_Ret both_are_pointers;` has
//     none either.
//   * the body must follow vendor/stlport/stl/_num_put.c exactly: reassign
//     BOTH __buf and __iend to the scratch buffer before calling
//     __insert_grouping, and pass '+' and '-' as literals.  The earlier
//     version hoisted plus/minus into locals at the top and passed
//     local_buffer/local_buffer+length directly, which changed the register
//     allocation -- retail keeps `buf` live in ebx and `f` in ebp, and only
//     this shape reproduces that.
//
// What is left, at offsets into the body:
//
//   +0x21          retail spills the numpunct facet to [esp+0x58]; this body
//                  spills it to [esp+0x68].
//   +0x47 +0x4D +0x57  retail keeps basechars at [esp+0x5c]; this body keeps
//                  it at [esp+0x58].
//   +0x70 +0x74    the two reloads of those same two slots.
//
// So retail packs the facet and basechars into the two halves of the
// by-value ostreambuf_iterator parameter slot, and this body packs basechars
// into the dead __iend slot and the facet higher up.  Nothing else differs:
// same length, same instructions, same registers, same branch displacements.
// It is purely which dead incoming-parameter slot MSVC picks for two spills.
// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// The narrow twin of 0x00010A70, and three structural differences from it,
// each worth a chunk of the body:
//
//   * no locale temporary. The wide unit opens with stream.getloc(); retail's
//     narrow body reads the numpunct facet straight out of ios_base at +0x44
//     and never builds a locale, so there is no /EHsc frame at all - that
//     frame alone is twenty of the wide body's bytes.
//   * no widen. plus and minus are the literals 0x2B and 0x2D pushed
//     directly, where the wide unit runs them through ctype::widen.
//   * the buffer copy moves INSIDE the grouping branch. The wide unit has to
//     copy unconditionally because it is widening; the narrow one only needs a
//     scratch copy when __insert_grouping is about to rewrite it in place.

typedef int ptrdiff_t;

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
	__declspec(dllimport) __forceinline bool empty() const
	{
		return _M_start == _M_finish;
	}

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

class _Locale_impl
{
public:
	virtual void _M_unused();
	virtual void _M_incr();
	virtual void _M_decr();
};

class locale
{
public:
	class facet
	{
	public:
		virtual ~facet();
	};

	__declspec(dllimport) __forceinline ~locale()
	{
		_M_impl->_M_decr();
	}

private:
	_Locale_impl *_M_impl;
};

template <class CharT>
class ctype;

template <>
class ctype<char> : public locale::facet
{
public:
	__declspec(dllimport) __forceinline char widen(char character) const
	{
		return do_widen(character);
	}
	__declspec(dllimport) __forceinline const char *widen(
			const char *first, const char *last, char *out) const
	{
		return do_widen(first, last, out);
	}

protected:
	virtual ~ctype();
	virtual bool do_is(unsigned short, char) const;
	virtual const char *do_is(
			const char *, const char *, unsigned short *) const;
	virtual const char *do_scan_is(
			unsigned short, const char *, const char *) const;
	virtual const char *do_scan_not(
			unsigned short, const char *, const char *) const;
	virtual char do_toupper(char) const;
	virtual const char *do_toupper(char *, const char *) const;
	virtual char do_tolower(char) const;
	virtual const char *do_tolower(char *, const char *) const;
	virtual char do_widen(char) const;
	virtual const char *do_widen(
			const char *, const char *, char *) const;
	virtual char do_narrow(char, char) const;
	virtual const char *do_narrow(
			const char *, const char *, char, char *) const;
};

template <class CharT>
class numpunct;

template <>
class numpunct<char> : public locale::facet
{
public:
	__declspec(dllimport) __forceinline char thousands_sep() const
	{
		return do_thousands_sep();
	}

protected:
	virtual ~numpunct();
	virtual char do_decimal_point() const;
	virtual char do_thousands_sep() const;
};

class ios_base
{
public:
	typedef int fmtflags;
	typedef int streamsize;

	enum
	{
		hex = 0x0010,
		oct = 0x0020,
		basefield = 0x0038,
		showbase = 0x0200
	};

	locale getloc() const;
	__declspec(dllimport) __forceinline fmtflags flags() const
	{
		return _M_fmtflags;
	}
	__declspec(dllimport) __forceinline streamsize width(streamsize value)
	{
		streamsize previous = _M_width;
		_M_width = value;
		return previous;
	}
	__declspec(dllimport) __forceinline const locale::facet *_M_ctype_facet() const
	{
		return _M_cached_ctype;
	}
	__declspec(dllimport) __forceinline const locale::facet *_M_numpunct_facet() const
	{
		return _M_cached_numpunct;
	}
	__declspec(dllimport) __forceinline const narrow_string &_M_grouping() const
	{
		return _M_cached_grouping;
	}

private:
	void *_M_vptr;
	fmtflags _M_fmtflags;
	int _M_iostate;
	int _M_openmode;
	int _M_seekdir;
	int _M_exception_mask;
	streamsize _M_precision;
	streamsize _M_width;
	locale _M_locale;
	void *_M_callbacks;
	unsigned int _M_num_callbacks;
	unsigned int _M_callback_index;
	long *_M_iwords;
	unsigned int _M_num_iwords;
	void **_M_pwords;
	unsigned int _M_num_pwords;
	locale::facet *_M_cached_ctype;
	locale::facet *_M_cached_numpunct;
	narrow_string _M_cached_grouping;
};

template <class CharT, class Traits>
class ostreambuf_iterator
{
private:
	void *_M_buf;
	bool _M_ok;
};

ptrdiff_t __cdecl __insert_grouping(
		char *, char *, const narrow_string &,
		char, char, char, int);

template <class CharT, class OutputIter>
OutputIter __cdecl __copy_integer_and_fill(
		const CharT *, ptrdiff_t, OutputIter,
		ios_base::fmtflags, ios_base::streamsize, CharT, CharT, CharT);

struct __true_type {};

template <class InputIter, class OutputIter>
struct _BothPtrType
{
	typedef __true_type _Ret;
};

template <class InputIter, class OutputIter>
OutputIter __cdecl __copy_aux(InputIter first, InputIter last, OutputIter result,
		const __true_type &);

template <class InputIter, class OutputIter>
inline OutputIter __cdecl copy(InputIter first, InputIter last,
		OutputIter result)
{
	typename _BothPtrType<InputIter, OutputIter>::_Ret both_are_pointers;
	return __copy_aux(first, last, result, both_are_pointers);
}

template <class OutputIter>
OutputIter __cdecl __put_integer(
		char *buf, char *iend, OutputIter s,
		ios_base &f, ios_base::fmtflags flags, char fill)
{
	ptrdiff_t len = iend - buf;

	const numpunct<char> &np =
			*(const numpunct<char> *)f._M_numpunct_facet();
	const narrow_string &grouping = f._M_grouping();

	if (!grouping.empty())
	{
		int basechars;
		if (flags & ios_base::showbase)
			switch (flags & ios_base::basefield)
			{
			case ios_base::hex:
				basechars = 2;
				break;
			case ios_base::oct:
				basechars = 1;
				break;
			default:
				basechars = 0;
			}
		else
			basechars = 0;

		// make sure there is room at the end of the buffer
		// we pass to __insert_grouping
		char grpbuf[64];
		copy(buf, iend, (char *)grpbuf);
		buf = grpbuf;
		iend = grpbuf + len;
		len = __insert_grouping(buf, iend, grouping, np.thousands_sep(),
				'+', '-', basechars);
	}

	return __copy_integer_and_fill(buf, len, s, flags, f.width(0), fill,
			'+', '-');
}

typedef ostreambuf_iterator<char, char_traits<char> > narrow_output_iterator;

template narrow_output_iterator __put_integer<narrow_output_iterator>(
		char *, char *, narrow_output_iterator,
		ios_base &, ios_base::fmtflags, char);

}
