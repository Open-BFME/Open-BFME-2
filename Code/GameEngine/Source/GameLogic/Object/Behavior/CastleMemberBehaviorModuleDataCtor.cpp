// cl: /DNDEBUG /MD
// Native constructor 0x00395B03; defaults from the INI table at VA 0x00C1A310.
#include "CastleMemberBehaviorModuleData.h"

CastleMemberBehaviorModuleData::CastleMemberBehaviorModuleData()
{
	m_campDestroyedOwnerEvaEvent = 9;
	m_campDestroyedAllyEvaEvent = 0xA;
	m_campDestroyedAttackerEvaEvent = 8;
	m_beingBuiltSound.m_ptr = 0;
	m_storeUpgradePrice = false;
	m_countsForEvaCastleBreached = false;
}
