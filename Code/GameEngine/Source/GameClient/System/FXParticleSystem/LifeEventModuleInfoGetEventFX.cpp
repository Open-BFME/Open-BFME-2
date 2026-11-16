// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?getEventFX@LifeEventModuleInfo@FXParticleSystem@@QAEPBVFXList@@XZ @0x0056410F 46B.
// Lazy FXList cache: on first call resolves the event name (m_data at +4
// with the +8 header skip, else the pinned empty string at 0x00BBAC1C)
// through TheFXListStore::findFXList (rowed 0x001E281A) and caches it at
// +0x14. Donor: BFME1 LifeEventModuleInfo (AsciiString m_eventName,
// GameClientRandomVariable m_eventTime, const FXList *m_cached; non-const
// getEventFX). Callers at 0x00564197 and 0x00564249; unblocks 0x0056413D
// and 0x005641ED.

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class FXList
{
};

#include "../../../../Include/GameClient/FXListStore.h"

extern FXListStore *TheFXListStore;

#include "../../../../Include/GameClient/LifeEventModuleInfo.h"

const FXList *FXParticleSystem::LifeEventModuleInfo::getEventFX()
{
	if (m_14 == 0)
	{
		const char *name = m_04.str();
		m_14 = TheFXListStore->findFXList(name);
	}
	return m_14;
}
