// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?Rva003BD062Set@@YGXPAXPBVAsciiString@@E@Z @0x003BD062 102B (dump range 18).
// Template-plus-player-mask loop: resolves the template name through the
// rowed 0x002D06CA lookup on TheThingFactory, builds the player mask from
// the struct's +0x10 name through rowed ScriptEngine 0x00357475, then walks
// the rowed 0x002A7BC9 getEachPlayerFromMask loop. The flag byte selects the
// rowed 0x002ABFA0 list-short-remove (flag != 0) or the pinned 0x002ACEDF
// sibling (flag == 0); retail shows the sibling reading the same +0x5D8 key
// through the same this+0x700 list, so it is the add-side twin.
#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern class ThingFactory *TheThingFactory;

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern ScriptEngine *TheScriptEngine;

class Player;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class Rva002ABFA0
{
public:
	void rva002ABFA0(void *p);
};
class Rva002ACEDF
{
public:
	void rva002ACEDF(void *p);
};

void __stdcall Rva003BD062Set(void *p, const AsciiString *templateName, unsigned char flag)
{
	void *t = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(templateName);
	if (t == 0)
		return;
	const AsciiString &name = *(const AsciiString *)((const char *)p + 0x10);
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *pl;
	do {
		pl = ThePlayerList->getEachPlayerFromMask(mask);
		if (pl != 0) {
			if (flag != 0)
				((Rva002ABFA0 *)pl)->rva002ABFA0(t);
			else
				((Rva002ACEDF *)pl)->rva002ACEDF(t);
		}
	} while (mask != 0);
}
