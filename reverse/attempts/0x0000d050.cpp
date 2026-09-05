// ??$__put_integer@V?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@YA?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@0@PAD0V10@AAVios_base@0@HD@Z
// partial score=0.97 date=2026-09-02
// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
//
// Callees, all three read out of retail's own REL32 displacements in this body
// (offsets relative to 0x0000D050): +0x68 -> 0x000179B0 __copy_trivial,
// +0x90 -> 0x0001A600 __insert_grouping, +0xC4 -> 0x000095E0
// __copy_integer_and_fill.  The last of these is now pinned in
// reverse/symbols.csv; without it the tail call verifies as unresolved.  The
// 40-byte cleanup after it (83 c4 28) corroborates the identification: ten
// dwords, which is this call's eight arguments with the iterator passed by
// value as two.
//
// What is left is register allocation, not shape -- the branch displacements
// already match exactly (74 6f, 74 20, 74 0e).  Retail keeps stream in ebp and
// spills the numpunct facet to [esp+0x58], reloading it at the thousands_sep
// call; this body keeps stream in ebx and the facet live in ebp, so it never
// spills.  Flipping that pair is the whole remaining gap.
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

void *__cdecl __copy_trivial(const void *first, const void *last, void *result);

template <class OutputIter>
OutputIter __cdecl __put_integer(
		char *buffer, char *buffer_end, OutputIter out,
		ios_base &stream, ios_base::fmtflags flags, char fill)
{
	char plus = '+';
	char minus = '-';

	ptrdiff_t length = buffer_end - buffer;

	const numpunct<char> &punctuation =
			*static_cast<const numpunct<char> *>(
					stream._M_numpunct_facet());
	const narrow_string &grouping = stream._M_grouping();

	if (!grouping.empty())
	{
		char local_buffer[64];
		int base_characters;
		if (flags & ios_base::showbase)
		{
			switch (flags & ios_base::basefield)
			{
			case ios_base::hex:
				base_characters = 2;
				break;
			case ios_base::oct:
				base_characters = 1;
				break;
			default:
				base_characters = 0;
			}
		}
		else
			base_characters = 0;

		__copy_trivial(buffer, buffer_end, local_buffer);

		length = __insert_grouping(
				local_buffer, local_buffer + length, grouping,
				punctuation.thousands_sep(), plus, minus,
				base_characters);

		buffer = local_buffer;
	}

	return __copy_integer_and_fill(
			buffer, length, out, flags, stream.width(0), fill,
			plus, minus);
}

typedef ostreambuf_iterator<char, char_traits<char> > narrow_output_iterator;

template narrow_output_iterator __put_integer<narrow_output_iterator>(
		char *, char *, narrow_output_iterator,
		ios_base &, ios_base::fmtflags, char);

}
