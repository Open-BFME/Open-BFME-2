// cl: /DNDEBUG /MD /EHs-c-
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
	RELOADING_CLIP
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
	char m_pad00[0x80];
	bool m_flag80;
	char m_pad81[0xE4 - 0x80 - 1];
	Int m_clipSize;
};

class Object
{
public:
	void setDisabledUntil(DisabledType type, UnsignedInt frame);
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
public:
	UnsignedInt getRemainingAmmo(bool countReloadingAsEmpty) const;
private:
	char m_pad00[4];
	WeaponTemplate *m_template;
	char m_pad08[8];
	WeaponStatus m_status;
	UnsignedInt m_ammoInClip;
	UnsignedInt m_whenWeCanFireAgain;
	char m_pad1C[0x28 - 0x1C];
	UnsignedInt m_whenLastReloadStarted;
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
