// cl: /Oy- /DNDEBUG /MD /GX
//
// ?get@Rva00555A8BNarrowField@@QBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ @0x00555A8B 27B
// Value-returning STLport-string getter matching sibling 0x00555AC1 (30B):
// returns narrow-string member at +0x6c via hidden return pointer through
// rowed narrow copy ctor 0x9170; caller 0x00557E5D same family.

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

template <class CharT, class Alloc>
class _String_base
{
public:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	basic_string(const basic_string<CharT, Traits, Alloc> &that);
	~basic_string();
};

}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > StlportNarrowString;

class Rva00555A8BNarrowField
{
public:
	StlportNarrowString get() const;

private:
	char m_pad[0x6c];
	StlportNarrowString m_value; // +0x6c
};

StlportNarrowString Rva00555A8BNarrowField::get() const
{
	return m_value;
}
