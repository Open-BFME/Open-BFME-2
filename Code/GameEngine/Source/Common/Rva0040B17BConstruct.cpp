// cl: /Ob2 /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /ICode/Libraries/Source/debug
// stlport46
// Retail 0x0040B17B (45B): STLport _Construct<Rva0040AF66,Rva0040AF66>.
// Native vector overflow/push-back calls target this copy-construction body.
// Element stride 0x68 is proven by those callers; source identity follows
// their existing STLport specialization and the generic placement-new body.
// Evidence: calls rowed copy ctor 0x0040AF66; EH prolog with state 0; null check on dst; callers 0x0040B1DB 0x0040B206 stride 0x68; same 45B shape as rowed 0x0040B14E.
#include <vector>
#include <new>

#include "ascii_string.h"

enum ScienceType
{
	SCIENCE_NONE = 0
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	char m_pad[0x1C];
};

class Rva0040AF66
{
public:
	Rva0040AF66(const Rva0040AF66 &other);
	Rva0040AF66 &operator=(const Rva0040AF66 &other);
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

template void _STL::_Construct<Rva0040AF66, Rva0040AF66>(
	Rva0040AF66 *, const Rva0040AF66 &);
