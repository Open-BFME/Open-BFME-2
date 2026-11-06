// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?getEventFX@TerrainCollisionModuleInfo@FXParticleSystem@@QAEPBVFXList@@XZ, retail 0x0056468E, 46 bytes; export ordinal 1686.
// Lazy FXList cache twin of LifeEventModuleInfo::getEventFX @0x0056410F (same
// 46B shape, same callees): on first call resolves the event name (m_data at
// +4 with the +8 header skip, else the pinned empty string at 0x00BBAC1C)
// through TheFXListStore::findFXList (rowed 0x001E281A) and caches it at
// +0x18 (this class carries a bool before the cache that LifeEvent lacks).
// Evidence: callers at 0x00564719 and 0x0056495A; unblocks 0x005646BC/135
// and 0x005648FE/157.

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class FXList
{
};

#include "../../../../Include/GameClient/FXListStore.h"
#include "../../../../Include/GameClient/TerrainCollisionModuleInfo.h"

extern FXListStore *TheFXListStore;

const FXList *FXParticleSystem::TerrainCollisionModuleInfo::getEventFX()
{
	if (m_18 == 0)
	{
		const char *name = m_04.str();
		m_18 = TheFXListStore->findFXList(name);
	}
	return m_18;
}
