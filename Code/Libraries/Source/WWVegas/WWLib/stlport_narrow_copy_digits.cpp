// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport


namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class T>
__declspec(dllimport) __forceinline const T &max(const T &left, const T &right)
{
	return left < right ? right : left;
}

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

	void reserve(size_type);
	__declspec(dllimport) __forceinline size_type size() const
	{
		return static_cast<size_type>(_M_finish - _M_start);
	}
	__declspec(dllimport) __forceinline void push_back(CharT character)
	{
		if (_M_finish + 1 == _M_end_of_storage._M_data)
			reserve(size() + (max)(size(), static_cast<size_type>(1)));
		*(_M_finish + 1) = 0;
		*_M_finish = character;
		++_M_finish;
	}

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

template <class CharT, class Traits>
class basic_streambuf
{
public:
	int sbumpc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	bool equal(const istreambuf_iterator &) const;
	__declspec(dllimport) __forceinline CharT operator*() const
	{
		_M_getc();
		return _M_c;
	}
	__declspec(dllimport) __forceinline istreambuf_iterator &operator++()
	{
		_M_buf->sbumpc();
		_M_have_c = false;
		return *this;
	}

private:
	void _M_getc() const;

	basic_streambuf<CharT, Traits> *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

__declspec(dllimport) __forceinline bool __get_fdigit(char &character, const char *)
{
	return character >= '0' && character <= '9';
}

template <class InputIter, class CharT>
bool __cdecl __copy_digits(
		InputIter &in, InputIter &end,
		narrow_string &buffer, const CharT *digits)
{
	bool ok = false;

	for (; !in.equal(end); ++in)
	{
		CharT character = *in;
		if (__get_fdigit(character, digits))
		{
			buffer.push_back(static_cast<char>(character));
			ok = true;
		}
		else
			break;
	}
	return ok;
}

typedef istreambuf_iterator<char, char_traits<char> > narrow_iterator;

template bool __copy_digits<narrow_iterator, char>(
		narrow_iterator &, narrow_iterator &, narrow_string &, const char *);

}
