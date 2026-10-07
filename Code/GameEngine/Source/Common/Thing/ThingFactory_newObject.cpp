// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@PBUCreateMask@@_N@Z,
// retail 0x002D0A23 (275 bytes); the mangled name is the existing call-site
// pin's (parameter types after the team are opaque there and stay so here).
// Donor (Zero Hour ThingFactory.cpp ThingFactory::newObject): pick a random
// build variation through findTemplate, have TheGameLogic create the
// object, run every behavior module's create interface, then initObject.
// Target evidence: WorldBuilder lead names 0x002D0A23 ThingFactory::newObject;
// the variation draw cites ThingFactory.cpp line 0x20B, the variation vector
// is ThingTemplate+0x330, findTemplate is the pinned 0x002D06CA and the
// behavior list Object+0x244. BFME 2 deltas (target): a null template returns
// NULL instead of throwing; TheGameLogic (0x00DFE78C) creation 0x0023CAE7
// takes a fourth argument passed straight through; no partition-manager
// registration; Sleep(0) yields under the 0x00DFF004 flag (as in the sibling
// 0x002CF21B); and a "newObj %s id %i" line to the 0x00DFEFF0 log.
// 0x002934E7 is Object::initObject (WorldBuilder lead), the last call.
#include "ascii_string.h"

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern void *g_00DFEFF0;
extern unsigned char g_00DFF004;

int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define THINGFACTORY_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\Common\\Thing\\ThingFactory.cpp"

typedef int Int;
typedef unsigned int ObjectID;

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	bool hasBuildVariations() const { return m_buildVariationsBegin != m_buildVariationsEnd; }
	Int getBuildVariationCount() const { return m_buildVariationsEnd - m_buildVariationsBegin; }
	const AsciiString &getBuildVariation(Int i) const { return m_buildVariationsBegin[i]; }

private:
	char m_pad[0x64];
	AsciiString m_name; // +0x64
	char m_pad68[0x330 - 0x68];
	AsciiString *m_buildVariationsBegin; // +0x330
	AsciiString *m_buildVariationsEnd;   // +0x334
};

class CreateModuleInterface
{
public:
	virtual void onCreate() = 0;
};

class ModuleBase
{
public:
	virtual ~ModuleBase();

private:
	char m_pad[8];
};

class BehaviorModuleInterface
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual CreateModuleInterface *getCreate() = 0;
};

class BehaviorModule : public ModuleBase, public BehaviorModuleInterface
{
};

class Team;
struct CreateMask;

class Object
{
public:
	Object(const ThingTemplate *tmplate, const CreateMask *mask, Team *team, bool flag, bool);
	ObjectID getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	void initObject();

private:
	char m_pad[0x74];
	ObjectID m_id; // +0x74
	char m_pad78[0x244 - 0x78];
	BehaviorModule **m_behaviors; // +0x244
	char m_pad248[0x4D8 - 0x248]; // target allocation size at 0x0023CAE7
};

class GameLogic
{
public:
	Object *friend_createObject(const ThingTemplate *tmplate, const CreateMask *mask, Team *team, bool flag);
};
extern GameLogic *TheGameLogic;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);
	const ThingTemplate *findTemplate(const AsciiString &name);
};

// ?friend_createObject@GameLogic@@QAEPAVObject@@PBVThingTemplate@@PBUCreateMask@@PAVTeam@@_N@Z
// @0x0023CAE7, 69B. Its matched caller at 0x002D0A23 supplies TheGameLogic
// and (template, mask, team, flag). Target allocates 0x4D8 bytes via scalar
// operator new 0x0002FDA0, then calls the Object constructor at 0x00298EA9
// with those four values followed by true. The helper's purpose beyond
// constructing an Object remains inferred from the caller and target calls.
Object *GameLogic::friend_createObject(const ThingTemplate *tmplate, const CreateMask *mask, Team *team, bool flag)
{
	return new Object(tmplate, mask, team, flag, true);
}

Object *ThingFactory::newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag)
{
	if (tmplate == 0)
		return 0;

	if (g_00DFF004)
		Sleep(0);

	if (tmplate->hasBuildVariations())
	{
		Int which = GetGameLogicRandomValue(0, tmplate->getBuildVariationCount() - 1, THINGFACTORY_FILE, 0x20B);
		const ThingTemplate *tmp = findTemplate(tmplate->getBuildVariation(which));
		if (tmp != 0)
			tmplate = tmp;
	}

	Object *obj = TheGameLogic->friend_createObject(tmplate, mask, team, flag);

	for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
	{
		if (g_00DFF004)
			Sleep(0);
		CreateModuleInterface *create = (*m)->getCreate();
		if (!create)
			continue;
		create->onCreate();
	}

	if (g_00DFF004)
		Sleep(0);
	obj->initObject();
	if (g_00DFF004)
		Sleep(0);

	if (g_00DFEFF0)
		fprintf((FprintfTarget *)g_00DFEFF0, "newObj %s id %i", tmplate->getName().str(), obj->getID());

	return obj;
}
