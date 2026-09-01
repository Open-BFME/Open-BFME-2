// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

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

template <class CharT, class Traits>
class basic_streambuf
{
public:
	virtual ~basic_streambuf();

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
