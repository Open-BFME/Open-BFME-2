// ?pauseCountdown@Rva004C4430@@QAEX_N@Z
// partial score=0.97 date=2026-10-03
// ?pauseCountdown@Rva004C4430@@QAEX_N@Z
// partial score=0.97 date=2026-10-03
// cl: /DNDEBUG /MD
// ?pauseCountdown@Rva004C4430@@QAEX_N@Z @0x004C4430 77B: chain from 0x00492FC2
// Evidence: thiscall bool (cmp byte [ebp+8] ret 4); +0x24 gate then float from [this-0xC]+0x7C
// zeroed when arg!=0 via movss/xorps; Object at [this-8] -> getControllingPlayer (row 0x0028AFA9)
// -> Player::rva002A9E25(float) (row 0x002A9E25) with early push/fstp reuse; tail
// mov ecx,esi -> SpecialPowerModule::pauseCountdown(bool) (row 0x00492FC2). Negative offsets via explicit
// byte casts (same bytes as MI second-base); ScavengerSpecialPower neighbours give TU/flags.

class Player
{
public:
	void rva002A9E25(float value);
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

struct FloatHolder004C4430
{
	char m_pad[0x7C];
	float m_7C;
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

class Rva004C4430
{
public:
	void pauseCountdown(bool flag);

private:
	char m_pad[0x24];
	unsigned char m_24;
};

void Rva004C4430::pauseCountdown(bool flag)
{
	if (m_24 != 0) {
		float f = (*(FloatHolder004C4430 **)((char *)this - 12))->m_7C;
		if (flag != 0)
			f = 0.0f;
		Object *obj = *(Object **)((char *)this - 8);
		obj->getControllingPlayer()->rva002A9E25(f);
	}
	((SpecialPowerModule *)this)->SpecialPowerModule::pauseCountdown(flag);
}
