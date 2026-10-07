// cl: /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /O2 /Ob2 /arch:SSE /G7
// Provenance: Open-BFME-1 game/Libraries/Source/WWVegas/WW3D2/Rva00910F10DeviceSlot79.cpp at 6583b3c1ff; include paths repointed at the
// reference checkout and built the BFME2 way (/arch:SSE /G7), where its body places
// exactly once in game.dat by masked byte search.
// Compiler-generated vector construction uses one shared retail helper.
// Give its first emission the verified /O1 frame and loop shape at RVA 0x1423;
// the unemitted anchor needs no implementation, and the unit flags resume below.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

#include "dx8wrapper.h"


struct Rva00910F10Device;
struct Rva00910F10Vtable
{
	void *m_prior[79];
	long (__stdcall *m_slot79)(Rva00910F10Device *, unsigned);
};
struct Rva00910F10Device
{
	Rva00910F10Vtable *m_vtable;
};
extern unsigned int number_of_DX8_calls;

void rva00910F10DeviceSlot79(unsigned value)
{
	reinterpret_cast<Rva00910F10Device *>(DX8Wrapper::_Get_D3D_Device8())->m_vtable->m_slot79(reinterpret_cast<Rva00910F10Device *>(DX8Wrapper::_Get_D3D_Device8()), value);
	++number_of_DX8_calls;
}
