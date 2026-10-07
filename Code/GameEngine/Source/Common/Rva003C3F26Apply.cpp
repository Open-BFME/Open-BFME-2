// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?doPlayerSetSpecialPowerCountdown@ScriptActions@@IAEXABVAsciiString@@0H@Z @0x003C3F26 120B: player object via NameKeyGenerator PlayerList then SpecialPowerTemplate by name query Object special-power module then slot 0x20 with scaled GameLogic frame. Evidence: sibling Rva003C3EC5Apply same findSpecialPowerTemplate 0x29B6EB via g_00E02D4C Object::getSpecialPowerModule 0x28BB9E StringBase copy 0x365F0 plus rowed nameToKey 0x9FA65 findPlayerWithNameKey 0x2A7A41 rva002AC629 0x2AC629; caller 0x003CC6EE; ret 0xC stdcall.
#include "ascii_string.h"

enum NameKeyType { NK_NONE = 0 };

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
};

class Object;
class Player;
class ScriptEngine;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};
extern PlayerList *ThePlayerList;

class Player
{
public:
	Object *rva002AC629();
};

class SpecialPowerTemplate;
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

extern int g_Va00DBA4E4;

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

class Rva003C3F26Target
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08(int arg);
};

class ScriptActions
{
protected:
	void doPlayerSetSpecialPowerCountdown(const AsciiString &playerName, const AsciiString &powerName, int arg3);
};

void ScriptActions::doPlayerSetSpecialPowerCountdown(const AsciiString &playerName, const AsciiString &powerName, int arg3)
{
	Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName));
	if (player == 0)
		return;
	Object *obj = player->rva002AC629();
	if (obj == 0)
		return;
	const SpecialPowerTemplate *found = TheSpecialPowerStore->findSpecialPowerTemplate((AsciiString &)powerName);
	if (found == 0)
		return;
	void *sub = obj->getSpecialPowerModule(found);
	if (sub == 0)
		return;
	((Rva003C3F26Target *)sub)->w08(g_Va00DBA4E4 * arg3 + TheGameLogic->m_40);
}
