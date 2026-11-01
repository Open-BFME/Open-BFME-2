// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??4BuildListInfo@@QAEAAV0@ABV0@@Z @0x003299AD 211B
// BuildListInfo copy assignment (memberwise, 0x80 bytes).
// Evidence: layout identical to pinned copy ctor ??0BuildListInfo@@QAE@ABV0@@Z
// at 0x00329DE6 (same +4/+8/+30 AsciiStrings, same +0xC-0x20 six dwords,
// same +0x2C next pointer, same 10-dword array at +0x50 = MAX_RESOURCE_GATHERERS,
// same tail at +0x78/+0x7C); vtable 0x0080D904 from copy/default ctors;
// callees are AsciiString assign 0x000366F0 (vs 0x000365F0 copy in ctor);
// callers are 0x80 copy loops at 0x00329D64/0x0032A1FE/0x0032A587/0x0032BD25
// (sar 7 = /128). Donor: ZH SidesList.h BuildListInfo (3 AsciiStrings,
// Coord3D+Coord2D+Real, 9 bools, ObjectID/timestamp, 10 gatherers); retail
// groups the 4 tail bools at +0x44-0x47 (supply at +0x46 per AIPlayer).

#include "ascii_string.h"


#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../Include/GameLogic/Bfme2BuildListInfo.h"

BuildListInfo &BuildListInfo::operator=(const BuildListInfo &that)
{
	m_buildingName = that.m_buildingName;
	m_templateName = that.m_templateName;
	m_location = that.m_location;
	m_rallyPointOffset = that.m_rallyPointOffset;
	m_angle = that.m_angle;
	m_isInitiallyBuilt = that.m_isInitiallyBuilt;
	m_numRebuilds = that.m_numRebuilds;
	m_nextBuildList = that.m_nextBuildList;
	m_script = that.m_script;
	m_health = that.m_health;
	m_whiner = that.m_whiner;
	m_unsellable = that.m_unsellable;
	m_repairable = that.m_repairable;
	m_automaticallyBuild = that.m_automaticallyBuild;
	m_renderObj = that.m_renderObj;
	m_shadowObj = that.m_shadowObj;
	m_selected = that.m_selected;
	m_underConstruction = that.m_underConstruction;
	m_isSupplyBuilding = that.m_isSupplyBuilding;
	m_priorityBuild = that.m_priorityBuild;
	m_objectID = that.m_objectID;
	m_objectTimestamp = that.m_objectTimestamp;
	for (int i = 0; i < 10; i++)
		m_resourceGatherers[i] = that.m_resourceGatherers[i];
	m_desiredGatherers = that.m_desiredGatherers;
	m_currentGatherers = that.m_currentGatherers;
	return *this;
}
