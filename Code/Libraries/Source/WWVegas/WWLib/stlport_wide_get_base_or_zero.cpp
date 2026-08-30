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
class ctype
{
public:
	static locale::id id;

	__declspec(dllimport) __forceinline const char *widen(
			const char *first, const char *last, CharT *out) const
	{
		return do_widen(first, last, out);
	}

protected:
	virtual ~ctype();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual const char *do_widen(const char *, const char *, CharT *) const;
};

template <class Facet>
__declspec(dllimport) __forceinline const Facet &use_facet(const locale &value)
{
	return *reinterpret_cast<const Facet *>(value._M_use_facet(Facet::id));
}

class ios_base
{
public:
	typedef int fmtflags;

	enum
	{
		dec = 0x0008,
		hex = 0x0010,
		oct = 0x0020,
		basefield = dec | hex | oct
	};

	locale getloc() const;
	__declspec(dllimport) __forceinline fmtflags flags() const
	{
		return _M_fmtflags;
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
class numpunct<char>
{
public:
	__declspec(dllimport) __forceinline char decimal_point() const
	{
		return do_decimal_point();
	}
	__declspec(dllimport) __forceinline char thousands_sep() const
	{
		return do_thousands_sep();
	}

protected:
	virtual ~numpunct();
	virtual char do_decimal_point() const;
	virtual char do_thousands_sep() const;
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	wchar_t sbumpc();
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

extern const char __narrow_atoms[];

template <class InputIter, class CharT>
int __cdecl _M_get_base_or_zero(
		InputIter &in, InputIter &end, ios_base &stream, CharT *)
{
	CharT atoms[5];
	const ctype<CharT> &characterType =
			use_facet<ctype<CharT> >(stream.getloc());

	characterType.widen(__narrow_atoms, __narrow_atoms + 5, atoms);

	bool negative = false;
	CharT character = *in;

	if (character == atoms[1])
	{
		negative = true;
		++in;
	}
	else if (character == atoms[0])
		++in;

	int base;
	int validZero = 0;

	ios_base::fmtflags basefield = stream.flags() & ios_base::basefield;

	switch (basefield)
	{
	case ios_base::oct:
		base = 8;
		break;
	case ios_base::dec:
		base = 10;
		break;
	case ios_base::hex:
		base = 16;
		if (!in._M_equal_inline(end) && *in == atoms[2])
		{
			++in;
			if (!in._M_equal_inline(end) && (*in == atoms[3] || *in == atoms[4]))
				++in;
			else
				validZero = 1;
		}
		break;
	default:
		if (!in._M_equal_inline(end) && *in == atoms[2])
		{
			++in;
			if (!in._M_equal_inline(end) && (*in == atoms[3] || *in == atoms[4]))
			{
				++in;
				base = 16;
			}
			else
			{
				base = 8;
				validZero = 1;
			}
		}
		else
			base = 10;
		break;
	}

	return (base << 2) | (static_cast<int>(negative) << 1) | validZero;
}

typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_iterator;

template int __cdecl _M_get_base_or_zero<wide_iterator, wchar_t>(
		wide_iterator &, wide_iterator &, ios_base &, wchar_t *);

}
