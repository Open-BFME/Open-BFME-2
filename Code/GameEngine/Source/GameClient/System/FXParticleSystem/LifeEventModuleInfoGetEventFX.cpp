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

namespace FXParticleSystem
{

class LifeEventModuleInfo
{
public:
	const FXList *getEventFX();
private:
	char m_pad0[4];
	AsciiString m_eventName;
	char m_pad8[12];
	const FXList *m_cached;
};

}

const FXList *FXParticleSystem::LifeEventModuleInfo::getEventFX()
{
	if (m_cached == 0)
	{
		const char *name = m_eventName.str();
		m_cached = TheFXListStore->findFXList(name);
	}
	return m_cached;
}
