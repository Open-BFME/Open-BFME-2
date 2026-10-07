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

enum ObjectStatusTypes { OBJECT_STATUS_0x37 = 0x37 };

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	const void *getTemplate() const { return m_template; }

private:
	void *m_vtbl;
	const void *m_template;
};

class Drawable;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Rva002CF21B
{
public:
	void *rva002CF21B(void *tmplate, int status, int random);
};
extern Rva002CF21B *g_00DFF000;

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();

	unsigned char m_data[0x4C];
};

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int event, void *obj, BfmeDelayedLuaEventList *list);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class GameLogic
{
public:
	void rva0023FABE(Object *obj);
	void bindObjectAndDrawable(Object *obj, Drawable *draw);
};

void GameLogic::rva0023FABE(Object *obj)
{
	int random = GetGameLogicRandomValue(1, 999,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\GameLogic.cpp",
		0x199D);
	int status = 0;
	if (obj->testStatus(OBJECT_STATUS_0x37))
		status = 0x20;
	Drawable *draw = (Drawable *)g_00DFF000->rva002CF21B((void *)obj->getTemplate(), status, random);
	bindObjectAndDrawable(obj, draw);
	BfmeDelayedLuaEventList events;
	reinterpret_cast<BfmeObjectEventDispatch *>(TheLuaScriptEngine)->rva003360D2(0xC, obj, &events);
}
