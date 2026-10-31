// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Rva0040AF66 copy ctor, retail 0x0040AF66 141 bytes. Copy ctor with int
// plus two vector<ScienceType> plus two FixedStorage plus two StringBase plus
// ints and byte. Evidence: caller 0x0040B197, rowed vector 0x0054878E, rowed
// FixedStorage 0x0004543D, pin StringBase 0x000365F0, unblocks 0x0040B17B.
// The strings are AsciiString members with an inline copy ctor: retail forms
// the +0x54 member address before pushing the source, which a direct
// StringBase copy-ctor call orders the other way (the banked 0.98 attempt).
// The FixedStorage copy ctor is the rowed class-key spelling (ABV0).

#include <vector>

class AsciiString;

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

enum ScienceType
{
	SCIENCE_NONE = 0
};

// The unwind actions call the ScienceType vector destructor out of line, as
// AwardSystemManager.cpp declares it; the kept copy serves the link.
namespace _STL { template <> _Vector_base<ScienceType,_STL::allocator<ScienceType> >::~_Vector_base(); }
namespace _STL { template <> vector<ScienceType,_STL::allocator<ScienceType> >::~vector(); }


namespace _STL
{
// Suppress the duplicate vector<ScienceType> copy COMDAT; retail's copy is
// rowed at 0x0054878E in ProductionPrerequisiteCopyCtor.cpp. The row below
// keeps calling it (member-inits), so its bytes are unchanged.
template <> vector<ScienceType, allocator<ScienceType> >::vector(const vector<ScienceType, allocator<ScienceType> > &);
}

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	char m_pad[0x1C];
};

// The 0x68-byte award statistic: the copy constructor 0x0040AF66 builds
// every member; the lookup 0x0040AAF8 reads the name key in the first word.
class Rva0040AF66
{
public:
	Rva0040AF66(const Rva0040AF66 &other);
	int m_00;
private:
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_04;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_10;
	BfmeFixedStorage0004543D m_1C;
	BfmeFixedStorage0004543D m_38;
	AsciiString m_54;
	AsciiString m_58;
	int m_5C;
	int m_60;
	unsigned char m_64;
};

Rva0040AF66::Rva0040AF66(const Rva0040AF66 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_10(other.m_10)
	, m_1C(other.m_1C)
	, m_38(other.m_38)
	, m_54(other.m_54)
	, m_58(other.m_58)
	, m_5C(0)
	, m_60(0)
	, m_64(other.m_64)
{
}
