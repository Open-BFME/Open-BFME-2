// cl: /O1 /EHsc /arch:SSE2 /MD /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii
//
// ?createViewObject@SpecialPowerModule@@IAEXPBUCoord3D@@@Z, retail 0x00493845,
// 356 bytes. Zero Hour SpecialPowerModule::createViewObject semantic lead with
// BFME2 target deltas (all read from the retail body):
// - location null guard first (triggerSpecialPower(NULL) reaches here).
// - No modData null check; template null check stays.
// - viewObjectRange/duration live in the template's final override at +0x50/+0x4C
//   (two friend_getFinalOverride calls, one per ZH getter).
// - TheGlobalData->m_specialPowerViewObjectName AsciiString at +0xBA4.
// - ThingFactory::newObject takes four args (template, team, 16-byte zeroed
//   creation params, false); the params type is opaque, contents all zero.
// - getDefaultTeam() is an inline Player+0x2EC read.
// - Extra viewObject->bfmeRefreshPartitionCells() between setShroudClearingRange
//   and the DeletionUpdate lookup (rowed 0x0028C11A body).
// - DeletionUpdate reached via protected Object::findModule (friend access);
//   static DeletionUpdate key via TheNameKeyGenerator (/O1 static-guard EH).
// Float range compare is SSE (ucomiss) while the shroud-range argument still
// travels via x87 fstp: /arch:SSE2, like the stashed 0.8755-ratio scratch
// (reverse/attempts/0x00493845.cpp) this TU completes.
#include "ascii_string.h"
#include <string.h>

typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class SpecialPowerTemplate : public Overridable
{
public:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	Real getViewObjectRange() const { return getFO()->m_viewObjectRange; }
	UnsignedInt getViewObjectDuration() const { return getFO()->m_viewObjectDuration; }
private:
	char m_pad[0x4C];
	UnsignedInt m_viewObjectDuration;
	Real m_viewObjectRange;
};

class Team;
class Module;
class Player;
class ThingTemplate;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void setShroudClearingRange(Real range);
	void bfmeRefreshPartitionCells();
protected:
	Module *findModule(NameKeyType key) const;
	friend class SpecialPowerModule;
};

class DeletionUpdate
{
public:
	void setLifetimeRange(UnsignedInt a, UnsignedInt b);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GlobalData
{
public:
	char m_pad[0xBA4];
	AsciiString m_specialPowerViewObjectName;
};

extern GlobalData *TheGlobalData;

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	char m_pad[0x2EC];
	Team *m_defaultTeam;
};

// 16 bytes of creation params, all zero in this caller; exact type TBD.
struct CreateMask
{
	unsigned int words[4];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);
};

extern ThingFactory *TheThingFactory;

class ModuleData
{
public:
	virtual ~ModuleData();
};

class SpecialPowerModuleData : public ModuleData
{
public:
	char m_pad04[4];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class ObjectModule
{
protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class SpecialPowerModule : public BehaviorModule
{
protected:
	void createViewObject(const Coord3D *location);
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return (const SpecialPowerModuleData *)getModuleData(); }
};

void SpecialPowerModule::createViewObject(const Coord3D *location)
{
	if (location == NULL)
		return;

	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();
	const SpecialPowerTemplate *powerTemplate = modData->m_specialPowerTemplate;

	if (powerTemplate == NULL)
		return;

	Real visionRange = powerTemplate->getViewObjectRange();
	UnsignedInt visionDuration = powerTemplate->getViewObjectDuration();

	if (visionRange == 0 || visionDuration == 0)
		return; // We don't want a view object at all.

	AsciiString objectName = TheGlobalData->m_specialPowerViewObjectName;
	if (objectName.isEmpty())
		return;

	const ThingTemplate *viewObjectTemplate = TheThingFactory->findTemplate(objectName);
	if (viewObjectTemplate == NULL)
		return;

	CreateMask mask;
	memset(&mask, 0, sizeof(mask));

	Object *viewObject = TheThingFactory->newObject(viewObjectTemplate,
		getObject()->getControllingPlayer()->getDefaultTeam(), &mask, false);

	if (viewObject == NULL)
		return;

	viewObject->setPosition(location);
	viewObject->setShroudClearingRange(visionRange);
	viewObject->bfmeRefreshPartitionCells();

	static NameKeyType key_DeletionUpdate = TheNameKeyGenerator->nameToKey("DeletionUpdate");
	DeletionUpdate *dup = (DeletionUpdate *)viewObject->findModule(key_DeletionUpdate);
	if (dup)
	{
		dup->setLifetimeRange(visionDuration, visionDuration);
	}
}
