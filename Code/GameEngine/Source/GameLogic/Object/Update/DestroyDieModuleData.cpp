// PC identity update: the registered DestroyDie data factory 0x254E7D calls
// this constructor. Derived callers share this data base at offset zero.
// cl: /GX /MD /DNDEBUG /Ireference/shims/moduledata
//
// ??0DestroyDieModuleData@@QAE@XZ at retail 0x00253510 (50B). Opaque intermediate
// base ctor (EH leaf: explicit vtable 0x00C4ED70 plus DieMuxData member at
// +8 through the rowed init at 0x004CE534); called this-direct with no
// adjustment by 12 derived ctors (0x2538EC/0x2539C5/0x253A7B/0x253B7B/
// 0x254E9E/0x2550F0/0x257301/0x45D17D/0x485D9B/0x485F45/0x486722/
// 0x4C2311), so it serves as their +0 base; opaque derived 0x253B78
// included. The 0x00C4ED70 vtable is the shared trivial fold (also
// installed by DeletionUpdate/SlotToLock/ReflectDamage), so the install
// proves linkage, not class. Pin-to-row upgrade; identity still unproven.

// Native constructor unwind action 0x00771C42 cleans this+0 through
// Snapshot::~Snapshot (0x0049B47C), rather than destroying DieMuxData.
#include "Common/Snapshot.h"

extern "C" const void *const __identifier("??_7ObjectHelperModuleData@@6B@")[];  // folded nine-class vftable 0x00C4ED70, by its data-ledger name

class DieMuxData
{
public:
	DieMuxData *init();

private:
	unsigned char m_bytes[0x30];
};

class __declspec(novtable) DestroyDieModuleData : public Snapshot
{
public:
	DestroyDieModuleData();

private:
	unsigned int m_unused04; // +4
	DieMuxData m_dieMux; // +8
};

// ??0DestroyDieModuleData@@QAE@XZ @0x253510
DestroyDieModuleData::DestroyDieModuleData()
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7ObjectHelperModuleData@@6B@"));
	m_dieMux.init();
}
