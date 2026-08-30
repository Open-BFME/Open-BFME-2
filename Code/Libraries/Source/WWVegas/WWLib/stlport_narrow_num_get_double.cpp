// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow basic_string destructor emitted by the num_get<double>
// instantiation. The retail unwind map for 0x0000FCC0 selects the copy at
// 0x00142D70.
// /EHc must remain disabled so VC7.1 retains the retail unwind-state update
// around the C-linkage free call.

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

template basic_string<char, char_traits<char>, allocator<char> >::~basic_string();

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
	bool equal(const istreambuf_iterator &) const;

private:
	void *_M_buf;
	CharT _M_c;
	unsigned char _M_eof;
	unsigned char _M_have_c;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;
typedef istreambuf_iterator<char, char_traits<char> > narrow_iterator;

template <class InputIter, class CharT>
bool __cdecl _M_read_float(
		narrow_string &, InputIter &, InputIter &, ios_base &, CharT *);

void __cdecl __string_to_float(const narrow_string &, double &);
void __cdecl __string_to_float(const narrow_string &, float &);

template <class CharT, class InputIter>
class num_get
{
protected:
	virtual InputIter do_get(
			InputIter, InputIter, ios_base &, ios_base::iostate &, float &) const;
	virtual InputIter do_get(
			InputIter, InputIter, ios_base &, ios_base::iostate &, double &) const;
};

template <>
narrow_iterator num_get<char, narrow_iterator>::do_get(
		narrow_iterator in, narrow_iterator end, ios_base &stream,
		ios_base::iostate &error, double &value) const
{
	narrow_string buffer;
	bool ok = _M_read_float(buffer, in, end, stream, (char *)0);
	__string_to_float(buffer, value);
	error = static_cast<ios_base::iostate>(
			ok ? ios_base::goodbit : ios_base::failbit);
	if (in.equal(end))
		error |= ios_base::eofbit;
	return in;
}

template <>
narrow_iterator num_get<char, narrow_iterator>::do_get(
		narrow_iterator in, narrow_iterator end, ios_base &stream,
		ios_base::iostate &error, float &value) const
{
	narrow_string buffer;
	bool ok = _M_read_float(buffer, in, end, stream, (char *)0);
	__string_to_float(buffer, value);
	error = static_cast<ios_base::iostate>(
			ok ? ios_base::goodbit : ios_base::failbit);
	if (in.equal(end))
		error |= ios_base::eofbit;
	return in;
}

}
