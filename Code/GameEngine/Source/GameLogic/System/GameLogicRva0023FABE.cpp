// cl: /O1 /DNDEBUG /MD /EHsc
//
// Unnamed GameLogic member (WorldBuilder 0x00D08400, GameLogic.cpp), retail
// 0x0023FABE (154B): give an object a drawable. A random value in [1, 999]
// (GetGameLogicRandomValue, called with this file and its line as in
// WorldBuilder), drawable status 0x20 when the object has status bit 0x37,
// ThingFactory::newDrawable (0x002CF21B on 0x00DFF000) for the object's
// template, GameLogic::bindObjectAndDrawable, then a local delayed Lua event
// list handed to the object-event dispatcher (TheLuaScriptEngine 0x003360D2, event
// 0xC). WorldBuilder line 0x199A against retail 0x199D.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../Common/Thing/thing.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_0x37 = 0x37 };
class Module;
class Drawable;
class Player;

class Object : public Thing, public Snapshot
{
public:
	void rva0028ACEE(int a, int b);
protected: Module *findModule(NameKeyType) const;
public: Module *lookupModule(NameKeyType key) const {return findModule(key);}
	bool isMassSelectable() const;
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
	void *rva0028BD3A() const;
	void rva0029041B(Player *player);
	void rva00290496(Player *player);
	void friend_bindToDrawable( Drawable *draw );
	void rva0028B31A(int val);
	bool testStatus(ObjectStatusTypes status) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }

	char m_pad64[0x74 - 0x64];
	ObjectID m_id; // +0x74
	char m_pad78[0x8C - 0x78];
	Object *m_next; // +0x8C
};

class Drawable;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class AsciiString;
struct CreateMask;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, ObjectID flag);
	void *newDrawable(void *tmplate, int status, int random);
};
extern ThingFactory *TheThingFactory;

// DelayedLuaEventList: ctor 0x000B6D8B and virtual dtor 0x000B6DD2 (slot 0 of its
// vftable 0x007C9CF0 is the scalar deleting dtor 0x000B6E0C); the vptr is the +0 word.
// BfmeDelayedLuaEventList is only the parameter tag of the 0x003360D2 row.
struct BfmeDelayedLuaEventList;
struct DelayedLuaEventList
{
	DelayedLuaEventList();
	virtual ~DelayedLuaEventList();

	unsigned char m_data[0x48];
};

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int event, void *obj, BfmeDelayedLuaEventList *list);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

void GameLogic::rva0023FABE(Object *obj)
{
	int random = GetGameLogicRandomValue(1, 999,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\GameLogic.cpp",
		0x199D);
	int status = 0;
	if (obj->testStatus(OBJECT_STATUS_0x37))
		status = 0x20;
	Drawable *draw = (Drawable *)TheThingFactory->newDrawable((void *)obj->getTemplate(), status, random);
	bindObjectAndDrawable(obj, draw);
	DelayedLuaEventList events;
	reinterpret_cast<BfmeObjectEventDispatch *>(TheLuaScriptEngine)->rva003360D2(0xC, obj, (BfmeDelayedLuaEventList *)&events);
}
