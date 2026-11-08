// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Weapon@@IAE@ABV0@@Z @0x002CC2FC 162B
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/WeaponCopyConstructor.cpp
//   (BFME1 Weapon copy ctor) plus ZH GeneralsMD Weapon.h (protected copy ctor, no default ctor).
// Target evidence: vtable 0x0080214C at +0; single-arg ret 4; copies +4/+8/+0xC/+0x30
//   from src, recomputes pitch (+0x88/+0x8C) and shots (+0x108) from template.
#include <vector>

#include "../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
};

#include "../../../Include/GameLogic/WeaponTemplate.h"

// LINK: read the pitch limits and shots per barrel through TU-local inlines
// (identical inlined bytes) so this TU emits no loser COMDATs of the
// header's getters. No flags touched.
static __forceinline float weaponTemplateMinPitch(const WeaponTemplate *wt) { return wt->m_minTargetPitch; }
static __forceinline float weaponTemplateMaxPitch(const WeaponTemplate *wt) { return wt->m_maxTargetPitch; }
static __forceinline int weaponTemplateShotsPerBarrel(const WeaponTemplate *wt) { return wt->m_shotsPerBarrel; }

#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class Xfer;
class Weapon
{
protected:
	Weapon(const WeaponTemplate *tmpl, WeaponSlotType wslot);
	Weapon(const Weapon &that);
	virtual ~Weapon(); // rowed in WeaponDtor.cpp; vtable 0x0080214C: dtor then three snapshot slots
	// Retail's table 0x00C0214C: the deleting destructor, an empty loadPostProcess (0x000B3FD0, shared),
	// the name getter 0x002CC2F6 and xfer 0x002CDD47. GameState::addPostProcessSnapshot leaves Weapons
	// off its post-process list by this name, so a pure slot here calls __purecall on load.
	virtual void loadPostProcess() {}
	virtual const char *GetSnapshotName() const { return "Weapon"; }
public:
	virtual void xfer(Xfer *xfer);
protected:

private:
	const WeaponTemplate *m_template; // +4
	unsigned int m_ownerID; // +8
	WeaponSlotType m_wslot; // +0xC
	unsigned int m_status; // +0x10
	unsigned int m_ammoInClip; // +0x14
	unsigned int m_whenWeCanFireAgain; // +0x18
	unsigned int m_whenPreAttackFinished; // +0x1C
	unsigned int m_whenLastReloadStarted; // +0x20
	unsigned int m_lastFireFrame; // +0x24
	unsigned int m_projectileStreamID; // +0x28
	unsigned int m_unknown2C; // +0x2C
	unsigned int m_suspendFXFrame; // +0x30
	int m_maxShotCount; // +0x34
	int m_curBarrel; // +0x38
	int m_numShotsForCurBarrel; // +0x3C
	_STL::vector<BfmeE16> m_scatterTargets; // +0x40
	bool m_pitchLimited; // +0x4C
	char m_pad4D[3];
	unsigned int m_leechWeaponRangeActive; // +0x50
	unsigned int m_unknown54; // +0x54
	unsigned int m_tailState; // +0x58
	unsigned int m_extra5C; // +0x5C
};

Weapon::Weapon(const Weapon &that)
	: m_scatterTargets(_STL::allocator<BfmeE16>())
{
	m_tailState = 0;
	m_template = that.m_template;
	m_ownerID = that.m_ownerID;
	m_wslot = that.m_wslot;
	m_status = 1;
	m_ammoInClip = 0;
	m_whenPreAttackFinished = 0;
	m_whenLastReloadStarted = 0;
	m_lastFireFrame = 0;
	m_projectileStreamID = 0;
	m_whenWeCanFireAgain = 0;
	m_leechWeaponRangeActive = 0;
	m_unknown54 = 0;
	m_pitchLimited = weaponTemplateMinPitch(m_template) > -3.14159265f || weaponTemplateMaxPitch(m_template) < 3.14159265f;
	m_curBarrel = 0;
	m_maxShotCount = 0x7fffffff;
	m_numShotsForCurBarrel = weaponTemplateShotsPerBarrel(m_template);
	m_unknown2C = 0;
	unsigned int suspend = that.m_suspendFXFrame;
	m_extra5C = 0;
	m_suspendFXFrame = suspend;
}

// ??0Weapon@@IAE@PBVWeaponTemplate@@W4WeaponSlotType@@@Z @0x002CC23D 185B
// Protected ctor (WeaponStore::allocateNewWeapon caller 0x0028AAA8). Donor
// order (BFME1 WeaponConstructor.cpp / ZH Weapon.cpp): template then slot,
// after the BFME2 +0x58 field; BFME2 null-checks the template for the pitch
// limit, the shots per barrel (default 1) and the suspend-FX frame
// (TheGameLogic frame plus the delay at +0x150). That statement order is
// what parks the vector's default-argument allocator temporary in the
// template parameter's slot ([ebp+0xb]), as retail does; the vector is left
// to its default argument.
Weapon::Weapon(const WeaponTemplate *weaponTemplate, WeaponSlotType wslot)
{
	m_tailState = 0;
	m_template = weaponTemplate;
	m_wslot = wslot;
	m_ownerID = 0;
	m_status = 1;
	m_ammoInClip = 0;
	m_whenWeCanFireAgain = 0;
	m_whenPreAttackFinished = 0;
	m_whenLastReloadStarted = 0;
	m_lastFireFrame = 0;
	m_projectileStreamID = 0;
	m_leechWeaponRangeActive = 0;
	m_unknown54 = 0;
	m_pitchLimited = weaponTemplate && (weaponTemplateMinPitch(weaponTemplate) > -3.14159265f || weaponTemplateMaxPitch(weaponTemplate) < 3.14159265f);
	m_maxShotCount = 0x7fffffff;
	m_curBarrel = 0;
	m_numShotsForCurBarrel = weaponTemplate ? weaponTemplateShotsPerBarrel(weaponTemplate) : 1;
	m_unknown2C = 0;
	unsigned int suspend = weaponTemplate ? TheGameLogic->getFrame() + weaponTemplate->getSuspendFXDelay() : 0;
	m_extra5C = 0;
	m_suspendFXFrame = suspend;
}

