// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?Rva003BD19CSet@@YGXPAXPAVParameter@@@Z @0x003BD19C 212B (dump range 18).
// Unit-named-plus-player-mask loop: resolves the unit through rowed
// ScriptEngine 0x003588E7 getUnitNamed, builds the player mask from the
// struct's +0x10 name through rowed 0x00357475, then walks rowed 0x002A7BC9.
// When the walked player is the list's +0x10 local player, notifies
// TheInGameUI (slot 0x110), emits message 0x3E9 (rowed appends
// 0x0030F963/0x0030F979) and routes the unit's drawable through TheInGameUI
// slot 0x108; every walked player also feeds the pinned 0x0023C924 GameLogic
// member with (unit, 1, 1 << index, 0).
#include "ascii_string.h"

class Parameter;
class Drawable;
enum ObjectID
{
	OBJECTID_NONE = 0
};

class Object
{
public:
	Drawable *getDrawable() const;
	char m_pad[0x74];
	ObjectID m_id; // +0x74
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern ScriptEngine *TheScriptEngine;

class Player
{
public:
	unsigned char m_pad[0x54];
	int m_playerIndex; // +0x54
};
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
	char m_pad00[0x10];
	Player *m_localPlayer; // +0x10
};
extern PlayerList *ThePlayerList;

class GameLogic
{
public:
	void rva0023C924(void *obj, int a, int bit, int b);
};
extern GameLogic *TheGameLogic;

class GameMessage
{
public:
	void appendBooleanArgument(bool arg);
	void appendObjectIDArgument(ObjectID id);
};

class MessageStream
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *appendType(int type);
};
extern class MessageStream *TheMessageStream;

class InGameUI
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
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void w20();
	virtual void w21();
	virtual void w22();
	virtual void w23();
	virtual void w24();
	virtual void w25();
	virtual void w26();
	virtual void w27();
	virtual void w28();
	virtual void w29();
	virtual void w30();
	virtual void w31();
	virtual void w32();
	virtual void w33();
	virtual void w34();
	virtual void w35();
	virtual void w36();
	virtual void w37();
	virtual void w38();
	virtual void w39();
	virtual void w40();
	virtual void w41();
	virtual void w42();
	virtual void w43();
	virtual void w44();
	virtual void w45();
	virtual void w46();
	virtual void w47();
	virtual void w48();
	virtual void w49();
	virtual void w50();
	virtual void w51();
	virtual void w52();
	virtual void w53();
	virtual void w54();
	virtual void w55();
	virtual void w56();
	virtual void w57();
	virtual void w58();
	virtual void w59();
	virtual void w60();
	virtual void w61();
	virtual void w62();
	virtual void w63();
	virtual void w64();
	virtual void w65();
	virtual void w66(Drawable *d);
	virtual void w67();
	virtual void notify();
};
extern InGameUI *TheInGameUI;

void __stdcall Rva003BD19CSet(void *p, Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	const AsciiString &name = *(const AsciiString *)((const char *)p + 0x10);
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *pl;
	do {
		pl = ThePlayerList->getEachPlayerFromMask(mask);
		if (pl != 0) {
			if (pl == ThePlayerList->m_localPlayer) {
				TheInGameUI->notify();
				GameMessage *msg = TheMessageStream->appendType(0x3E9);
				msg->appendBooleanArgument(true);
				msg->appendObjectIDArgument(obj->m_id);
				TheInGameUI->w66(obj->getDrawable());
			}
			TheGameLogic->rva0023C924(obj, 1, 1 << pl->m_playerIndex, 0);
		}
	} while (mask != 0);
}
