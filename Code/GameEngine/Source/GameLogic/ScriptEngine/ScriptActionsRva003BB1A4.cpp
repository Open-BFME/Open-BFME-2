// cl: /Ireference/shims/bfme2_ascii
// ?Rva003BB1A4Grant@@YGXABVAsciiString@@0@Z, retail 0x003BB1A4, 91 bytes.
// Grant upgrade to players matching name mask.
// Evidence: leaf lane; callees ScriptEngine rva00357475 getEachPlayerFromMask findUpgrade Player rva002AE329; caller 0x003CA957.
#include "ascii_string.h"
#include "../../Common/RTS/PlayerUpgradeStatus.h"

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matched);
};
extern class ScriptEngine *TheScriptEngine;
class Player;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;
class UpgradeTemplate
{
public:
	char m_pad00[4];
	int m_val04;
};
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern "C" UpgradeCenter *TheUpgradeCenter;
class Player
{
public:
	Upgrade *rva002AE329(const UpgradeTemplate *tpl, UpgradeStatusType a2, int a3);
};
void __stdcall Rva003BB1A4Grant(const AsciiString &playerName, const AsciiString &upgradeName)
{
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (mask == 0)
		return;
	while (mask != 0) {
		Player *p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p != 0) {
			const UpgradeTemplate *tpl = TheUpgradeCenter->findUpgrade(upgradeName);
			if (tpl->m_val04 == 0)
				p->rva002AE329(tpl, UPGRADE_STATUS_COMPLETE, 0);
		}
	}
}
