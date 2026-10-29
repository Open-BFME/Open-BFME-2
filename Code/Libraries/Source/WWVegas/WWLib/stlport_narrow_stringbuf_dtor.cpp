// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// STLport basic_stringbuf<char>::~basic_stringbuf, retail 0x001F6606 (65 B).
// The vendored 4.5.3 header defines this destructor out of line through
// _String_base::_M_deallocate_block, which the node allocator keeps a call;
// retail inlines it as `if (_M_start) free(_M_start)` against the game
// allocator and wraps it in an /O1 outlined-__EH_prolog frame, so the body is
// modelled by hand (cf. stlport_narrow_string_base_dtor.cpp):
//
//   * free declared with C++ linkage. As extern "C" it is nothrow, the call
//     needs no unwind region, and the frame collapses. With C++ linkage the
//     call throws, which buys the `and [ebp-4],0` state and the funclet.
//   * the string member as a bare pointer triple at +0x58, where the retail
//     load reads _M_start (the probe TU's `lea ecx,[esi+0x58]` for
//     _M_deallocate_block pins _M_str at +0x58; the base is 0x50).
//   * the streambuf base declared-only, so the trailing call stays a direct
//     E8 to the rowed 0x0001C6E0 destructor.

extern "C" void __cdecl free(void *block) throw(...);

namespace _STL
{

template <class T>
class char_traits {};

template <class State> class fpos;

template <class T>
class allocator {};

class locale
{
public:
	~locale();
};

// Preserve the complete STLport 4.5.3 virtual interface in both views.
// The retail destructor writes the same table used by the header-based units.
template <class CharT, class Traits>
class basic_streambuf
{
public:
	virtual ~basic_streambuf();

protected:
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

template <class CharT, class Traits, class Alloc>
class basic_stringbuf : public basic_streambuf<CharT, Traits>
{
public:
	virtual ~basic_stringbuf();

protected:
	virtual int underflow();
	virtual int uflow();
	virtual int pbackfail(int);
	virtual int overflow(int);
	virtual int xsputn(const CharT *, int);
	virtual int _M_xsputnc(CharT, int);
	virtual basic_streambuf<CharT, Traits> *setbuf(CharT *, int);
	virtual fpos<int> seekoff(long, int, int);
	virtual fpos<int> seekpos(fpos<int>, int);

private:
	int _M_mode;
	int _M_reserved;
	CharT *_M_start;
	CharT *_M_finish;
	CharT *_M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
basic_stringbuf<CharT, Traits, Alloc>::~basic_stringbuf()
{
	if (_M_start != 0)
		free(_M_start);
}

template class basic_stringbuf<char, char_traits<char>, allocator<char> >;

}
