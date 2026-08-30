// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport



namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	void push_back(CharT);
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

template <class InputIter, class CharT>
InputIter __cdecl __copy_sign(
		InputIter in, InputIter end, narrow_string &buffer,
		CharT plus, CharT minus)
{
	if (!in.equal(end))
	{
		CharT character = *in;
		if (character == plus)
			++in;
		else if (character == minus)
		{
			buffer.push_back('-');
			++in;
		}
	}
	return in;
}

typedef istreambuf_iterator<char, char_traits<char> > narrow_iterator;

template narrow_iterator __copy_sign<narrow_iterator, char>(
		narrow_iterator, narrow_iterator, narrow_string &, char, char);

}
