// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/shims/moduledata
// ??1EvacuateDamageModuleData@@UAE@XZ @ 0x004BAD91 48B
// Implicit virtual dtor restoring Snapshot base vtable 0x00BBB554 with no
// base call. Member evacuation-weapon string at +0x08 via 0x00036410.
// Layout from ctor TU 0x004BAD10 (pad +4 string +0x08). Vtable 0x00859CF8
// slot 0 is ??_G 0x004BAD75. ShareExperienceBehaviorModuleDataDtor precedent.
#include "ascii_string.h"
#include "Common/Snapshot.h"
class EvacuateDamageModuleData : public Snapshot
{
public:
	EvacuateDamageModuleData(); // rowed in EvacuateDamageModuleDataCtor.cpp
	EvacuateDamageModuleData(struct EmitVtableTag *); // vtable anchor, no retail body
// Implicit virtual dtor (never declared, never defined)
private:
	unsigned char m_unk04[4];
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
