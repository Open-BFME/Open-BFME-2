// cl: /MD
//
// ?setUpgradeExecuted@UpgradeMux@@UAEX_N@Z, retail 0x00452354, 10 bytes.
// Gap between 0x0045232D (Rva dtor) and 0x0045235E (AutoHeal pool key).
// Shared slot 9 (offset 0x24) of UpgradeMux member vtables (AutoHeal
// 0x83FC88 plus Replenish 0x849F20 plus AttributeModifier 0x850CD8 plus
// RadiateFear 0x850F68 and others) via rowed ctor evidence. Sets bool at
// +4 (m_upgradeExecuted). UpgradeMux table 0x00C5FF10 slot 9 holds it, and
// giveSelfUpgrade (0x0045230C) calls slot 9 with true; ZH UpgradeModule.h
// names that slot setUpgradeExecuted with this body. GameWinBlockInput's
// direct call reaches the same ICF-folded body.

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

void UpgradeMux::setUpgradeExecuted(bool e)
{
	m_upgradeExecuted = e;
}
