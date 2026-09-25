// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
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

void __cdecl free(void *);

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

class locale
{
public:
	~locale();
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	virtual ~basic_streambuf();

private:
	unsigned char _M_pad[0x4C - 4];
	locale _M_locale;
};

template <class CharT, class Traits, class Alloc>
class basic_stringbuf : public basic_streambuf<CharT, Traits>
{
public:
	virtual ~basic_stringbuf();

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
