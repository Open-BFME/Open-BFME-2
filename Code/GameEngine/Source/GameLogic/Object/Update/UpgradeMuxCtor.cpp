// cl: /O1 /DNDEBUG /MD
//
// ??0UpgradeMux@@QAE@XZ, retail 0x004CE2A3, 13 bytes. UpgradeMux root
// ctor (frameless leaf: installs vtable (void *)&g_00C5FF10 explicitly over the
// novtable model plus clears the executed flag at +4). Called this-direct
// with no adjustment by 12 behavior-ctor sites (0x4525B8/0x45F5C5/
// 0x460B12/0x48282B/0x482DA6/0x48424E/0x49B586/0x49C12C/0x4A3454/
// 0x4B40AA/0x4B7CE2/0x4C1CAB) as a shared member/base, and declared with
// this exact spelling in the AudioLoopUpgrade/FireWeaponWhenDamaged/
// RadiateFear/AttributeModifierAura behavior TUs (bool m_upgradeExecuted
// at +4); donor ZH UpgradeModule.h backs the UpgradeMux name. Row
// supersedes the same-name pin; the TU-local ALU_UpgradeMux alias pin
// stands for its own TU.

// Retail table 0x00C5FF10 (18 slots), stored by the constructor below. Own the
// complete initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?isAlreadyUpgraded@UpgradeMux@@UBE_NXZ")();
void __identifier("?attemptUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z")();
void __identifier("?wouldUpgrade@UpgradeMux@@UBE_NABV?$BitFlags@$0IA@@@@Z")();
void __identifier("?resetUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z")();
void __identifier("?vslot07@UpgradeMux@@UBE_NXZ")();
void __identifier("?isSubObjectsUpgrade@UpgradeMux@@UAE_NXZ")();
void __identifier("?upgradeMuxLoadPostProcess@UpgradeMux@@MAEXXZ")();
void __identifier("?forceRefreshUpgrade@UpgradeMux@@UAEXXZ")();
void __identifier("?postUpgradeCheck@UpgradeMux@@UAEXXZ")();
int __cdecl _purecall(void);
void __identifier("?setUpgradeExecuted@UpgradeMux@@UAEX_N@Z")();
void __identifier("?upgradeMuxXfer@UpgradeMux@@MAEXPAVXfer@@@Z")();
}
extern const void *const g_00C5FF10[18] = {
	(const void *)&__identifier("?isAlreadyUpgraded@UpgradeMux@@UBE_NXZ"), //  0 0x00098CBC
	(const void *)&__identifier("?attemptUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z"), //  1 0x004CE27C
	(const void *)&__identifier("?wouldUpgrade@UpgradeMux@@UBE_NABV?$BitFlags@$0IA@@@@Z"), //  2 0x004CE2B0
	(const void *)&__identifier("?resetUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z"), //  3 0x004CE342
	(const void *)&__identifier("?isSubObjectsUpgrade@UpgradeMux@@UAE_NXZ"), //  4 0x0047A699
	(const void *)&__identifier("?forceRefreshUpgrade@UpgradeMux@@UAEXXZ"), //  5 0x004CE270
	(const void *)&__identifier("?postUpgradeCheck@UpgradeMux@@UAEXXZ"), //  6 0x000B3FD0
	(const void *)&__identifier("?vslot07@UpgradeMux@@UBE_NXZ"), //  7 0x0047A699
	(const void *)&_purecall, //  8 0x0003B810
	(const void *)&__identifier("?setUpgradeExecuted@UpgradeMux@@UAEX_N@Z"), //  9 0x00452354
	(const void *)&_purecall, // 10 0x0003B810
	(const void *)&_purecall, // 11 0x0003B810
	(const void *)&_purecall, // 12 0x0003B810
	(const void *)&_purecall, // 13 0x0003B810
	(const void *)&_purecall, // 14 0x0003B810
	(const void *)&_purecall, // 15 0x0003B810
	(const void *)&__identifier("?upgradeMuxXfer@UpgradeMux@@MAEXPAVXfer@@@Z"), // 16 0x004CE397
	(const void *)&__identifier("?upgradeMuxLoadPostProcess@UpgradeMux@@MAEXXZ")  // 17 0x000B3FD0
};

class __declspec(novtable) UpgradeMux
{
public:
	UpgradeMux();

private:
	void *m_vtable; // +0
	bool m_executed; // +4, upgrade-executed flag
};

// ??0UpgradeMux@@QAE@XZ @0x4CE2A3
inline UpgradeMux::UpgradeMux()
	: m_vtable(reinterpret_cast<void *>((void *)&g_00C5FF10)),
	  m_executed(false)
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeUpgradeMuxInlineAnchor@@YAXPAVUpgradeMux@@@Z absent-from-retail
void _bfmeUpgradeMuxInlineAnchor(UpgradeMux *upgradeMux)
{
    upgradeMux->UpgradeMux::UpgradeMux();
}
#pragma inline_depth()
