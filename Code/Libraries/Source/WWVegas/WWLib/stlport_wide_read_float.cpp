// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport

typedef unsigned short wchar_t;

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
	void push_back(CharT);
	__declspec(dllimport) __forceinline unsigned int size() const
	{
		return static_cast<unsigned int>(_M_finish - _M_start);
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
	class id
	{
	public:
		unsigned int _M_index;
	};

	class facet {};

	__declspec(dllimport) __forceinline ~locale()
	{
		_M_impl->_M_decr();
	}

	facet *_M_use_facet(const id &) const;

private:
	_Locale_impl *_M_impl;
};

template <class CharT>
class ctype : public locale::facet
{
public:
	static locale::id id;
};

template <class Facet>
__declspec(dllimport) __forceinline const Facet &use_facet(const locale &value)
{
	return *static_cast<const Facet *>(value._M_use_facet(Facet::id));
}

class ios_base
{
public:
	locale getloc() const;
	__declspec(dllimport) __forceinline const void *_M_numpunct_facet() const
	{
		return _M_cached_numpunct;
	}
	__declspec(dllimport) __forceinline const narrow_string &_M_grouping() const
	{
		return _M_cached_grouping;
	}

private:
	void *_M_vptr;
	int _M_fmtflags;
	int _M_iostate;
	int _M_openmode;
	int _M_seekdir;
	int _M_exception_mask;
	int _M_precision;
	int _M_width;
	locale _M_locale;
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

template <class CharT, class Traits>
class basic_streambuf
{
public:
	CharT sbumpc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	bool equal(const istreambuf_iterator &) const;
	__declspec(dllimport) __forceinline bool _M_equal_inline(
			const istreambuf_iterator &other) const
	{
		if (_M_buf != 0)
			_M_getc();
		if (other._M_buf != 0)
			other._M_getc();
		return _M_eof == other._M_eof;
	}
	__declspec(dllimport) __forceinline CharT operator*() const
	{
		_M_getc();
		return _M_c;
	}
	__declspec(dllimport) __forceinline istreambuf_iterator &operator++()
	{
		_M_bumpc();
		return *this;
	}

private:
	void _M_getc() const;
	__declspec(dllimport) __forceinline void _M_bumpc()
	{
		_M_buf->sbumpc();
		_M_have_c = false;
	}

	basic_streambuf<CharT, Traits> *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

template <class InputIter, class CharT>
InputIter __cdecl __copy_sign(
		InputIter, InputIter, narrow_string &, CharT, CharT);

template <class InputIter, class CharT>
bool __cdecl __copy_digits(
		InputIter &, InputIter &, narrow_string &, const CharT *);

template <class InputIter, class CharT>
bool __cdecl __copy_grouped_digits(
		InputIter &, InputIter &, narrow_string &, const CharT *, CharT,
		const narrow_string &, bool &);

void __cdecl _Initialize_get_float(
		const ctype<wchar_t> &, wchar_t &, wchar_t &, wchar_t &, wchar_t &,
		wchar_t *);

template <class InputIter, class CharT>
bool __cdecl _M_read_float(
		narrow_string &buffer, InputIter &in, InputIter &end,
		ios_base &stream, CharT *)
{
	bool digits_before_dot;
	bool digits_after_dot = false;
	bool ok;
	bool grouping_ok = true;

	const ctype<CharT> &character_type =
			use_facet<ctype<CharT> >(stream.getloc());
	const numpunct<CharT> &punctuation =
			*static_cast<const numpunct<CharT> *>(stream._M_numpunct_facet());
	const narrow_string &grouping = stream._M_grouping();

	CharT dot = punctuation.decimal_point();
	CharT separator = punctuation.thousands_sep();
	CharT digits[10];
	CharT plus;
	CharT minus;
	CharT exponent_lower;
	CharT exponent_upper;

	_Initialize_get_float(
			character_type, plus, minus, exponent_lower, exponent_upper, digits);

	in = __copy_sign(in, end, buffer, plus, minus);

	if (grouping.size() != 0)
		digits_before_dot = __copy_grouped_digits(
				in, end, buffer, digits, separator, grouping, grouping_ok);
	else
		digits_before_dot = __copy_digits(in, end, buffer, digits);

	if (!in.equal(end) && *in == dot)
	{
		buffer.push_back('.');
		++in;
		digits_after_dot = __copy_digits(in, end, buffer, digits);
	}

	ok = digits_before_dot || digits_after_dot;

	if (ok && !in._M_equal_inline(end) &&
			(*in == exponent_lower || *in == exponent_upper))
	{
		buffer.push_back('e');
		++in;
		in = __copy_sign(in, end, buffer, plus, minus);
		ok = __copy_digits(in, end, buffer, digits);
	}

	return ok;
}

typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_iterator;

template bool _M_read_float<wide_iterator, wchar_t>(
		narrow_string &, wide_iterator &, wide_iterator &, ios_base &, wchar_t *);

}
