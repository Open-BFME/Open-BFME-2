// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport

typedef unsigned short wchar_t;
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
class ctype<wchar_t> : public locale::facet
{
public:
	__declspec(dllimport) __forceinline wchar_t widen(char character) const
	{
		return do_widen(character);
	}
	__declspec(dllimport) __forceinline const char *widen(
			const char *first, const char *last, wchar_t *out) const
	{
		return do_widen(first, last, out);
	}

protected:
	virtual ~ctype();
	virtual bool do_is(unsigned short, wchar_t) const;
	virtual const wchar_t *do_is(
			const wchar_t *, const wchar_t *, unsigned short *) const;
	virtual const wchar_t *do_scan_is(
			unsigned short, const wchar_t *, const wchar_t *) const;
	virtual const wchar_t *do_scan_not(
			unsigned short, const wchar_t *, const wchar_t *) const;
	virtual wchar_t do_toupper(wchar_t) const;
	virtual const wchar_t *do_toupper(wchar_t *, const wchar_t *) const;
	virtual wchar_t do_tolower(wchar_t) const;
	virtual const wchar_t *do_tolower(wchar_t *, const wchar_t *) const;
	virtual wchar_t do_widen(char) const;
	virtual const char *do_widen(
			const char *, const char *, wchar_t *) const;
	virtual char do_narrow(wchar_t, char) const;
	virtual const wchar_t *do_narrow(
			const wchar_t *, const wchar_t *, char, char *) const;
};

template <class CharT>
class numpunct;

template <>
class numpunct<wchar_t> : public locale::facet
{
public:
	__declspec(dllimport) __forceinline wchar_t thousands_sep() const
	{
		return do_thousands_sep();
	}

protected:
	virtual ~numpunct();
	virtual wchar_t do_decimal_point() const;
	virtual wchar_t do_thousands_sep() const;
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
		wchar_t *, wchar_t *, const narrow_string &,
		wchar_t, wchar_t, wchar_t, int);

template <class CharT, class OutputIter>
OutputIter __cdecl __copy_integer_and_fill(
		const CharT *, ptrdiff_t, OutputIter,
		ios_base::fmtflags, ios_base::streamsize, CharT, CharT, CharT);

template <class OutputIter>
OutputIter __cdecl __put_integer(
		char *buffer, char *buffer_end, OutputIter out,
		ios_base &stream, ios_base::fmtflags flags, wchar_t fill)
{
	locale current_locale = stream.getloc();
	const ctype<wchar_t> &character_type =
			*static_cast<const ctype<wchar_t> *>(stream._M_ctype_facet());

	wchar_t plus = character_type.widen('+');
	wchar_t minus = character_type.widen('-');

	wchar_t wide_buffer[64];
	character_type.widen(buffer, buffer_end, wide_buffer);
	ptrdiff_t length = buffer_end - buffer;
	wchar_t *wide_buffer_end = wide_buffer + length;

	const numpunct<wchar_t> &punctuation =
			*static_cast<const numpunct<wchar_t> *>(
					stream._M_numpunct_facet());
	const narrow_string &grouping = stream._M_grouping();

	if (!grouping.empty())
	{
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

		length = __insert_grouping(
				wide_buffer, wide_buffer_end, grouping,
				punctuation.thousands_sep(), plus, minus,
				base_characters);
	}

	return __copy_integer_and_fill(
			wide_buffer, length, out, flags, stream.width(0), fill,
			plus, minus);
}

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_output_iterator;

template wide_output_iterator __put_integer<wide_output_iterator>(
		char *, char *, wide_output_iterator,
		ios_base &, ios_base::fmtflags, wchar_t);

}
