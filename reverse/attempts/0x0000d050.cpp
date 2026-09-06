// ??$__put_integer@V?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@YA?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@0@PAD0V10@AAVios_base@0@HD@Z
// partial score=0.97 date=2026-09-06
// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// KEEP THE TWO LINES ABOVE AT THE TOP.  tools/build.py scans only a prefix of
// the file for them, and this header had grown long enough that `// cl:` sat at
// byte ~2538 and was silently ignored -- the body was compiling on the base
// flags alone.  Any flag conclusion recorded against this body BEFORE that was
// found is worthless and must be re-tested with the directive inside the
// window.
//
// 214 bytes against retail's 214, and 208 of them identical.  All six that
// differ are stack displacement bytes, listed at the end.
//
// THE FRAME, decoded from the target (this corrects the earlier note here,
// which said retail packs the spills into the by-value ostreambuf_iterator
// parameter slot -- it does not, and that claim sent two sessions the wrong
// way).  The prologue is `sub esp,0x40` then push ebx/ebp/esi/edi, so with
// E = entry esp the baseline is E-0x50 and the map is:
//
//   [esp+0x00..0x10)  the four saved registers
//   [esp+0x10..0x50)  grpbuf[64] -- exactly 0x40 bytes, the WHOLE local block
//   [esp+0x50]        return address
//   [esp+0x54]        hidden sret pointer
//   [esp+0x58]        buf          [esp+0x5c]  iend
//   [esp+0x60]        s._M_buf     [esp+0x64]  s._M_ok
//   [esp+0x68]        f            [esp+0x6c]  flags      [esp+0x70]  fill
//
// `lea edx,[esp+0x14]` one push deep confirms grpbuf at baseline+0x10, and the
// tail confirms the sret: __copy_integer_and_fill cleans 0x28 = ten dwords =
// sret + buf + len + s(2) + flags + width + fill + '+' + '-', and the epilogue
// returns the hidden pointer in eax via `mov eax,esi`.
//
// So the local block is entirely consumed by grpbuf.  There is no free local
// space at all, which is WHY this body is contended: both compilers are forced
// to spill into dead incoming-parameter homes, and the frame size is identical
// (0x40 on both sides), so the only remaining freedom is which home each spill
// takes.
//
//   retail:    facet -> 0x58 (buf's home)    basechars -> 0x5c (iend's home)
//   this body: facet -> 0x68 (f's home)      basechars -> 0x58 (buf's home)
//
// The iterator's own home at 0x60/0x64 is untouched by BOTH.  Retail takes the
// two lowest dead homes in spill order; this build does not.
//
// The six differing bytes, at offsets into the body:
//
//   +0x21              facet spill        target 58, here 68
//   +0x47 +0x4D +0x57  basechars stores   target 5c, here 58
//   +0x70 +0x74        the reloads of those SAME two slots, seen through an esp
//                      lowered 0x10 by the four argument pushes for
//                      __insert_grouping: target 6c/68, here 68/78.  They are
//                      not a third and fourth slot.
//
// REFUTED, all measured with the `// cl:` line inside the scan window so the
// flags genuinely reached cl.exe.  None reduced the diff below 6 and none moved
// either slot toward retail:
//
//   inert:      /Ow /Oy /Ot /Og /Ob1 /Ob2 /Oi /Ox /Gy /GF /Zi /G5 /G6 /GA /GT
//               /Zp4 /Zp16 /Oa /Ow
//   wreck it:   /Oa (206 bytes), /Os and /O1 (183), /GS (199 diff), /G7 (212),
//               /Zp1 (keeps the 6, adds ~52 more)
//
// Source shapes refuted too, all inert at 6 bytes except where noted: hoisting
// basechars to function scope; swapping the grouping/np declaration order; np
// as a pointer instead of a reference; writing the __copy_aux call out by hand
// with the tag hoisted.  Moving the np declaration inside the if-block behaves
// exactly like /Oa -- 206 bytes, a different shape, worse.
//
// This is the same wall as 0x00019260 (_Init_timeinfo, sret temporary in a dead
// param slot), 0x0000C000/0x0000DAA0 (money_get, two callee-saved registers
// against retail's four) and _M_fill_insert (commit 8e15a12, one dead dword).
// Four bodies, correct instruction streams, all blocked on MSVC 7.1's allocator
// preference and all refuted against flag sweeps.  Untried here: perturbing the
// slot-allocation ORDER rather than the shapes -- changing basechars' type or
// width, or introducing a dummy local, so the two spilled values stop having
// identical live-range shapes.
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
//   * the wide twin never reuses a parameter home at all: three stores in its
//     whole 332 bytes, all either /EHs scaffolding or a low local.  It offers
//     no template for the narrow body's packing.

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
