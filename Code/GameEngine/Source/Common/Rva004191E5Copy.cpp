// cl: /Ireference/shims/bfme2_ascii /EHs /MD
//
// ??0Rva004191E5@@QAE@ABU0@@Z @0x004191E5 73B: copy constructor of a record
// holding an AsciiString at +0, a 12-byte member copied by the unrowed copy
// constructor 0x00419035 (+4; address-derived pin; no destructor unwind state
// in retail) and a BfmeFixedStorage002CF0F0 at +0x10 (rowed copy 0x002CF0F0).
// Callers 0x00419254 and 0x0041928E; record identity not recovered.

#include "ascii_string.h"

// The +4 member is the rowed STLport set tree; its copy constructor is
// ??0?$_Rb_tree@URva00419035Element@@... @0x00419035 (StlSweepW4Rva00419035.cpp).
struct Rva00419035Element;
namespace _STL
{
template <class _Tp> struct _Identity;
template <class _Tp> struct less;
template <class _Tp> class allocator;
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree
{
public:
	_Rb_tree(const _Rb_tree &other);

private:
	char m_pad[0xC];
};
}
typedef _STL::_Rb_tree<Rva00419035Element, Rva00419035Element, _STL::_Identity<Rva00419035Element>, _STL::less<Rva00419035Element>, _STL::allocator<Rva00419035Element> > Rva00419035;

#include "../../Include/Common/BfmeFixedStorage002CF0F0.h"

struct Rva004191E5
{
	Rva004191E5(const Rva004191E5 &other);

	AsciiString m_00;
	Rva00419035 m_04;
	BfmeFixedStorage002CF0F0 m_10;
};

Rva004191E5::Rva004191E5(const Rva004191E5 &other) :
	m_00(other.m_00),
	m_04(other.m_04),
	m_10(other.m_10)
{
}
