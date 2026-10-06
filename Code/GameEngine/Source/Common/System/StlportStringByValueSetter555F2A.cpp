// cl: /EHs /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?set@Rva00555F2ASetter@@QAEXV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z @0x00555F2A 62B
// By-value narrow-string setter matching siblings 0x00555EB4/0x00555EEF:
// assigns the parameter into the member at +0x84 through the rowed assign
// body 0x120C0; the by-value parameter gives ret 0xc and the EH state guards
// its destruction. Caller 0x005580FB.

extern "C" void __cdecl free(void *block);

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
	basic_string(const basic_string<CharT, Traits, Alloc> &that);
	~basic_string() { if (_M_start != 0) free(_M_start); }
	basic_string<CharT, Traits, Alloc> &assign(
		const basic_string<CharT, Traits, Alloc> &that);

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > StlportNarrowString;

class Rva00555F2ASetter
{
public:
	void set(StlportNarrowString value);

private:
	char m_pad[0x84];
	StlportNarrowString m_value; // +0x84
};

void Rva00555F2ASetter::set(StlportNarrowString value)
{
	m_value.assign(value);
}
