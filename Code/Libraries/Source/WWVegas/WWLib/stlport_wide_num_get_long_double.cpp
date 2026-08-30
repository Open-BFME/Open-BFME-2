// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide istreambuf_iterator numeric input specialization. Numeric
// text is accumulated in a narrow string before the long-double conversion.

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
	basic_string();
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
	typedef int iostate;

	enum
	{
		goodbit = 0,
		eofbit = 2,
		failbit = 4
	};
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	__declspec(dllimport) __forceinline bool equal(
			const istreambuf_iterator &other) const
	{
		if (_M_buf != 0)
			_M_getc();
		if (other._M_buf != 0)
			other._M_getc();
		return _M_eof == other._M_eof;
	}

private:
	void _M_getc() const;

	void *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_iterator;

template <class InputIter, class CharT>
bool __cdecl _M_read_float(
		narrow_string &, InputIter &, InputIter &, ios_base &, CharT *);

void __cdecl __string_to_float(const narrow_string &, long double &);

template <class CharT, class InputIter>
class num_get
{
protected:
	virtual InputIter do_get(
			InputIter, InputIter, ios_base &, ios_base::iostate &,
			long double &) const;
};

template <>
wide_iterator num_get<wchar_t, wide_iterator>::do_get(
		wide_iterator in, wide_iterator end, ios_base &stream,
		ios_base::iostate &error, long double &value) const
{
	narrow_string buffer;
	bool ok = _M_read_float(buffer, in, end, stream, (wchar_t *)0);
	__string_to_float(buffer, value);
	error = static_cast<ios_base::iostate>(
			ok ? ios_base::goodbit : ios_base::failbit);
	if (in.equal(end))
		error |= ios_base::eofbit;
	return in;
}

}
