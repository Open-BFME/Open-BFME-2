// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/shims/moduledata
// ??1EvacuateDamageModuleData@@UAE@XZ @ 0x004BAD91 48B
// Implicit virtual dtor restoring Snapshot base vtable 0x00BBB554 with no
// base call. Member evacuation-weapon string at +0x08 via 0x00036410.
// Layout from ctor TU 0x004BAD10 (module tag +4 string +0x08). Vtable
// 0x00859CF8 slot 0 is ??_G 0x004BAD75. The class derives from the canonical
// ModuleData, as its constructor unit (EvacuateDamage.cpp) declares it, so this
// unit's copy of the 31-slot vftable is the same table; ModuleData's empty
// destructor is inline here so the teardown keeps retail's inlined Snapshot
// restore (Rva004ABFD9Dtor.cpp precedent).
#include "ascii_string.h"
#include "../../../../Include/Common/ModuleData.h"
inline ModuleData::~ModuleData() {}
class EvacuateDamageModuleData : public ModuleData
{
public:
	EvacuateDamageModuleData(); // rowed in EvacuateDamage.cpp
	EvacuateDamageModuleData(struct EmitVtableTag *); // vtable anchor, no retail body
// Implicit virtual dtor (never declared, never defined)
private:
	AsciiString m_weapon;
};
// ?<EvacuateDamageModuleData::EvacuateDamageModuleData> absent-from-retail
EvacuateDamageModuleData::EvacuateDamageModuleData(EmitVtableTag *)
{
}
void deleteEvacuateDamageModuleData(EvacuateDamageModuleData *evacuateDamageModuleData)
{
	delete evacuateDamageModuleData;
}
