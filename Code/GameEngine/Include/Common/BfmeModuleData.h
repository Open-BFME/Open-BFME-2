#pragma once

// BFME2 ModuleData: the 31-slot virtual table every ModuleData vftable in
// game.dat starts with (tools/vftable_map.py over 0x00C49950, 0x00C4AD40,
// 0x00C5BC48, 0x00C594E0 and their siblings). Slot 0 is the class's own
// scalar deleting destructor; slots 1-30 are the shared base bodies below,
// which every derived ModuleData inherits unchanged:
//
//   1        ret                          0x000B3FD0
//   2        return "ModuleData"          0x00065212
//   3        void (Xfer *) {}             0x0047A69C  (ret 4)
//   4-13,15  return false                 0x0047A699
//   14       return TheEmptyString (int)  0x000B69A1
//   16-29    return NULL                  0x000D43D0
//   30       return true                  0x0050B5C6
//
// Target evidence fixes each slot's position, arity and body; their source
// names are not recovered (BFME1's ModuleData declares only seven of them),
// so the slots carry their position. Declaring them inline lets a unit that
// constructs a ModuleData emit its vtable by name with the compiler's own
// slot pointers, instead of a hand-built table bound to unrelated folded
// names. Slot 21 is HordeContain's getter override point
// (HordeContainIface11CSlots.cpp reads it); the rest are unpinned.
//
// Include with /Ireference/shims/bfme2_ascii first among the unit's /I flags.
//
// novtable: retail never installs ModuleData's own table (each derived ctor
// stores only its derived vtable), so no unit should emit ??_7ModuleData or
// ??_GModuleData; the sweep shim's Common/Module.h view is novtable likewise,
// leaving ??0ModuleData identical (mov eax,ecx; ret) in both.

#include "ascii_string.h"

class Xfer;

class __declspec(novtable) ModuleData
{
public:
	ModuleData() {}
	virtual ~ModuleData();

	virtual void slot01() {}
	virtual const char *slot02() const { return "ModuleData"; }
	virtual void slot03(Xfer *) {}
	virtual bool slot04() const { return false; }
	virtual bool slot05() const { return false; }
	virtual bool slot06() const { return false; }
	virtual bool slot07() const { return false; }
	virtual bool slot08() const { return false; }
	virtual bool slot09() const { return false; }
	virtual bool slot10() const { return false; }
	virtual bool slot11() const { return false; }
	virtual bool slot12() const { return false; }
	virtual bool slot13() const { return false; }
	virtual AsciiString slot14(int) const { return AsciiString::TheEmptyString; }
	virtual bool slot15() const { return false; }
	virtual const void *slot16() const { return 0; }
	virtual const void *slot17() const { return 0; }
	virtual const void *slot18() const { return 0; }
	virtual const void *slot19() const { return 0; }
	virtual const void *slot20() const { return 0; }
	virtual const void *slot21() const { return 0; }
	virtual const void *slot22() const { return 0; }
	virtual const void *slot23() const { return 0; }
	virtual const void *slot24() const { return 0; }
	virtual const void *slot25() const { return 0; }
	virtual const void *slot26() const { return 0; }
	virtual const void *slot27() const { return 0; }
	virtual const void *slot28() const { return 0; }
	virtual const void *slot29() const { return 0; }
	virtual bool slot30() const { return true; }
};
