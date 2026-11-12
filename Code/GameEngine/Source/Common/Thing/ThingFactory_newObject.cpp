// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@PBUCreateMask@@W4ObjectID@@@Z,
// Retail 0x002D0A23 forwards the preset ObjectID through GameLogic creation.
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

// platformsdk
#include <windows.h>
#undef near
#undef far

struct FprintfTarget
{
	char m_pad[4];
};
// The game's own fprintf (pinned _fprintf), not the CRT import: read
// <stdio.h> without dllimport so the call goes straight to that thunk.
#define _CRTIMP
#include <stdio.h>
#undef _CRTIMP
extern "C" void *theLogicRandomLogFile;
extern unsigned char isLoadingMap;

int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define THINGFACTORY_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\Common\\Thing\\ThingFactory.cpp"

typedef int Int;
#include "../GameLogicObjectLookupView.h"

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

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "../../../Include/GameLogic/Module/BehaviorModule.h"


class Team;
struct CreateMask;

// The native constructor has a virtual base and therefore a hidden most-derived
// word. These call-only base views preserve its observed 0x74 ID, 0x244 module
// list and 0x4D8 allocation; constructor stores establish the base offsets.
#include "thing.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
class BfmeCtorFirstBase001B3A20 { public: virtual void slot(); };
class BfmeCtorVirtualBase001B3A20 { public: virtual void slot(); };
class BfmeCtor001B3A20 : public BfmeCtorFirstBase001B3A20, public virtual BfmeCtorVirtualBase001B3A20 {};
struct Rva00BFC2B8Base { virtual void base06CSlot0(); };
struct Rva00BFC290Base { virtual void base070Slot0(); };
class Object : public Thing, public Snapshot, public BfmeCtor001B3A20, public Rva00BFC2B8Base, public Rva00BFC290Base
{
public:
	Object(const ThingTemplate *tmplate, const CreateMask *mask, Team *team, ObjectID id);
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *);
	ObjectID getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	void initObject();

protected:
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle);

private:
	ObjectID m_id; // +0x74
	char m_pad78[0x244 - 0x78];
	BehaviorModule **m_behaviors; // +0x244
	char m_pad248[0x4D4 - 0x248]; // target allocation size at 0x0023CAE7
};

typedef char NativeObjectAllocationSize[sizeof(Object)==0x4D8?1:-1];

extern GameLogic *TheGameLogic;

#include "../../../Include/Common/ThingFactory.h"

// ?friend_createObject@GameLogic@@QAEPAVObject@@PBVThingTemplate@@PBUCreateMask@@PAVTeam@@W4ObjectID@@@Z
// @0x0023CAE7, 69B. Its matched caller at 0x002D0A23 supplies TheGameLogic
// and (template, mask, team, flag). Target allocates 0x4D8 bytes via scalar
// operator new 0x0002FDA0, then calls the Object constructor at 0x00298EA9
// with those four values preceded on the stack by the hidden most-derived
// true word. The helper's purpose beyond
// constructing an Object remains inferred from the caller and target calls.
Object *GameLogic::friend_createObject(const ThingTemplate *thingTemplate, const CreateMask *mask, Team *team, ObjectID id)
{
	// Retail forwards the complete four-byte argument slot to ObjectID.
	return new Object(thingTemplate, mask, team, id);
}

Object *ThingFactory::newObject(const ThingTemplate *thingTemplate, Team *team, const CreateMask *mask, ObjectID id)
{
	if (thingTemplate == 0)
		return 0;

	if (isLoadingMap)
		Sleep(0);

	if (thingTemplate->hasBuildVariations())
	{
		Int which = GetGameLogicRandomValue(0, thingTemplate->getBuildVariationCount() - 1, THINGFACTORY_FILE, 0x20B);
		const ThingTemplate *tmp = findTemplate(thingTemplate->getBuildVariation(which));
		if (tmp != 0)
			thingTemplate = tmp;
	}

	Object *obj = TheGameLogic->friend_createObject(thingTemplate, mask, team, id);

	for (BehaviorModule **behaviorModule = obj->getBehaviorModules(); *behaviorModule; ++behaviorModule)
	{
		if (isLoadingMap)
			Sleep(0);
		CreateModuleInterface *create = (*behaviorModule)->getCreate();
		if (!create)
			continue;
		create->onCreate();
	}

	if (isLoadingMap)
		Sleep(0);
	obj->initObject();
	if (isLoadingMap)
		Sleep(0);

	if (theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile, "newObj %s id %i", thingTemplate->getName().str(), obj->getID());

	return obj;
}
