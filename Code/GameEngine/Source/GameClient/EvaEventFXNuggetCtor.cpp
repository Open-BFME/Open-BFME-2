// cl: /O1 /DNDEBUG /MD
//
// ??0EvaEventFXNugget@@QAE@XZ 46B @0x1DFFFA: no-arg ctor called by
// EvaEventFXNugget::parse (0x001E12AD) for the EvaEvent FXList keyword;
// class name from BFME1. Member names and offsets from the retail FieldParse
// table 0x00BDCAD8 (EvaEventOwner@0x148 EvaEventAlly@0x14C EvaEventEnemy@0x150)
// and the BFME1 donor (FXNugget::m_field04 type id; BFME2 type is 15).
// Base 0x001DFEAA is a shared FXNugget-family base ctor; pinned opaquely.

// Retail VA 0x00BDD754 (.rdata): a 5-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_001DFF5D();
extern "C" void vfn_001E0028();
extern "C" void vfn_001E0A3B();
extern "C" void vfn_001F01E8();
extern "C" void vfn_0050B238();
#pragma comment(linker, "/alternatename:_vfn_001DFF5D=?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")
#pragma comment(linker, "/alternatename:_vfn_001E0028=?doFXObj@EvaEventFXNugget@@UBEXPBVObject@@0@Z")
#pragma comment(linker, "/alternatename:_vfn_001E0A3B=??_GRva001E009E@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_001F01E8=?rva001F01E8@Rva001F01E8@@QAEXHHHH@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B238=?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")
extern "C" const void *const vtbl_00BDD754[] = {
	(const void *)&vfn_001E0A3B,
	(const void *)&vfn_001F01E8,
	(const void *)&vfn_001E0028,
	(const void *)&vfn_0050B238,
	(const void *)&vfn_001DFF5D
};

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
protected:
	unsigned int m_vtablePad; // +0, overwritten by the derived vtable store
	int m_field04; // +4, nugget type id (BFME1 FXNugget::m_field04)
	unsigned char m_pad[0x148 - 8];
};

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
	m_field04 = 15;
}
