// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva003F610FElement@@QAE@H@Z @0x003F55D6 113B: int ctor (int plus two vectors plus tail20 with reserve 4)
// Evidence: same 48-byte layout as default ctor 0x003F5322 copy ctor 0x003F54DC dtor 0x003F535B; Vector_base 0x00211E58 twice then reserve 0x002B712E and 0x003F5192; m_00 and m_1C[0] store the int arg.
#include <vector>

class ModuleData;

#include "../../../Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

struct BfmeAssignRecord104
{
	int a[26];
};

// Retail's reserve is the rowed copy in stlport_asciistring_record_bodies.cpp.
namespace _STL { template <> void vector<BfmeAssignRecord104, allocator<BfmeAssignRecord104> >::reserve(size_t); }

struct Rva003F610FElement
{
	int m_00;
	_STL::vector<BfmeE16> m_04;
	_STL::vector<BfmeE16> m_10;
	int m_1C[5];
	Rva003F610FElement(int a);
};

Rva003F610FElement::Rva003F610FElement(int a)
	: m_00(a)
	, m_04(_STL::allocator<BfmeE16>())
	, m_10(_STL::allocator<BfmeE16>())
{
	m_1C[0] = a;
	m_1C[1] = 0;
	m_1C[2] = 0;
	m_1C[3] = 0;
	m_1C[4] = 0;
	((_STL::vector<const ModuleData *> *)&m_04)->reserve(4);
	((_STL::vector<BfmeAssignRecord104> *)&m_10)->reserve(4);
}
