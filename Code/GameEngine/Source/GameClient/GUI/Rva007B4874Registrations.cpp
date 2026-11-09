// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// Two startup initializers of named registrations (the counted-note family
// of Rva0052B668, whose rowed constructor 0x0052B894 registers
// the name and writes the base vptr): each builds the label, constructs the
// global over it, installs the derived vtable and registers the rowed atexit
// thunk that runs the shared destructor 0x005C47A3.
//  - ?registerStrengthenArmy@@YAXXZ retail 0x007B4874 (87 bytes): "StrengthenArmy" at
//    0x00E065B8, vtable 0x00C74698, thunk 0x007B96F8.
//  - ?registerUpgradeTroops@@YAXXZ retail 0x007B48CB (87 bytes): "UpgradeTroops" at
//    0x00E065BC, vtable 0x00C7475C, thunk 0x007B9702.
// Two more of the same family, never attempted before (their starts are
// EH-prolog starts that Ghidra did not list): ?registerSpawnArmy@@YAXXZ retail
// 0x007B33C5 (87 bytes): "SpawnArmy" at 0x00E04500, vtable 0x00C63398, thunk
// 0x007B9035; ?registerIncreaseCommandPoints@@YAXXZ retail 0x007B481D (87 bytes):
// "IncreaseCommandPoints" at 0x00E065B4, vtable 0x00C745A0, thunk 0x007B96EE.
// The application classes are unknown; names are address-derived.

#include "ascii_string.h"
#include <stdlib.h>

class Rva0052B668
{
public:
	Rva0052B668(const AsciiString &name);
	const void *const *m_vtable;
};

extern unsigned int g_Va00E04500;
extern unsigned int g_Va00E065B4;
extern unsigned int g_Va00E065B8;
extern unsigned int g_Va00E065BC;
// Each registration has two slots: its shared deleting destructor and its
// factory. The following independently installed object vtables begin at
// C633A0, C745A8, C746A0 and C74764, bounding these tables at eight bytes.
// The declarations retain the existing code owners rather than inventing
// another class identity for the registration or its factory.
extern "C" {
void __identifier("??_GRva005C47A3@@UAEPAXI@Z")();
void __identifier("?Rva004FAC99Create@@YGPAVRva004FAC21@@ABV?$StringBase@D@@@Z")();
void __identifier("?rva0052B58F@@YGPAXPBX@Z")();
void __identifier("?rva0052B5C6@@YGPAXPBX@Z")();
void __identifier("?rva0052B5FD@Rva0052B5FD@@QAEPAVRva005C4A91@@ABVAsciiString@@@Z")();
}
extern const void *const spawnArmyVtable[2] = {
	(const void *)&__identifier("??_GRva005C47A3@@UAEPAXI@Z"),
	(const void *)&__identifier("?Rva004FAC99Create@@YGPAVRva004FAC21@@ABV?$StringBase@D@@@Z")
};
extern const void *const increaseCommandPointsVtable[2] = {
	(const void *)&__identifier("??_GRva005C47A3@@UAEPAXI@Z"),
	(const void *)&__identifier("?rva0052B58F@@YGPAXPBX@Z")
};
extern const void *const strengthenArmyVtable[2] = {
	(const void *)&__identifier("??_GRva005C47A3@@UAEPAXI@Z"),
	(const void *)&__identifier("?rva0052B5C6@@YGPAXPBX@Z")
};
extern const void *const upgradeTroopsVtable[2] = {
	(const void *)&__identifier("??_GRva005C47A3@@UAEPAXI@Z"),
	(const void *)&__identifier("?rva0052B5FD@Rva0052B5FD@@QAEPAVRva005C4A91@@ABVAsciiString@@@Z")
};
void rva007B9035();
void rva007B96EE();
void rva007B96F8();
void rva007B9702();

void registerStrengthenArmy()
{
	{
		AsciiString label("StrengthenArmy");
		Rva0052B668 &registration = *(Rva0052B668 *)&g_Va00E065B8;
		registration.Rva0052B668::Rva0052B668(label);
		registration.m_vtable = strengthenArmyVtable;
	}
	atexit(rva007B96F8);
}

void registerUpgradeTroops()
{
	{
		AsciiString label("UpgradeTroops");
		Rva0052B668 &registration = *(Rva0052B668 *)&g_Va00E065BC;
		registration.Rva0052B668::Rva0052B668(label);
		registration.m_vtable = upgradeTroopsVtable;
	}
	atexit(rva007B9702);
}

void registerSpawnArmy()
{
	{
		AsciiString label("SpawnArmy");
		Rva0052B668 &registration = *(Rva0052B668 *)&g_Va00E04500;
		registration.Rva0052B668::Rva0052B668(label);
		registration.m_vtable = spawnArmyVtable;
	}
	atexit(rva007B9035);
}

void registerIncreaseCommandPoints()
{
	{
		AsciiString label("IncreaseCommandPoints");
		Rva0052B668 &registration = *(Rva0052B668 *)&g_Va00E065B4;
		registration.Rva0052B668::Rva0052B668(label);
		registration.m_vtable = increaseCommandPointsVtable;
	}
	atexit(rva007B96EE);
}
