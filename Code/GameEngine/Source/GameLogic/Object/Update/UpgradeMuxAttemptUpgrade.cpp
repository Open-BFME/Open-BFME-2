// cl: /DNDEBUG /MD
//
// ?forceRefreshUpgrade@UpgradeMux@@UAEXXZ, retail 0x004CE270, 12 bytes.
// ?attemptUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z, retail 0x004CE27C, 33 bytes.
// ?isAlreadyUpgraded@UpgradeMux@@UBE_NXZ, retail 0x00098CBC, 4 bytes.
// ?postUpgradeCheck@UpgradeMux@@UAEXXZ, retail 0x000B3FD0, 1 byte.
// UpgradeMux slots 5, 1 and 0 of vftable 0x00C5FF10 (installed by the rowed
// ??0UpgradeMux at 0x004CE2A3); both are shared by the 17 behavior
// vftables that embed an UpgradeMux. Donor ZH UpgradeModule.cpp:
//   forceRefreshUpgrade: if executed, re-run upgradeImplementation (slot 10,
//     the slot the rowed giveSelfUpgrade calls third);
//   attemptUpgrade: if wouldUpgrade (slot 2, rowed 0x004CE2B0) then
//     giveSelfUpgrade (rowed 0x0045230C) and return true.
//   isAlreadyUpgraded: return the executed flag. Slot 0 of 0x00C5FF10 holds
//     0x00098CBC (mov al,[ecx+4] / ret); retail ICF-folds it with the
//     identical RegistryClass::Is_Valid body rowed there.
// postUpgradeCheck: slot 6 of 0x00C5FF10 and of every UpgradeMux table that
//   does not override it (UpgradeModule 0x00842720, AttributeModifierUpgrade
//   0x008587A0, ...) is the shared empty RET at 0x000B3FD0; the rowed
//   Object::updateUpgradeModules calls it after attemptUpgrade (BFME 1 name).
// Retail's attemptUpgrade pops one dword (ret 4) and forwards it unchanged,
// so BFME2 passes the mask by reference, not by value as ZH does.

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

// ?isAlreadyUpgraded@UpgradeMux@@UBE_NXZ @0x00098CBC
bool UpgradeMux::isAlreadyUpgraded() const
{
	return m_upgradeExecuted;
}

// ?forceRefreshUpgrade@UpgradeMux@@UAEXXZ @0x004CE270
void UpgradeMux::forceRefreshUpgrade()
{
	if (m_upgradeExecuted)
	{
		upgradeImplementation();
	}
}

// ?postUpgradeCheck@UpgradeMux@@UAEXXZ @0x000B3FD0
void UpgradeMux::postUpgradeCheck()
{
}

// ?attemptUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z @0x004CE27C
bool UpgradeMux::attemptUpgrade(const BitFlags<128> &keyMask)
{
	if (wouldUpgrade(keyMask))
	{
		giveSelfUpgrade();
		return true;
	}
	return false;
}
