// cl: /DNDEBUG /MD
//
// ??0AttachedModelFXNugget@@QAE@XZ 46B @0x1E084A: no-arg ctor called by
// AttachedModelFXNugget::parse (0x001E168D) for the AttachedModel FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDD118 (Modelname@0x148, RandomlyRotate@0x14C,
// ExpireTimer@0x150); parse TU notes news 0x154 and builder 0x001DFBE8.
// Base 0x001DFEAA is a shared FXNugget-family base ctor (16 ctor-start
// callers with this undisplaced); pinned opaquely, do not name.

// Retail VA 0x00BDD814 (.rdata): a 5-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")();
extern "C" void __identifier("?doFXObj@AttachedModelFXNugget@@UBEXPBVObject@@0@Z")();
extern "C" void __identifier("??_GCursorParticleSystemFXNugget@@UAEPAXI@Z")();
extern "C" void __identifier("?rva001E1709@AttachedModelFXNugget@@UBEXAAVAssetList@@H@Z")();
extern "C" void __identifier("?rva001F01E8@Rva001F01E8@@QAEXHHHH@Z")();
extern "C" const void *const vtbl_00BDD814[] = {
	(const void *)&__identifier("??_GCursorParticleSystemFXNugget@@UAEPAXI@Z"),
	(const void *)&__identifier("?rva001F01E8@Rva001F01E8@@QAEXHHHH@Z"),
	(const void *)&__identifier("?doFXObj@AttachedModelFXNugget@@UBEXPBVObject@@0@Z"),
	(const void *)&__identifier("?rva001E1709@AttachedModelFXNugget@@UBEXAAVAssetList@@H@Z"),
	(const void *)&__identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")
};

extern int BfmeLogicFramesPerSecond;

#define LogicFramesPerSecond BfmeLogicFramesPerSecond

#include "../../Include/GameClient/Rva001DFEAABase.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AttachedModelFXNugget : public Rva001DFEAABase
{
public:
	AttachedModelFXNugget();
private:
	const char *m_modelName; // +0x148
	bool m_randomlyRotate; // +0x14C
	int m_expireTimer; // +0x150, default LogicFramesPerSecond * 8
};

// ??0AttachedModelFXNugget@@QAE@XZ
AttachedModelFXNugget::AttachedModelFXNugget()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BDD814);
	_ReadWriteBarrier();
	m_modelName = 0;
	m_randomlyRotate = false;
	m_expireTimer = LogicFramesPerSecond * 8;
}
