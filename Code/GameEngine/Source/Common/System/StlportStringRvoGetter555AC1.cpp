// cl: /Oy- /DNDEBUG /MD /GX
//
// Value-returning STLport-string getter with the RVO idiom proven by
// StlportStringRvoGetters.cpp (retail 0x00389E2D etc., 30 bytes):
// returns the narrow-string member at +0x84 via the hidden return
// pointer; the member copy-constructs directly into it (RVO) through
// the matched narrow copy body at 0x9170, and the function returns the
// hidden pointer. The copy constructor is declared only so the call
// resolves to the ledger row (split-TU rule: caller here, body in
// stlport_narrow_string_copy_ctor.cpp). Dedicated TU (not the shared
// family TU) to avoid edit races in the shared checkout. Class name is
// address-derived (identity unrecoverable from 30 bytes).

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

class Rva00555AC1NarrowField
{
public:
	StlportNarrowString get() const;

private:
	char m_pad[0x84];
	StlportNarrowString m_value; // +0x84
};

// ?get@Rva00555AC1NarrowField@@QBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ
StlportNarrowString Rva00555AC1NarrowField::get() const
{
	return m_value;
}
