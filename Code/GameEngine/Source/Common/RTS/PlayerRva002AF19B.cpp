// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// ?initPlayerUpgrades@Player@@QAEXXZ @0x002AF19B 81B Player grants starting upgrades from template vector at +0x180 via UpgradeCenter 0x0026F26D plus rowed rva002AE329 with 2 0. Evidence: caller 0x002AFC28 plus callee pin rva002AE329 plus global TheUpgradeCenter plus sibling Rva00485C86Finish loop pattern.
#include "ascii_string.h"

#include "PlayerUpgradeStatus.h"

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern "C" UpgradeCenter *TheUpgradeCenter;
#pragma comment(linker, "/alternatename:_TheUpgradeCenter=?TheUpgradeCenter@@3PAVUpgradeCenter@@A")

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
	Upgrade *rva002AE329(const UpgradeTemplate *t, UpgradeStatusType a, int b);
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
		const UpgradeTemplate *t = TheUpgradeCenter->findUpgrade(name);
		if (!t)
			continue;
		rva002AE329(t, UPGRADE_STATUS_COMPLETE, 0);
	}
}
