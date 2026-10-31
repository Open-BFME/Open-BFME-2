// cl: /MD /DNDEBUG /GX- /Oy- /O1 /arch:SSE /G7
//
// WeaponChangeSpecialPowerModule::doSpecialPower, retail 0x004C40BA, 413 bytes:
// slot 10 of the +0x10 special-power interface vftable 0x00C5D150, so `this`
// is that subobject (module data at -0x0C, Object at -0x08), as for
// ScavengerSpecialPower 0x004C4401. Toggles each weapon-set flag named by the
// module data's mask at +0x7C on the Object (clear when set, else set and
// clear the moving/attacking/firing model conditions), then applies the data's
// attribute modifier, disabled-until frames and special model condition, and
// runs the SpecialPowerModule base 0x0049490F.
// Target copy constructor 0x002CF108 (16 fixed bytes; see Object872.h).
class BfmeObject872Header
{
	char bytes[16];
public:
	__declspec(nothrow) BfmeObject872Header(const BfmeObject872Header &);
};
// Out-of-line StringBase<char>::isEmpty is the matched row 0x00001E2F.
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)

#include "../../../Common/Thing/thing.h"
class Player;
class Team;
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

class Rva0028D891Owner
{
public:
	bool testBit(int bit) const;
};

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;


struct WeaponChangeData
{
	unsigned char m_pad00[0x7C];
	BfmeObject872Header m_weaponSets;	// +0x7C, 16 bytes
	int m_attackerModifier;			// +0x8C
	int m_disabledFrames;			// +0x90
	AsciiString m_name94;			// +0x94
	AsciiString m_name98;			// +0x98
	const unsigned int *weaponSetWords() const { return (const unsigned int *)&m_weaponSets; }
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

class WeaponChangeSpecialPowerModule : public SpecialPowerModule
{
public:
	WeaponChangeSpecialPowerModule( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;
	virtual void doSpecialPower(unsigned int options);
	const WeaponChangeData *getData() const { return (const WeaponChangeData *)m_moduleData; }
	virtual void doSpecialPowerUsingWaypoints(void *target, float angle, int commandOptions);

protected:
	virtual ~WeaponChangeSpecialPowerModule();
};

void WeaponChangeSpecialPowerModule::doSpecialPower(unsigned int options)
{
	Object *object = m_object;
	if (object)
	{
		const WeaponChangeData *data = getData();
		static BitFlags<304> conditions;
		conditions.clear();
		conditions.setBitByName("MOVING");
		conditions.setBitByName("ATTACKING");
		conditions.setBitByName("FIRING_OR_PREATTACK_A");
		conditions.setBitByName("FIRING_OR_PREATTACK_B");
		if (!data)
			return;
		BfmeObject872Header sets(data->m_weaponSets);
		const unsigned int *words = (const unsigned int *)&sets;
		bool added = false;
		for (int i = 0; i < 0x68; ++i)
		{
			if (words[(unsigned int)i >> 5] & (1 << (i & 0x1f)))
			{
				if (((const Rva0028D891Owner *)object)->testBit(i))
					object->clearWeaponSetFlag((WeaponSetType)i);
				else
				{
					object->setWeaponSetFlag((WeaponSetType)i);
					object->rva001E42F2((const int *)&conditions);
					added = true;
					object->rva001E42F2((const int *)&conditions);
				}
			}
		}
		if (added)
		{
			if (!((const StringBase<char> *)&data->m_name94)->isEmpty() && data->m_attackerModifier)
				object->addAttributeModifierToPool(data->m_name94, data->m_attackerModifier);
			if (data->m_attackerModifier > 0)
				object->setDisabledUntil((DisabledType)4, TheGameLogic->getFrame() + data->m_attackerModifier);
			object->setSpecialModelConditionState((ModelConditionFlagType)0x149, data->m_attackerModifier);
		}
		else
		{
			if (!((const StringBase<char> *)&data->m_name98)->isEmpty() && data->m_disabledFrames)
				object->addAttributeModifierToPool(data->m_name98, data->m_disabledFrames);
			if (data->m_disabledFrames > 0)
				object->setDisabledUntil((DisabledType)4, TheGameLogic->getFrame() + data->m_disabledFrames);
		}
	}
	SpecialPowerModule::doSpecialPower(options);
}
