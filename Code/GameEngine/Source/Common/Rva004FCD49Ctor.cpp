// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva004FCD49@@QAE@XZ, retail 0x004FCD29, 32 bytes.
// Ctor for the Rva004FCD49 class whose dtor is rowed at 0x004FCD49 (same vtable
// 0x0086355C, same TU FreeMemberDeleters.cpp): installs vtable, constructs
// vector<BfmeE16> at +4 via rowed Vector_base 0x00211E58 (allocator temp on
// esp+7, frameless), zeroes int at +0x10 via and-mem-0 under /O1. Gap between
// ??1Rva004FCD14 and ??1Rva004FCD49; caller 0x004FD79C unclaimed. Shape follows
// Rva00330757Member (vector plus int via same Vector_base).

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva004FCD49
{
public:
	Rva004FCD49();
	virtual ~Rva004FCD49();

private:
	_STL::vector<BfmeE16> m_vec; // +4
	int m_int10; // +0x10
};

Rva004FCD49::Rva004FCD49()
	: m_vec(_STL::allocator<BfmeE16>())
{
	m_int10 = 0;
}
