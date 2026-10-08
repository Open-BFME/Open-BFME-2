// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c-
// ?reloadWithBonus@Weapon@@IAEXPBVObject@@ABVWeaponBonus@@_N@Z @0x002CDB99 164B
// BFME1 donor: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp reloadWithBonus.
// BFME2 diverges per retail: provider-gated ammo (getRemainingAmmo), conditional
// RELOADING_CLIP store, float frame+reload via ftol2, setDisabledUntil sharing
// gated on template+0x80 with DisabledType 8. Callers 0x002CE1DE/0x002CE21B.
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

enum DisabledType
{
	DISABLED_DEFAULT,
	DISABLED_HACKED,
	DISABLED_EMP,
	DISABLED_HELD,
	DISABLED_PARALYZED,
	DISABLED_UNMANNED,
	DISABLED_UNDERPOWERED,
	DISABLED_FREEFALL,
	DISABLED_AWESTRUCK,
	DISABLED_BRAINWASHED,
	DISABLED_SUBDUED,
	DISABLED_SCRIPT_DISABLED,
	DISABLED_SCRIPT_UNDERPOWERED,
	DISABLED_COUNT,
	DISABLED_ANY = 65535
};

enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Matrix3D;
class FXList
{
public:
	static void doFXPos(const FXList *, const Coord3D *, const Matrix3D *, float, const Coord3D *);
};
class Drawable
{
public:
	const Coord3D *getPosition() const;
	const Matrix3D *getTransformMatrix() const;
};
// Existing callback-list provider; its four machine-word arguments are
// the weapon, source, victim, and position in this caller.
class Rva002CA9CA
{
public:
	void rva002CA970(int, int, const void *, int);
};
class Object;
class WeaponBonus
{
public:
	Real m_field[6];
};

class WeaponTemplate
{
public:
	Int getClipSize() const { return m_clipSize; }
	Int getClipReloadTime(const WeaponBonus &bonus) const;
	bool getFlag80() const { return m_flag80; }
private:
	char m_pad00[0x68];
public:
	float m_weaponSpeed;
private:
	char m_pad6C[0x80-0x6C];
	bool m_flag80;
	char m_pad81[0xB8-0x81];
public:
	const FXList *m_fireFX;
private:
	char m_padBC[0xE4-0xBC];
	Int m_clipSize;
	char m_padE8[0x130-0xE8];
public:
	bool m_leechRangeWeapon;
	char m_pad131[7];
	int m_preAttackDelay;
	int m_preAttackRandom;
	char m_pad140[4];
	int m_timingExtra;
};

class Object
{
public:
	void setDisabledUntil(DisabledType type, UnsignedInt frame);
	Drawable *getDrawable() const;
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_pad00[0x40];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

class Weapon
{
protected:
	void reloadWithBonus(const Object *sourceObj, const WeaponBonus &bonus, bool loadInstantly);
	void rebuildScatterTargets();
	void computeBonus(const Object *, unsigned int, WeaponBonus &) const;
public:
	UnsignedInt getRemainingAmmo(bool countReloadingAsEmpty) const;
	void preFireWeapon(const Object *, const Object *, const Coord3D *);
	int getPreAttackDelay(const Object *, const Object *, const Coord3D *) const;
	void rva002C959E();
private:
	char m_pad00[4];
	WeaponTemplate *m_template;
	char m_pad08[8];
	WeaponStatus m_status;
	UnsignedInt m_ammoInClip;
	UnsignedInt m_whenWeCanFireAgain;
	UnsignedInt m_whenPreAttackFinished;
	UnsignedInt m_unknown20;
	UnsignedInt m_lastFireFrame;
	UnsignedInt m_whenLastReloadStarted;
	char m_pad2C[0x50-0x2C];
	UnsignedInt m_leechWeaponRangeActive;
};

void Weapon::reloadWithBonus(const Object *sourceObj, const WeaponBonus &bonus, bool loadInstantly)
{
	m_ammoInClip = m_template->getClipSize();
	if (getRemainingAmmo(false) <= 0)
		m_ammoInClip = 0x7fffffff;

	if (m_status != RELOADING_CLIP)
		m_status = RELOADING_CLIP;

	Real reloadTime = loadInstantly ? 0 : m_template->getClipReloadTime(bonus);
	UnsignedInt curFrame = TheGameLogic->getFrame();
	m_whenLastReloadStarted = curFrame;
	m_whenWeCanFireAgain = curFrame + reloadTime;

	if (reloadTime > 0.0f && m_template->getFlag80())
		const_cast<Object *>(sourceObj)->setDisabledUntil(DISABLED_AWESTRUCK, m_whenWeCanFireAgain);

	rebuildScatterTargets();
}

// Native 0x002CDC3D..0x002CDD47; WorldBuilder Weapon.cpp:3335 and
// Object::preFireCurrentWeapon's call establish the three-pointer ABI.
// Donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/Object/Weapon_preFireWeapon.cpp.
// Target deltas: rowed jitter helper, unconditional pre-attack frame update,
// integer timing extra, GameLogic frame +0x40, and the static null-safe FX wrapper.
void Weapon::preFireWeapon(const Object *source, const Object *victim,
	const Coord3D *position)
{
	rva002C959E();

	int delay = getPreAttackDelay(source, victim, position);
	if (delay <= 0)
		return;

	if (m_status !=	PRE_ATTACK)
		m_status =	PRE_ATTACK;

	WeaponBonus bonus;
	for (int i = 0; i < 6; ++i)
		bonus.m_field[i] = 1.0f;
	computeBonus(source, 0, bonus);

	WeaponTemplate *weaponTemplate = m_template;
	m_whenPreAttackFinished = TheGameLogic->getFrame() + delay;
	int timingExtra = weaponTemplate->m_timingExtra;
	if (timingExtra > 0)
		m_lastFireFrame = TheGameLogic->getFrame() + timingExtra + delay;

	if (weaponTemplate->m_leechRangeWeapon)
	{
		int leechRangeDuration = (int)((float)weaponTemplate->m_preAttackDelay * bonus.m_field[4]);
		int leechTimingExtra = weaponTemplate->m_timingExtra;
		m_leechWeaponRangeActive = TheGameLogic->getFrame() + leechRangeDuration + leechTimingExtra;
	}

	((Rva002CA9CA *)weaponTemplate)->rva002CA970(reinterpret_cast<int>(this), reinterpret_cast<int>(source), victim,
		reinterpret_cast<int>(position));

	const FXList *fireFX = weaponTemplate->m_fireFX;
	float weaponSpeed = weaponTemplate->m_weaponSpeed;
	FXList::doFXPos(fireFX, source->getDrawable()->getPosition(),
		source->getDrawable()->getTransformMatrix(), weaponSpeed,
		source->getDrawable()->getPosition());
}
