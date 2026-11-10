// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?doPlayerSetSpecialPowerCountdown@ScriptActions@@IAEXABVAsciiString@@0H@Z @0x003C3F26 120B: player object via NameKeyGenerator PlayerList then SpecialPowerTemplate by name query Object special-power module then slot 0x20 with scaled GameLogic frame. Evidence: sibling doNamedSetSpecialPowerCountdown same findSpecialPowerTemplate 0x29B6EB via g_00E02D4C Object::getSpecialPowerModule 0x28BB9E StringBase copy 0x365F0 plus rowed nameToKey 0x9FA65 findPlayerWithNameKey 0x2A7A41 rva002AC629 0x2AC629; caller 0x003CC6EE; ret 0xC stdcall.
#include "ascii_string.h"

enum NameKeyType { NK_NONE = 0 };

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

#include "../GameLogic/Object/object.h"

class Object;
class Player;
class ScriptEngine;

#include "../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../Include/Common/Player.h"

class SpecialPowerTemplate;
#include "../../Include/Common/SpecialPowerStore.h"

extern SpecialPowerStore *TheSpecialPowerStore;

extern int BfmeLogicFramesPerSecond;

#include "GameLogicObjectLookupView.h"

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
	((Rva003C3F26Target *)sub)->w08(BfmeLogicFramesPerSecond * arg3 + TheGameLogic->getFrame());
}
