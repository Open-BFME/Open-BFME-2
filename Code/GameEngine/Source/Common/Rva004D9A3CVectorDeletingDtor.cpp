// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common /Ireference/shims/bfmelist /Ireference/shims/moduledata
//
// ??_ERva004D9A3C@@QAEPAXI@Z 75B @0x00392011: vector deleting dtor for
// Rva004D9A3C (28-byte element with StringBase<char> at +0x14, dtor rowed
// at 0x004D9A3C via StringBaseTailDtors). Shape routes array branch through
// vector delete operator and scalar branch through scalar delete, both via
// rowed mem_ops. Evidence: push 0x1C plus dtor 0x004D9A3C plus ??_M at
// 0x00629110, flag bit2 vector plus bit0 delete, ret 4, caller 0x00392068
// in 0x0039205C which becomes ready on landing. Recipe follows landed
// Rva0073B700VectorDeletingDtor (empty dtor plus absent DeleteArray plus
// declared vector-delete); here ??1 is already rowed so declared only.

// Retail's array branch frees through the vector delete operator; MSVC only
// routes the call through ??_V when a vector-delete is declared in the TU
// (probe-proven in Rva0073B700VectorDeletingDtor: without this declaration
// cl emits ??3 in both branches). The declaration emits no code.
#include <new>


#include "ascii_string.h"

class Rva004D9A3C
{
public:
	Rva004D9A3C();
	~Rva004D9A3C();
public:
	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	unsigned char m_byte10;
	AsciiString m_name;										// +0x14
	int m_18;
};

// ?Rva004D9A3CDeleteArray@@YAXPAVRva004D9A3C@@@Z absent-from-retail
void Rva004D9A3CDeleteArray(Rva004D9A3C *array)
{
	delete[] array;
}
