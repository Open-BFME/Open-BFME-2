// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport46
// ??1Rva004F69C3@@QAE@XZ, retail 0x004F69C3, 19 bytes.
// Holder dtor releasing TargetRef at +0xAC of pointee at +4 via rowed
// fastcall 0x0007DEEF. Same shape as Rva002B2F97 holder with int pad at +0.
// Evidence: tail-jmp to Release; callers at 0x0040D05E 0x0040DC49 0x0040DCFA
// 0x0040DF22 0x0040EDE8 plus tail-jmp callers incl Unwind funclets.

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

#include <vector>

struct Rva004F69C3Target
{
	char m_pad[0xAC];
	TargetRef00217D4C m_ac;
};

struct Rva004F69C3
{
	int m_00;
	Rva004F69C3Target *m_04;
	~Rva004F69C3();
};

// Select-any like the identical LivingWorldAutoResolveBattle.cpp copy (first in
// link order); the identical bodies fold instead of duplicating at link time.
// Referenced by the forwarder below, so the body stays emitted.
inline Rva004F69C3::~Rva004F69C3()
{
	if (m_04)
		ReleaseTreeHintRef00217D4C(&m_04->m_ac);
}

// ?pop_back@?$vector@URva004F69C3@@V?$allocator@URva004F69C3@@@_STL@@@_STL@@QAEXXZ
// @0x0040D8AC 12B: STLport pop_back of the 8-byte holder vector (--_M_finish,
// then the inline single-object _Destroy tail-jumps the dtor above). Instantiated
// here so the dtor stays referenced.
template void _STL::vector<Rva004F69C3>::pop_back();
