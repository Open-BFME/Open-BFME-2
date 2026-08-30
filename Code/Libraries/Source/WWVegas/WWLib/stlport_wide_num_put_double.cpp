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
	void reserve(size_type);
	__declspec(dllimport) __forceinline const CharT *c_str() const
	{
		return _M_start;
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
	__declspec(dllimport) __forceinline streamsize precision() const
	{
		return _M_precision;
	}
	__declspec(dllimport) __forceinline const void *_M_numpunct_facet() const
	{
		return _M_cached_numpunct;
	}
	__declspec(dllimport) __forceinline const narrow_string &_M_grouping() const
	{
		return _M_cached_grouping;
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

template <class CharT, class Traits>
class ostreambuf_iterator
{
private:
	void *_M_buf;
	bool _M_ok;
};

template <class CharT>
class numpunct;

template <>
class numpunct<wchar_t>
{
public:
	__declspec(dllimport) __forceinline wchar_t decimal_point() const
	{
		return do_decimal_point();
	}
	__declspec(dllimport) __forceinline wchar_t thousands_sep() const
	{
		return do_thousands_sep();
	}

protected:
	virtual ~numpunct();
	virtual wchar_t do_decimal_point() const;
	virtual wchar_t do_thousands_sep() const;
};

void __cdecl __write_float(
		narrow_string &, ios_base::fmtflags, int, double);

template <class OutputIter>
OutputIter __cdecl __put_float(
		char *, char *, OutputIter, ios_base &, wchar_t, wchar_t, wchar_t,
		const narrow_string &);

template <class CharT, class OutputIter, class Float>
OutputIter __cdecl _M_do_put_float(
		OutputIter out, ios_base &stream, CharT fill, Float value)
{
	narrow_string buffer;
	buffer.reserve(128);
	__write_float(
			buffer, stream.flags(), static_cast<int>(stream.precision()), value);

	const numpunct<CharT> &punctuation =
			*static_cast<const numpunct<CharT> *>(
					stream._M_numpunct_facet());

	return __put_float(
			const_cast<char *>(buffer.c_str()),
			const_cast<char *>(buffer.c_str()) + buffer.size(),
			out, stream, fill, punctuation.decimal_point(),
			punctuation.thousands_sep(), stream._M_grouping());
}

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_output_iterator;

template wide_output_iterator _M_do_put_float<
		wchar_t, wide_output_iterator, double>(
		wide_output_iterator, ios_base &, wchar_t, double);

}
