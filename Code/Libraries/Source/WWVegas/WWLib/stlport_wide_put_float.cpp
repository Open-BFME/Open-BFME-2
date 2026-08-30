// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport

typedef unsigned short wchar_t;

namespace _STL
{

extern "C" void __cdecl free(void *);

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

	basic_string();
	basic_string(const basic_string &);
	void push_back(CharT value);
	__declspec(dllimport) __forceinline bool empty() const
	{
		return _M_start == _M_finish;
	}
	__declspec(dllimport) __forceinline CharT &operator[](size_type offset)
	{
		return _M_start[offset];
	}
	__declspec(dllimport) __forceinline const CharT &operator[](size_type offset) const
	{
		return _M_start[offset];
	}
	__declspec(dllimport) __forceinline size_type size() const
	{
		return static_cast<size_type>(_M_finish - _M_start);
	}
	__forceinline ~basic_string()
	{
		if (_M_start != 0)
			free(_M_start);
	}

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

class ios_base
{
public:
	typedef int fmtflags;
	typedef int iostate;
	typedef int openmode;
	typedef int seekdir;
	typedef int streamsize;

	virtual ~ios_base();
	__declspec(dllimport) __forceinline fmtflags flags() const
	{
		return _M_fmtflags;
	}
	__declspec(dllimport) __forceinline streamsize width(streamsize value)
	{
		streamsize old = _M_width;
		_M_width = value;
		return old;
	}
	__declspec(dllimport) __forceinline const void *_M_ctype_facet() const
	{
		return _M_cached_ctype;
	}

private:
	fmtflags _M_fmtflags;
	iostate _M_iostate;
	openmode _M_openmode;
	seekdir _M_seekdir;
	iostate _M_exception_mask;
	streamsize _M_precision;
	streamsize _M_width;
	void *_M_locale;
	void *_M_callbacks;
	unsigned int _M_num_callbacks;
	unsigned int _M_callback_index;
	long *_M_iwords;
	unsigned int _M_num_iwords;
	void **_M_pwords;
	unsigned int _M_num_pwords;
	void *_M_cached_ctype;
	void *_M_cached_numpunct;
	narrow_string _M_cached_grouping;
};

template <class CharT>
class ctype;

class locale
{
public:
	class facet
	{
	public:
		virtual ~facet();
	};
};

template <>
class ctype<wchar_t> : public locale::facet
{
public:
	__declspec(dllimport) __forceinline wchar_t widen(char value) const
	{
		return do_widen(value);
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

template <class CharT, class Traits>
class ostreambuf_iterator
{
private:
	void *_M_buf;
	bool _M_ok;
};

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class InputIter, class Value>
InputIter __cdecl __find(
		InputIter, InputIter, const Value &, const random_access_iterator_tag &);

template <class InputIter, class Value>
__declspec(dllimport) __forceinline InputIter find(
		InputIter first, InputIter last, const Value &value)
{
	return __find(first, last, value, random_access_iterator_tag());
}

wchar_t *__cdecl __convert_float_buffer(
		const char *, const char *, wchar_t *, const ctype<wchar_t> &, wchar_t);

int __cdecl __insert_grouping(
		wchar_t *, wchar_t *, const narrow_string &, wchar_t,
		wchar_t, wchar_t, int);

template <class CharT, class OutputIter>
OutputIter __cdecl __copy_float_and_fill(
		const CharT *, const CharT *, OutputIter, ios_base::fmtflags,
		ios_base::streamsize, CharT, CharT, CharT);

template <class OutputIter>
OutputIter __cdecl __put_float(
		char *buffer, char *end, OutputIter out, ios_base &stream, wchar_t fill,
		wchar_t decimal_point, wchar_t separator, const narrow_string &grouping)
{
	const ctype<wchar_t> &character_type =
			*static_cast<const ctype<wchar_t> *>(stream._M_ctype_facet());

	wchar_t wide_buffer[128];
	wchar_t *wide_end = __convert_float_buffer(
			buffer, end, wide_buffer, character_type, decimal_point);

	if (!grouping.empty())
	{
		narrow_string new_grouping = grouping;
		wchar_t *decimal_pos = find(wide_buffer, wide_end, decimal_point);
		if (grouping.size() == 1)
			new_grouping.push_back(grouping[0]);

		new_grouping[0] += static_cast<char>(wide_end - decimal_pos);
		int length = __insert_grouping(
				wide_buffer, wide_end, new_grouping, separator,
				character_type.widen('+'), character_type.widen('-'), 0);
		wide_end = wide_buffer + length;
	}

	return __copy_float_and_fill(
			wide_buffer, wide_end, out, stream.flags(), stream.width(0), fill,
			character_type.widen('+'), character_type.widen('-'));
}

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_output_iterator;

template wide_output_iterator __put_float<wide_output_iterator>(
		char *, char *, wide_output_iterator, ios_base &, wchar_t,
		wchar_t, wchar_t, const narrow_string &);

}
