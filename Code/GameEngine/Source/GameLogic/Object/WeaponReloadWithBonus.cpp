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
class Object;
class FXList
{
public:
	static void doFXObj(const FXList *, const Object *, const Object *);
	static void doFXPos(const FXList *, const Coord3D *, const Matrix3D *, float, const Coord3D *);
};
#include "../../../Include/GameClient/Drawable.h"
// Existing callback-list provider; its four machine-word arguments are
// the weapon, source, victim, and position in this caller.
class WeaponBonus;
class Weapon;
class Rva001E11F8;
struct ListNode;
class Rva002CA9CA
{
private:
	friend class Weapon;
public:
	bool rva002CA9CA(int damageType, const void *weapon);
	void rva002CAA9D(int a1, const void *a2, const void *a3, const WeaponBonus &bonus);
	bool rva002CAA59(int source, const void *weapon);
	void postProcessLoad();
	void rva002CA970(int firingWeapon, int source, const void *weapon, int position);
	float getProjectileNuggetRadiusIfAlliesAffected(const void *arg);
	bool rva002CAD8B();
	void rva002CAC6E(int a, int context);
	bool getAutoReloadsClip() const { return m_128 == 0; }
	float getReal168() const { return m_168; }
	char m_pad00[0x58];
private:
	int m_58; // +0x58
	char m_pad5C[0x48];
	Rva001E11F8 *m_a4; // +0xA4
	Rva001E11F8 *m_a8; // +0xA8
	Rva001E11F8 *m_ac; // +0xAC
	Rva001E11F8 *m_b0; // +0xB0
	char m_padB4[0x4];
	Rva001E11F8 *m_b8; // +0xB8
	Rva001E11F8 *m_bc; // +0xBC
	Rva001E11F8 *m_c0; // +0xC0
	Rva001E11F8 *m_c4; // +0xC4
	char m_padC8[0x48];
	unsigned char m_110; // +0x110
	char m_pad111[0x17];
	int m_128; // +0x128
	char m_pad12C[0x4];
	float m_130; // +0x130
	char m_pad134[0x34];
	unsigned char m_168; // +0x168
	char m_pad169[0x13];
	ListNode *m_17c; // +0x17C
};
class WeaponBonus
{
public:
	Real m_field[6];
};

#include "../../../Include/GameLogic/WeaponTemplate.h"

#include "object.h"

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../Include/GameLogic/Weapon.h"

void Weapon::reloadWithBonus(const Object *sourceObj, const WeaponBonus &bonus, bool loadInstantly)
{
	m_ammoInClip = m_template->getClipSize();
	if (getRemainingAmmo(false) <= 0)
		m_ammoInClip = 0x7fffffff;

	if (m_status != RELOADING_CLIP)
		m_status = RELOADING_CLIP;

	Real reloadTime = loadInstantly ? 0 : m_template->getClipReloadTime(bonus);
	UnsignedInt curFrame = TheGameLogic->getFrame();
	m_projectileStreamID = curFrame;
	m_whenWeCanFireAgain = curFrame + reloadTime;

	if (reloadTime > 0.0f && m_template->m_field80)
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

	const WeaponTemplate *weaponTemplate = m_template;
	m_whenPreAttackFinished = TheGameLogic->getFrame() + delay;
	int timingExtra = weaponTemplate->m_field144;
	if (timingExtra > 0)
		m_lastFireFrame = TheGameLogic->getFrame() + timingExtra + delay;

	if (weaponTemplate->m_leechRangeWeapon)
	{
		int leechRangeDuration = (int)((float)weaponTemplate->m_preAttackDelay * bonus.m_field[4]);
		int leechTimingExtra = weaponTemplate->m_field144;
		m_leechWeaponRangeActive = TheGameLogic->getFrame() + leechRangeDuration + leechTimingExtra;
	}

	((Rva002CA9CA *)weaponTemplate)->rva002CA970(reinterpret_cast<int>(this), reinterpret_cast<int>(source), victim,
		reinterpret_cast<int>(position));

	const FXList *fireFX = weaponTemplate->m_fieldB8[0];
	float weaponSpeed = weaponTemplate->m_weaponSpeed;
	FXList::doFXPos(fireFX, source->getDrawable()->getPosition(),
		source->getDrawable()->getTransformMatrix(), weaponSpeed,
		source->getDrawable()->getPosition());
}
