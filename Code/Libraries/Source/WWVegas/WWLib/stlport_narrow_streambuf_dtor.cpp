// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

// STLport 4.5.3 basic_streambuf<char> destructor. Fourteen bytes: restore the
// vtable, then tail-jump into the locale destructor for the member at +0x4C -
// which is where the retail body's `add ecx, 0x4c` puts it.

namespace _STL
{

template <class T>
class char_traits {};

class locale
{
public:
	~locale();
};

template <class T>
class fpos {};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	virtual ~basic_streambuf();

protected:
	// The rest of STLport's table, in its order, as the first copy in link order
	// (stlport_narrow_filebuf.cpp) declares it: this TU's copy then has all 14 slots.
	virtual basic_streambuf *setbuf(CharT *, int);
	virtual fpos<int> seekoff(long, int, int);
	virtual fpos<int> seekpos(fpos<int>, int);
	virtual int sync();
	virtual int showmanyc();
	virtual int xsgetn(CharT *, int);
	virtual int underflow();
	virtual int uflow();
	virtual int pbackfail(int);
	virtual int xsputn(const CharT *, int);
	virtual int _M_xsputnc(CharT, int);
	virtual int overflow(int);
	virtual void imbue(const locale &);

private:
	unsigned char _M_pad[0x4C - 4];
	locale _M_locale;
};

template <class CharT, class Traits>
basic_streambuf<CharT, Traits>::~basic_streambuf()
{
}

template class basic_streambuf<char, char_traits<char> >;

}
