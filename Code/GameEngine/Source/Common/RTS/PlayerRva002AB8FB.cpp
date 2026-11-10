// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?rva002AB8FB@Player@@QAEXPAVObject@@_N@Z retail 0x002AB8FB 322B. Player grant AI
// difficulty upgrade via rowed callees plus pinned iterateObjects sibling. Copies
// 12B point pattern from 0x002AB22A precedent. Evidence: caller 0x0028B25B plus
// Upgrade literals plus TheGameLogic TheNameKeyGenerator TheUpgradeCenter.
#include "ascii_string.h"

class Object;
class Player;
class GameLogic;
class GameWindow;
class NameKeyGenerator;
class UpgradeCenter;
class UpgradeTemplate;
class BfmeGlob939D;

enum NameKeyType
{
	NK_Invalid = 0
};

#include "../../GameLogic/Object/object.h"

#include "../../../Include/Common/BfmeGlob939D.h"

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
extern UpgradeCenter *TheUpgradeCenter;
extern const char *g_Rva0107301CEmptyString;

#include "../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../Include/Common/NameKeyGenerator.h"

#include "../../../Include/Common/Upgrade.h"

class Player
{
	char m_pad00[0x2DC];
	GameWindow *m_window;
public:
	void rva002AB8FB(Object *obj, bool flag);
	void iterateObjects(void (*func)(Object *, void *), void *userData) const;
};

void __cdecl Rva002AA41A(Object *obj, void *userData);

void Player::rva002AB8FB(Object *obj, bool flag)
{
	if (!flag)
		return;
	if (obj == 0)
		return;
	if (obj->rva0028AFBB())
		return;
	if (obj->getControllingPlayer() == 0)
		return;
	if (*(int *)((char *)obj->getControllingPlayer() + 0x34) == 0)
		return;
	if (*(unsigned char *)((char *)*(int *)((char *)obj->getControllingPlayer() + 0x34) + 0x151) == 0)
		return;
	AsciiString upgradeName;
	BfmeGlob939D *gameLogic = *(BfmeGlob939D **)&TheGameLogic;
	GameWindow *gw;
	if (gameLogic->bfmeCall939D() == 0 || (gw = m_window) == 0) {
		GameLogic *gl = *(GameLogic **)&TheGameLogic;
		switch (*(int *)((char *)gl + 0xA4)) {
		case 0:
			upgradeName.set("Upgrade_EasyAISinglePlayer");
			break;
		case 1:
			upgradeName.set("Upgrade_MediumAISinglePlayer");
			break;
		case 2:
			upgradeName.set("Upgrade_HardAISinglePlayer");
			break;
		case 3:
			upgradeName.set("Upgrade_BrutalAISinglePlayer");
			break;
		}
	} else {
		switch ((int)gw->winGetUserData()) {
		case 0:
			upgradeName.set("Upgrade_EasyAIMultiPlayer");
			break;
		case 1:
			upgradeName.set("Upgrade_MediumAIMultiPlayer");
			break;
		case 2:
			upgradeName.set("Upgrade_HardAIMultiPlayer");
			break;
		case 3:
			upgradeName.set("Upgrade_BrutalAIMultiPlayer");
			break;
		}
	}
	const char *s = upgradeName.str();
	NameKeyType key = TheNameKeyGenerator->nameToKey(s);
	const UpgradeTemplate *upg = TheUpgradeCenter->findUpgradeByKey(key);
	if (upg != 0)
		obj->rva00293077(upg);
}
