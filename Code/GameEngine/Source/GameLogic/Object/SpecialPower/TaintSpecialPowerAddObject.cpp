// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// TaintSpecialPower::addObject, retail 0x004C4940 (110B), from the WorldBuilder
// lead (TaintSpecialPower.cpp): create an object of the named template
// (ThingFactory::findTemplate, then ThingFactory::newObject with no team and a
// zeroed 16-byte create mask), place it at the position and give it the
// owning object's team (module +0x08 object, Object +0x304 team;
// Object::setTeam); returns the new object, or NULL without a template.
// The 0x004C45CF CloudBreakSpecialPower::addObject twin skips the team.

#include "ascii_string.h"
#include <string.h>

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Team;
class ThingTemplate;

struct CreateMask
{
public:
	unsigned int m_words[4]; // +0x00
};

#include "../../../Common/Thing/thing.h"

class Player;
enum ObjectStatusTypes
{
	OBJECT_STATUS_0x54 = 0x54
};

template <int N> class BitFlags
{
public:
	// Retail's guarded static of this type carries no EH state.
	__declspec(nothrow) BitFlags() { clear(); }
	bool any() const;	// 0x0023C58B for N = 11
	bool setBitByName(const char *token);
	void clear() { memset(m_words, 0, sizeof(m_words)); }
private:
	unsigned int m_words[N == 11 ? 1 : 19];
};

enum WeaponSetType { WEAPONSET_FIRST = 0 };
enum DisabledType { DISABLED_FIRST = 0 };
enum ModelConditionFlagType { MODELCONDITION_FIRST = 0 };

class Object : public Thing
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void rva0028EC68(int a, void *b, int c);
	void setTeam(Team *);
	Team *getTeam() const { return m_team; }
	bool isDisabled() const { return m_disabledMask.any(); }
	void setWeaponSetFlag(WeaponSetType type);
	void clearWeaponSetFlag(WeaponSetType type);
	void rva001E42F2(const int *mask);
	bool addAttributeModifierToPool(const AsciiString &name, int n);
	void setDisabledUntil(DisabledType type, unsigned int frame);
	void setSpecialModelConditionState(ModelConditionFlagType set, unsigned int frames);
private:
	char m_pad60[0x74 - 0x60];
public:
	int m_id; // +0x74
private:
	char m_pad78[0x1C8 - 0x78];
	BitFlags<11> m_disabledMask; // +0x1C8
	char m_pad1CC[0x304 - 0x1CC];
	Team *m_team; // +0x304
};

enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID b);
};
extern ThingFactory *TheThingFactory;

class ModuleData;
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
	virtual void doSpecialPowerUsingWaypoints(void *target, float angle, int commandOptions) = 0;
};

class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
	virtual void doSpecialPower(unsigned int options);	// 0x0049490F
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);	// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
	virtual void pauseCountdown(bool pause);	// 0x00492FC2
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class TaintSpecialPower : public SpecialPowerModule
{
public:
	TaintSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;

	void rva004C49AE(const Coord3D *position);
	Object *addObject(const Coord3D *position, const AsciiString &name);
	Object *getObject() const { return m_object; }
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);

protected:
	virtual ~TaintSpecialPower();
};

Object *TaintSpecialPower::addObject(const Coord3D *pos, const AsciiString &asciiString)
{
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(asciiString);
	if (thingTemplate)
	{
		CreateMask mask;
		memset(&mask, 0, sizeof(mask));
		Object *obj = TheThingFactory->newObject(thingTemplate, 0, &mask, (ObjectID)0);
		if (obj)
		{
			obj->setPosition(pos);
			obj->setTeam(getObject()->getTeam());
		}
		return obj;
	}
	return 0;
}
