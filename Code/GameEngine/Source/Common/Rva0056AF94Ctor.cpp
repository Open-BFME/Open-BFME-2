// cl: /MD
//
// ??0Rva0056AF94@@QAE@PAX@Z @0x0056AF94 31B.
// Constructor: run the pinned EH 0x0056AD80 initializer, then install the
// 0x00C6D19C vftable at +0 and the 0x00C6D160 vftable at +8. Honest
// address-derived name.
class Rva0056AC26Owner;
class Rva0056AC26
{
public:
	Rva0056AC26(Rva0056AC26Owner *owner);
};

// The retail table at RVA 0x0086D19C: 5 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0056ACFF@@UAEPAXI@Z")();
void __identifier("?ac26Slot1@Rva0056ACFF@@UAE_NXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
}
extern "C" const void *const vtbl_00C6D19C[5] = {
	(const void *)&__identifier("??_GRva0056ACFF@@UAEPAXI@Z"), // slot 0 0x0056AFB3
	(const void *)&__identifier("?ac26Slot1@Rva0056ACFF@@UAE_NXZ"), // slot 1 0x0056ABC0
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 2 0x0047A69C
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 3 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 4 0x000B3FD0
};
// The retail table at RVA 0x0086D160: 15 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_ERva0056ACFF@@W7AEPAXI@Z")();
void __identifier("?b1Slot1@Rva0056ACFF@@UAE_NPAURva002B4BC9Arg@@@Z")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z")();
void __identifier("?rva0056ABD6@Rva0056ABD6@@QAE_NPAULivingWorldArmy@@PAVRva00318C32Ret@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?Remove_Sub_Object@RenderObjClass@@UAEHPAV1@@Z")();
}
extern "C" const void *const vtbl_00C6D160[15] = {
	(const void *)&__identifier("??_ERva0056ACFF@@W7AEPAXI@Z"), // slot 0 0x0056AD11
	(const void *)&__identifier("?b1Slot1@Rva0056ACFF@@UAE_NPAURva002B4BC9Arg@@@Z"), // slot 1 0x0056ABCB
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 2 0x005CB9FF
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // slot 3 0x0050B5F1
	(const void *)&__identifier("?rva0056ABD6@Rva0056ABD6@@QAE_NPAULivingWorldArmy@@PAVRva00318C32Ret@@@Z"), // slot 4 0x0056ABD6
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

class Rva0056AF94
{
public:
	Rva0056AF94(void *owner);
};

Rva0056AF94::Rva0056AF94(void *owner)
{
	((Rva0056AC26 *)this)->Rva0056AC26::Rva0056AC26((Rva0056AC26Owner *)owner);
	*(unsigned int *)this = ((unsigned int)vtbl_00C6D19C);
	*(unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C6D160);
}

