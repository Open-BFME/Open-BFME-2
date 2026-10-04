// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /G5
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

class Object
{
public:
	bool rva0028AFBB() const;
	Player *getControllingPlayer() const;
	void rva00293077(const void *upgrade);
};

class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
extern "C" UpgradeCenter *_TheUpgradeCenter;
extern const char *g_Rva0107301CEmptyString;

class GameWindow
{
public:
	void *winGetUserData();
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *s);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
};

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
	AsciiString tmp;
	BfmeGlob939D *g = *(BfmeGlob939D **)&TheGameLogic;
	GameWindow *gw;
	if (g->bfmeCall939D() == 0 || (gw = m_window) == 0) {
		GameLogic *gl = *(GameLogic **)&TheGameLogic;
		switch (*(int *)((char *)gl + 0xA4)) {
		case 0:
			tmp.set("Upgrade_EasyAISinglePlayer");
			break;
		case 1:
			tmp.set("Upgrade_MediumAISinglePlayer");
			break;
		case 2:
			tmp.set("Upgrade_HardAISinglePlayer");
			break;
		case 3:
			tmp.set("Upgrade_BrutalAISinglePlayer");
			break;
		}
	} else {
		switch ((int)gw->winGetUserData()) {
		case 0:
			tmp.set("Upgrade_EasyAIMultiPlayer");
			break;
		case 1:
			tmp.set("Upgrade_MediumAIMultiPlayer");
			break;
		case 2:
			tmp.set("Upgrade_HardAIMultiPlayer");
			break;
		case 3:
			tmp.set("Upgrade_BrutalAIMultiPlayer");
			break;
		}
	}
	const char *s = tmp.str();
	NameKeyType key = TheNameKeyGenerator->nameToKey(s);
	const UpgradeTemplate *upg = _TheUpgradeCenter->findUpgradeByKey(key);
	if (upg != 0)
		obj->rva00293077(upg);
}
