// cl: /DNDEBUG /MD
//
// ??0AnnounceBirthAndDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00485125, 56 bytes.
// AnnounceBirthAndDeathBehavior behavior ctor over the rowed CreateModule
// base (0x4B8CF7): double-stores +0x18 (C1C780 then C4A54C) around the
// primary vtable slot and the +0x0C/+0x10 secondary slots (address-of
// TU-local dummies, DIR32-masked). The rowed name getter at 0x485163 proves
// the class; the rowed instance factory 0x24C7C7 is the sole raw caller. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
// Retail table 0x00C4A61C (12 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva004851A8@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@BaseUpgrade@@MAEXXZ")();
void __identifier("?Rva0048515DGet@@YAHXZ")();
void __identifier("?xfer@Rva004851E3@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@AnnounceBirthAndDeathBehavior@@UBE?AW4NameKeyType@@XZ")();
void __identifier("?slot02@CreateModule@@UAEXXZ")();
void __identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z")();
void __identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ")();
}
static const void *const s_vtable[12] = {
	(const void *)&__identifier("??_GRva004851A8@@UAEPAXI@Z"), //  0 0x002549A5
	(const void *)&__identifier("?loadPostProcess@BaseUpgrade@@MAEXXZ"), //  1 0x00497805
	(const void *)&__identifier("?Rva0048515DGet@@YAHXZ"), //  2 0x0048515D
	(const void *)&__identifier("?xfer@Rva004851E3@@MAEXPAVXfer@@@Z"), //  3 0x004851E3
	(const void *)&__identifier("?getModuleNameKey@AnnounceBirthAndDeathBehavior@@UBE?AW4NameKeyType@@XZ"), //  4 0x00485163
	(const void *)&__identifier("?slot02@CreateModule@@UAEXXZ"), //  5 0x000B3FD0
	(const void *)&__identifier("?slot02@CreateModule@@UAEXXZ"), //  6 0x000B3FD0
	(const void *)&__identifier("?slot02@CreateModule@@UAEXXZ"), //  7 0x000B3FD0
	(const void *)&__identifier("?slot02@CreateModule@@UAEXXZ"), //  8 0x000B3FD0
	(const void *)&__identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z"), //  9 0x0050B238
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 10 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ")  // 11 0x000D43D0
};
// Retail table 0x00C4A560 (47 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ")();
void __identifier("?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ")();
void __identifier("?get@Rva0045875FLeaNegSbbField@@QBEHXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?slot02@CreateModule@@UAEXXZ")();
}
static const void *const s_secondary0C[47] = {
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), //  0 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), //  1 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), //  2 0x000D43D0
	(const void *)&__identifier("?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ"), //  3 0x002533D3
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), //  4 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), //  5 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), //  6 0x000D43D0
	(const void *)&__identifier("?get@Rva0045875FLeaNegSbbField@@QBEHXZ"), //  7 0x0045875F
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), //  8 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), //  9 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 10 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 11 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 12 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 13 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 14 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 15 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 16 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 17 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 18 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 19 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 20 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 21 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 22 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 23 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 24 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 25 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 26 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 27 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 28 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 29 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 30 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 31 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 32 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 33 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 34 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 35 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 36 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 37 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 38 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 39 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 40 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 41 0x000D43D0
	(const void *)&__identifier("?getDie@BehaviorModule@@UAEPAVDieModuleInterface@@XZ"), // 42 0x000D43D0
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), // 43 0x0047A69C
	(const void *)&__identifier("?slot02@CreateModule@@UAEXXZ"), // 44 0x000B3FD0
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), // 45 0x0047A69C
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z")  // 46 0x0047A69C
};
// Retail table 0x00C4A550 (4 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?onCreate@AnnounceBirthAndDeathBehavior@@UAEXXZ")();
void __identifier("?onBuildComplete@CreateModule@@UAEXXZ")();
void __identifier("?slot02@CreateModule@@UAEXXZ")();
void __identifier("?shouldDoOnBuildComplete@CreateModule@@UBE_NXZ")();
}
static const void *const s_secondary10[4] = {
	(const void *)&__identifier("?onCreate@AnnounceBirthAndDeathBehavior@@UAEXXZ"), //  0 0x004851AD
	(const void *)&__identifier("?onBuildComplete@CreateModule@@UAEXXZ"), //  1 0x00250A49
	(const void *)&__identifier("?slot02@CreateModule@@UAEXXZ"), //  2 0x000B3FD0
	(const void *)&__identifier("?shouldDoOnBuildComplete@CreateModule@@UBE_NXZ")  //  3 0x00098CBC
};
// Retail table 0x00C4A54C (1 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?onDie@AnnounceBirthAndDeathBehavior@@UAEXPBVDamageInfo@@@Z")();
}
static const void *const s_second18[1] = {
	(const void *)&__identifier("?onDie@AnnounceBirthAndDeathBehavior@@UAEXPBVDamageInfo@@@Z")  //  0 0x004851C7
};

// Rowed CreateModule base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class CreateModule
{
public:
	CreateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x18 - 0x14];
	const void *m_p18;
};

class AnnounceBirthAndDeathBehavior : public CreateModule
{
public:
	AnnounceBirthAndDeathBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0AnnounceBirthAndDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x485125
AnnounceBirthAndDeathBehavior::AnnounceBirthAndDeathBehavior(Thing *thing, const ModuleData *moduleData)
	: CreateModule(thing, moduleData)
{
	*(const void * volatile *)&m_p18 = &__identifier("??_7Rva003F498ACallback@@6B@");
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p18 = &s_second18;
}
