// cl: /GX /DNDEBUG /MD
//
// ??0RandomSoundSelectorClientBehaviorModuleData@@QAE@XZ, retail 0x0025785C,
// 102 bytes. Nullary ModuleData ctor over the rowed factory (0x25792A, news
// 0x1E0) and rowed proc (0x4CBC09, table 0xC5F318). Field layout from the
// table: UnitSpecificSounds at +0x1C8, Chance at +0x1D4, VoicePriority at
// +0x1D8, RerollOnEveryFrame at +0x1DD. The +8 region is a 448-byte array
// member (56 8-byte elements built by the 5-arg ehvec in 0x254FE4); the
// +0x1C8 member is 12 bytes built by the rowed map ctor 0x24613C. Both are
// declaration-only views. The empty base (inline-empty ctor plus declared-only
// dtor) drives the two EH states with zero emitted code (Topple pattern);
// without it the TU emits a single state. Chance defaults to 0.5 as a
// literal (pool-merged movss, address masked).

// The retail table at RVA 0x007F42A8: 31 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRandomSoundSelectorClientBehaviorModuleData@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
}
extern "C" const void *const vtbl_00BF42A8[31] = {
	(const void *)&__identifier("??_GRandomSoundSelectorClientBehaviorModuleData@@UAEPAXI@Z"), // slot 0 0x002578C2
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"), // slot 2 0x00065212
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 3 0x0047A69C
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 4 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 5 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 6 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 7 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 8 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 11 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 12 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13 0x0047A699
	(const void *)&__identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z"), // slot 14 0x000B69A1
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 15 0x0047A699
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 16 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 17 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 18 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 19 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 20 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 21 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 22 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 23 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 24 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 25 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 26 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 27 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 28 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 29 0x000D43D0
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 30 0x0050B5C6
};
class Rva00254FE4Member
{
public:
	Rva00254FE4Member();
	~Rva00254FE4Member();

private:
	unsigned char m_data[0x1C0];
};

// The +0x1C8 member's ctor is the rowed pod-map ctor 0x0024613C, spelled as
// Rva007ACDE1StlGlobalInits.cpp spells it; only the 12-byte header is modelled.
struct BfmePod8;
namespace _STL
{
template <class T> struct less;
template <class A, class B> struct pair;
template <class T> class allocator;

template <class K, class V, class C = less<K>, class A = allocator<pair<const K, V> > >
class map
{
public:
	map();
	~map();

private:
	unsigned char m_data[0x0C];
};
}

typedef _STL::map<int, BfmePod8> Rva0024613CMap;

// Retail's state-0 unwind funclet 0x00772097 jumps to the ModuleData dtor fold 0x0049B47C,
// rowed for this base as ??1ModuleDataBase@@QAE@XZ (AnimationSteeringUpdateModuleDataCtor.cpp).
class ModuleDataBase
{
public:
	__declspec(dllimport) __forceinline ModuleDataBase() {}
	~ModuleDataBase();
};

class RandomSoundSelectorClientBehaviorModuleData : public ModuleDataBase
{
public:
	RandomSoundSelectorClientBehaviorModuleData();

private:
	unsigned int m_vtable; // +0x00
	unsigned int m_pad04; // +0x04
	Rva00254FE4Member m_08; // +0x08 (0x1C0 bytes)
	Rva0024613CMap m_unitSpecificSounds; // +0x1C8
	float m_chance; // +0x1D4
	int m_voicePriority; // +0x1D8
	bool m_unknown1DC; // +0x1DC
	bool m_rerollOnEveryFrame; // +0x1DD
};

// ??0RandomSoundSelectorClientBehaviorModuleData@@QAE@XZ @0x25785C
RandomSoundSelectorClientBehaviorModuleData::RandomSoundSelectorClientBehaviorModuleData()
	: m_vtable(((unsigned int)vtbl_00BF42A8)), m_08(), m_unitSpecificSounds()
{
	m_chance = 0.5f;
	m_voicePriority = 0;
	m_unknown1DC = false;
	m_rerollOnEveryFrame = true;
}
