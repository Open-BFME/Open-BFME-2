// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BF96FDo@ScriptActions@@QAEXABVAsciiString@@0@Z @0x003BF96F 89B.
// Script unit player action via lookupUnitByValue then player mask and
// virtual slot 7 on the masked player.
// Evidence: rowed lookupUnitByValue rva00357475 getEachPlayerFromMask
// copy-ctor, externs g_Va009FE16C ThePlayerList, caller 0x003CB866 ret 8.
#include "ascii_string.h"

class Object
{
public:
	char m_pad00[0x74];
	void *m_74;
};

class Player
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual void d5();
	virtual void d6();
	virtual void v7(void *a1);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);
};

#include "../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void ScriptActions::Rva003BF96FDo(const AsciiString &asciiString, const AsciiString &a2)
{
	Object *obj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(a2);
	if (obj == 0)
		return;
	int mask = TheScriptEngine->rva00357475(asciiString, 0);
	Player *player = ThePlayerList->getEachPlayerFromMask(mask);
	if (player == 0)
		return;
	player->v7(obj->m_74);
}
