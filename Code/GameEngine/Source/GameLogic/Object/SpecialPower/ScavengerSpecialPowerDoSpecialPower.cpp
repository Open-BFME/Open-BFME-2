// cl: /MD /GX
//
// ScavengerSpecialPower::doSpecialPower, retail 0x004C4401, 47 bytes: slot
// 10 of the class's +0x10 special-power interface vftable 0x00C5D2A0 (slots
// 11/12 there are the SpecialPowerModule bases), so `this` is that subobject
// (module data at -0x0C, Object at -0x08). Stores the module data's +0x7C
// float into the controlling Player's +0x314 (Player::rva002A9E25,
// 0x002A9E25), runs the SpecialPowerModule base doSpecialPower 0x0049490F,
// then raises the byte at +0x34.

class Player
{
public:
	void rva002A9E25(float value);	// sets +0x314
};

#include <string.h>
#include "../../../Common/Thing/thing.h"
class Team;
class AsciiString;
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

struct ScavengerSpecialPowerModuleData
{
	unsigned char m_pad00[0x7C];
	float m_7C;			// +0x7C
};

class ScavengerSpecialPower : public SpecialPowerModule
{
public:
	ScavengerSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void doSpecialPower(unsigned int options);
	const ScavengerSpecialPowerModuleData *getData() const
	{
		return (const ScavengerSpecialPowerModuleData *)m_moduleData;
	}

private:
	bool m_34; // +0x34
};





void ScavengerSpecialPower::doSpecialPower(unsigned int options)
{
	const ScavengerSpecialPowerModuleData *data = getData();
	Object *object = m_object;
	object->getControllingPlayer()->rva002A9E25(data->m_7C);
	SpecialPowerModule::doSpecialPower(options);
	m_34 = true;
}
