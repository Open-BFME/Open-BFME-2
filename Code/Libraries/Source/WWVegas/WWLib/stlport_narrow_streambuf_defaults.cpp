// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Two of the narrow basic_streambuf base defaults, written out rather than
// instantiated. basic_streambuf<char> is an explicit specialisation in the
// vendored headers, so `template class` on it is C2950 and no user TU emits
// its members - the wide facet has no such problem, which is why
// stlport_wide_streambuf.cpp covers the wide side of this vtable.
//
// Both bodies are the upstream defaults from vendor/stlport/stl/_streambuf.h:
// underflow and pbackfail each return eof, which for char_traits<char> is the
// int -1, so each is an or eax, -1 and a return. The narrow streambuf vtable
// holds 0x0001CA70 in both slot 9 and slot 12, so overflow folded onto
// pbackfail; it is rowed below as that body's ICF twin.

namespace _STL
{

template <class T>
class char_traits
{
public:
	typedef int int_type;

	static int_type eof() { return -1; }
};

class locale;

// STLport 4.5.3 fpos<mbstate_t>: an offset and a conversion state. Its
// constructor makes it non-POD, so it comes back through a hidden pointer.
template <class StateT>
class fpos
{
public:
	fpos(long pos) : _M_pos(pos), _M_st(StateT()) {}

private:
	long _M_pos;
	StateT _M_st;
};

template <class CharT, class Traits>
class basic_streambuf;

template <>
class basic_streambuf<char, char_traits<char> >
{
public:
	typedef char_traits<char>::int_type int_type;

	// Declaration-only: the retail dtor/deleting-dtor live in
	// stlport_narrow_streambuf_dtor.cpp (0x0001C6E0) and the vtable has no
	// retail address. Defining ~basic_streambuf inline here plus a
	// whole-class explicit instantiation emitted our own wrong COMDAT copies
	// of ??1, ??_G and ??_7, which blocked this file from linking.
	virtual ~basic_streambuf();

protected:
	virtual int_type underflow();
	virtual int_type pbackfail(int_type c);

	// The other trivial upstream defaults, each folded in retail with the
	// wide instantiation's identical body: imbue (0x00180FD0, ret 4),
	// showmanyc and sync (0x0065CE90, return 0), setbuf (0x00013570, return
	// this) and overflow (0x0001CA70, return eof, with pbackfail).
	virtual void imbue(const locale &);
	virtual int showmanyc();
	virtual int sync();
	virtual basic_streambuf *setbuf(char *, int);
	virtual int_type overflow(int_type c);

	// seekoff and seekpos: both return pos_type(-1), an fpos written through
	// the hidden return pointer with four argument words to pop either way,
	// so retail folded both onto the wide seekoff body at 0x0001C970.
	virtual fpos<int> seekoff(long, int, int);
	virtual fpos<int> seekpos(fpos<int>, int);
};

int basic_streambuf<char, char_traits<char> >::underflow() { return char_traits<char>::eof(); }
int basic_streambuf<char, char_traits<char> >::pbackfail(int_type c) { return char_traits<char>::eof(); }
void basic_streambuf<char, char_traits<char> >::imbue(const locale &) {}
int basic_streambuf<char, char_traits<char> >::showmanyc() { return 0; }
int basic_streambuf<char, char_traits<char> >::sync() { return 0; }
basic_streambuf<char, char_traits<char> > *basic_streambuf<char, char_traits<char> >::setbuf(char *, int) { return this; }
int basic_streambuf<char, char_traits<char> >::overflow(int_type c) { return char_traits<char>::eof(); }
fpos<int> basic_streambuf<char, char_traits<char> >::seekoff(long, int, int) { return fpos<int>(-1); }
fpos<int> basic_streambuf<char, char_traits<char> >::seekpos(fpos<int>, int) { return fpos<int>(-1); }

}
