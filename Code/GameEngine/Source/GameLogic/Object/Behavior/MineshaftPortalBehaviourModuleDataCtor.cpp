// cl: /O1 /MD -D_STLP_NO_EXCEPTIONS /EHs-c-
//
// ??0MineshaftPortalBehaviourModuleData@@QAE@XZ, retail 0x00372DB8,
// 32 bytes. ModuleData ctor over the rowed OpenContainModuleData base
// (0x253487, 21B, folded vtable 0x00BF2558): installs the same folded vtable
// explicitly (novtable, mirroring OpenContainModuleDataCtor.cpp) and zeroes
// the two trailing flags at +0x118/+0x119. Class size 0x11C proven by both
// instance factories (FakePathfind 0x24B545 and Mineshaft 0x24B65D news
// 0x11C and both call this address): the two ModuleData ctors are ICF-folded
// here, and the 0x372Dxx page cluster (Mineshaft parse 0x372DD8 plus behavior
// 0x373096) proves the Mineshaft name for this row. Row supersedes the
// Mineshaft ModuleData pin; the FakePathfind pin at the same address is left
// in place as the fold alias.

class __declspec(novtable) OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

private:
	// +0x00 vptr (novtable: installed explicitly by each ctor).
	// Remainder is opaque here (0x114 bytes: UpdateModuleData tail plus the
	// +8 member the base ctor constructs); only the 0x118 size matters.
	unsigned char m_opaque[0x114];
};

class __declspec(novtable) MineshaftPortalBehaviourModuleData : public OpenContainModuleData
{
public:
	MineshaftPortalBehaviourModuleData();

private:
	// +0x118/+0x119 trailing behavior flags (false).
	bool m_trailingFlag0;
	bool m_trailingFlag1;
	char m_pad11A[2]; // to the rowed 0x11C instance size
};

// ??0MineshaftPortalBehaviourModuleData@@QAE@XZ @0x00372DB8
MineshaftPortalBehaviourModuleData::MineshaftPortalBehaviourModuleData()
	: OpenContainModuleData()
{
	*(unsigned int *)this = 0x00BF2558;
	m_trailingFlag0 = false;
	m_trailingFlag1 = false;
}
