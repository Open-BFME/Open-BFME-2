// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// ?initPlayerUpgrades@Player@@QAEXXZ @0x002AF19B 81B Player grants starting upgrades from template vector at +0x180 via UpgradeCenter 0x0026F26D plus rowed addUpgrade with 2 0. Evidence: caller 0x002AFC28 plus callee pin addUpgrade plus global TheUpgradeCenter plus sibling Rva00485C86Finish loop pattern.
#include "ascii_string.h"

#include "PlayerUpgradeStatus.h"

class UpgradeTemplate;

#include "../../../Include/Common/Upgrade.h"
extern UpgradeCenter *TheUpgradeCenter;

struct UpgradeVecHolder
{
	char m_pad[0x180];
	AsciiString *m_begin;
	AsciiString *m_end;
};

class Player
{
public:
	void initPlayerUpgrades();
	Upgrade *addUpgrade(const UpgradeTemplate *t, UpgradeStatusType a, int b);
private:
	char m_pad[0x34];
	UpgradeVecHolder *m_holder;
};

void Player::initPlayerUpgrades()
{
	UpgradeVecHolder *holder = m_holder;
	if (!holder)
		return;
	int count = holder->m_end - holder->m_begin;
	for (int i = 0; i < count; ++i)
	{
		AsciiString &name = holder->m_begin[i];
		const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade(name);
		if (!upgradeTemplate)
			continue;
		addUpgrade(upgradeTemplate, UPGRADE_STATUS_COMPLETE, 0);
	}
}
