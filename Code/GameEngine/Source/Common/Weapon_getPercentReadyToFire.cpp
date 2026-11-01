// ?getPercentReadyToFire@Weapon@@QBEMXZ
// cl: /DNDEBUG /MD
// ?getPercentReadyToFire@Weapon@@QBEMXZ @0x002CCE53 128B evidence: Weapon neighbours prev
// deleting dtor next getStatus plus computeStatus row; float div via
// BfmeZeroRange and 1.0 plus 2pow32 fixup; Rva000B2EB5 precedent flags.
enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK,
	WEAPON_STATUS_5
};
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#include "../../Include/GameLogic/Weapon.h"

float Weapon::getPercentReadyToFire() const
{
	WeaponStatus s = computeStatus(0);
	switch (s)
	{
	case READY_TO_FIRE:
		return 1.0f;
	case OUT_OF_AMMO:
		return 0.0f;
	case PRE_ATTACK:
		return 0.0f;
	case BETWEEN_FIRING_SHOTS:
	case RELOADING_CLIP:
	case WEAPON_STATUS_5:
		break;
	default:
		return 0.0f;
	}
	unsigned int cur = TheGameLogic->getFrame();
	if (cur >= m_whenWeCanFireAgain)
		return 1.0f;
	unsigned int total = m_whenWeCanFireAgain - m_projectileStreamID;
	if (total == 0)
		return 1.0f;
	unsigned int done = total - m_whenWeCanFireAgain + cur;
	if (done >= total)
		return 1.0f;
	return (float)done / (float)total;
}
