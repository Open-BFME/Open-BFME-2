// cl: /MD
//
// ??0Rva0056ADF1@@QAE@PAXH@Z @0x0056ADF1 53B.
// Constructor: run the pinned 0x0056AD80 initializer, null +0x14, install
// the 0x00C6D23C vftable at +0 and the 0x00C6D200 vftable at +8, then set
// +0x14 to the global-int at g_00DFEF10[0x100] plus the int argument.
// Honest address-derived name.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0056AC26Owner;
class Rva0056AC26
{
public:
	Rva0056AC26(Rva0056AC26Owner *owner);
};

// The retail table at RVA 0x0086D23C: 5 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0056AE4A@@UAEPAXI@Z")();
void __identifier("?rva0056A9A3@Rva0056A9B5@@QAEHXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
}
extern "C" const void *const vtbl_00C6D23C[5] = {
	(const void *)&__identifier("??_GRva0056AE4A@@UAEPAXI@Z"), // slot 0 0x0056AE2E
	(const void *)&__identifier("?rva0056A9A3@Rva0056A9B5@@QAEHXZ"), // slot 1 0x0056A9A3
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 2 0x0047A69C
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 3 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 4 0x000B3FD0
};
// The retail table at RVA 0x0086D200: 15 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_ERva0056AE4A@@W7AEPAXI@Z")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?Remove_Sub_Object@RenderObjClass@@UAEHPAV1@@Z")();
}
extern "C" const void *const vtbl_00C6D200[15] = {
	(const void *)&__identifier("??_ERva0056AE4A@@W7AEPAXI@Z"), // slot 0 0x0056AE26
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 1 0x005CB9FF
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 2 0x005CB9FF
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // slot 3 0x0050B5F1
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // slot 4 0x0050B5F1
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 5 0x005CB9FF
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 6 0x005CB9FF
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 7 0x005CB9FF
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 8 0x005CB9FF
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // slot 9 0x0050B5F1
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // slot 10 0x0050B5F1
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // slot 11 0x0050B5F1
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 12 0x005CB9FF
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13 0x0047A699
	(const void *)&__identifier("?Remove_Sub_Object@RenderObjClass@@UAEHPAV1@@Z"), // slot 14 0x005DAA6C
};

struct Rva0056ADF1Glob
{
	char m_pad[0x100];
	int m_100;
};

class Rva0056ADF1
{
public:
	Rva0056ADF1(void *owner, int arg2);
};

Rva0056ADF1::Rva0056ADF1(void *owner, int arg2)
{
	((Rva0056AC26 *)this)->Rva0056AC26::Rva0056AC26((Rva0056AC26Owner *)owner);
	*(int *)((char *)this + 0x14) = 0;
	*(unsigned int *)this = ((unsigned int)vtbl_00C6D23C);
	*(unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C6D200);
	*(int *)((char *)this + 0x14) = (*(Rva0056ADF1Glob **)&TheLivingWorldLogic)->m_100 + arg2;
}

