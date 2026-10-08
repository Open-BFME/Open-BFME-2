// cl: /Ireference/shims/bfme2_ascii
// ?Rva003E5017Check@@YG_NPAVParameter@@00@Z
// retail 0x003E5017 157B leaf free stdcall bool of 3x Parameter ret 0xc. Evidence:
// rowed Rva002D06CA::rva002D06CA via g_009FF000 with (Parameter+0x10 AsciiString)
// plus rowed ScriptEngine::getUnitNamed via g_Va009FE16C plus rowed rva00357B82
// plus rowed PlayerList::getPlayerFromMask via ThePlayerList plus rowed
// Object::getControllingPlayer twice plus static CastleBehavior::rva0003955DA
// plus rowed Object::findModule plus rowed Rva003971BF::rva003971BF;
// Parameter +0x08 int +0x10 AsciiString like sibling 0x003E6ED0;
// globals g_009FF000 g_Va009FE16C ThePlayerList; siblings 0x003E4F79 /O1.
#include "ascii_string.h"

class Parameter
{
public:
	char m_pad00[8];
	int m_int08;
	float m_real0c;
	AsciiString m_string10;
};

class Player
{
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;

class Object;

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
	int rva00357B82(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern class ThingFactory *TheThingFactory;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Module
{
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

struct Arg3971BF
{
};

class Rva003971BF
{
public:
	bool rva003971BF(Arg3971BF *arg);
};

class Object
{
	friend bool __stdcall Rva003E5017Check(Parameter *, Parameter *, Parameter *);
public:
	Player *getControllingPlayer() const;
protected:
	Module *findModule(NameKeyType key) const;
};

bool __stdcall Rva003E5017Check(Parameter *a, Parameter *b, Parameter *c)
{
	void *payload = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&c->m_string10);
	if (!payload)
		return false;
	Object *obj = TheScriptEngine->getUnitNamed(b);
	if (!obj)
		return false;
	int mask = TheScriptEngine->rva00357B82(a);
	if (!mask)
		return false;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player != 0) {
		Player *ctrl1 = obj->getControllingPlayer();
		if (ctrl1 == player) {
			Player *ctrl2 = obj->getControllingPlayer();
			if (player == ctrl2) {
				Module *mod = obj->findModule(CastleBehavior::rva0003955DA());
				if (mod != 0) {
					if (((Rva003971BF *)mod)->rva003971BF((Arg3971BF *)payload) != false)
						return true;
				}
			}
		}
	}
	return false;
}
