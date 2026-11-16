// cl: /DNDEBUG /MD
//
// ??0EvaEventFXNugget@@QAE@XZ 46B @0x1DFFFA: no-arg ctor called by
// EvaEventFXNugget::parse (0x001E12AD) for the EvaEvent FXList keyword;
// class name from BFME1. Member names and offsets from the retail FieldParse
// table 0x00BDCAD8 (EvaEventOwner@0x148 EvaEventAlly@0x14C EvaEventEnemy@0x150)
// and the BFME1 donor (FXNugget::m_field04 type id; BFME2 type is 15).
// Base 0x001DFEAA is the shared FXNugget-family base (Rva001DFEAABase.h).

// Retail VA 0x00BDD754 (.rdata): a 5-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")();
extern "C" void __identifier("?doFXObj@EvaEventFXNugget@@UBEXPBVObject@@0@Z")();
extern "C" void __identifier("??_GRva001E009E@@UAEPAXI@Z")();
extern "C" void __identifier("?rva001F01E8@Rva001F01E8@@QAEXHHHH@Z")();
extern "C" void __identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")();
extern "C" const void *const vtbl_00BDD754[] = {
	(const void *)&__identifier("??_GRva001E009E@@UAEPAXI@Z"),
	(const void *)&__identifier("?rva001F01E8@Rva001F01E8@@QAEXHHHH@Z"),
	(const void *)&__identifier("?doFXObj@EvaEventFXNugget@@UBEXPBVObject@@0@Z"),
	(const void *)&__identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z"),
	(const void *)&__identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")
};

#include "../../Include/GameClient/Rva001DFEAABase.h"

class EvaEventFXNugget : public Rva001DFEAABase
{
public:
	EvaEventFXNugget();
private:
	int m_evaEventOwner; // +0x148
	int m_evaEventAlly; // +0x14C
	int m_evaEventEnemy; // +0x150
};

// ??0EvaEventFXNugget@@QAE@XZ
EvaEventFXNugget::EvaEventFXNugget()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BDD754);
	m_evaEventOwner |= -1;
	m_evaEventAlly |= -1;
	m_evaEventEnemy |= -1;
	m_nuggetType = 15;
}
