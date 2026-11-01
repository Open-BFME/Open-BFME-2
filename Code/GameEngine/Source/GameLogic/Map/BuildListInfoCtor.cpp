// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
//
// ??0BuildListInfo@@QAE@XZ @0x0032A0CE 184B
// BuildListInfo default ctor (0x80 bytes).
// Evidence: vtable 0x0080D904 shared with pinned copy ctor ??0BuildListInfo@@QAE@ABV0@@Z
// at 0x00329DE6 and rowed assign ??4BuildListInfo@@QAEAAV0@ABV0@@Z at 0x003299AD;
// layout identical to BuildListInfoAssign.cpp (AsciiString at +4/+8/+30, Coord3D at +0x0C,
// Coord2D at +0x18, angle at +0x20, next at +0x2C, health 100 at +0x34, 10 gatherers
// at +0x50, tail at +0x78/+0x7C); both Strings copy AsciiString::TheEmptyString
// at 0x009E0878 via pinned StringBase copy 0x000365F0; callers are 0x80 copy loops
// at 0x0032A1FE/0x0032A587/0x0032BD25 that default-construct then assign.
// Donor: ZH SidesList.cpp BuildListInfo::BuildListInfo(void) (same init list plus
// body: location.zero, rally 0, selected false, gatherers INVALID_ID=0); retail
// zeroes templateName default inline (+8) and uses rep stosd for the 10 gatherers.
// Snapshot owns the state-0 cleanup; the scalar members retain the
// target layout and SSE float initialization.

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

#include "ascii_string.h"


// Coord3D: shared header/view; no private copy.
#include "../../../../Libraries/Include/Lib/Coord3DInline.h"

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../Include/GameLogic/Bfme2BuildListInfo.h"

BuildListInfo::BuildListInfo() :
	Snapshot(),
	m_buildingName(AsciiString::TheEmptyString),
	m_templateName(),
	m_nextBuildList(0),
	m_renderObj(0),
	m_shadowObj(0),
	m_isInitiallyBuilt(false),
	m_numRebuilds(0),
	m_angle(0.0f),
	m_script(AsciiString::TheEmptyString),
	m_health(100),
	m_whiner(true),
	m_unsellable(false),
	m_repairable(true),
	m_objectID(0),
	m_objectTimestamp(0),
	m_underConstruction(false),
	m_isSupplyBuilding(false),
	m_desiredGatherers(0),
	m_currentGatherers(0),
	m_automaticallyBuild(true),
	m_priorityBuild(false)
{
	m_location.zero();
	m_rallyPointOffset.x = 0.0f;
	m_rallyPointOffset.y = 0.0f;
	m_selected = false;
	for (int i = 0; i < 10; i++)
		m_resourceGatherers[i] = 0;
}

BuildListInfo *BuildListInfo::duplicate()
{
	BuildListInfo *first = new BuildListInfo;
	*first = *this;
	first->m_nextBuildList = 0;
	BuildListInfo *next = m_nextBuildList;
	BuildListInfo *cur = first;
	while (next) {
		BuildListInfo *link = new BuildListInfo;
		*link = *next;
		link->m_nextBuildList = 0;
		cur->m_nextBuildList = link;
		cur = link;
		next = next->m_nextBuildList;
	}
	return first;
}
