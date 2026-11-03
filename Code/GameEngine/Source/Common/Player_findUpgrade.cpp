// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?findUpgrade@Player@@QAEPAVUpgrade@@PBVUpgradeTemplate@@@Z @ 0x002AA031 (27B):
// list search (mov eax,[ecx+0x9c] / jmp test / mov ecx,[eax+4] / cmp ecx,[esp+4]
// / je ret / mov eax,[eax+0xc] / test eax,eax / jne loop / ret 4).
// Player::findUpgrade, ZH's walk of m_upgradeList comparing each upgrade's
// template, in BFME 2's layout: Player::addUpgrade (0x002AE329) and the
// upgrade-removal sibling 0x002ADAC3 call it with the Player in ecx and the
// UpgradeTemplate pushed, then unlink the result through Upgrade's +0x0C/+0x10
// next/prev; both units already spell the upgrade list at Player+0x9C and
// Upgrade's template at +0x04. ZH's own offsets (+0x40/+0x08/+0x10) do not
// apply. Formerly rowed as the address-named Rva002AA031Holder::find.
// Prev 0x002A9F0F (// cl: /O1) and next 0x002AA08E (// cl: /O1 /DNDEBUG /MD)
// share /O1.
class UpgradeTemplate;

class Upgrade
{
public:
	void *m_vtbl;
	const UpgradeTemplate *m_template;	// +0x04
	int m_status;						// +0x08
	Upgrade *m_next;					// +0x0C
	Upgrade *m_prev;					// +0x10
};

#include "../../Include/Common/Player.h"

Upgrade *Player::findUpgrade(const UpgradeTemplate *upgradeTemplate)
{
	for (Upgrade *upgrade = m_upgradeList; upgrade; upgrade = upgrade->m_next)
		if (upgrade->m_template == upgradeTemplate)
			return upgrade;
	return 0;
}
