// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc
//
// ??0BuildListInfo@@QAE@ABV0@@Z @0x00329DE6 253B
// BuildListInfo copy constructor (memberwise, 0x80 bytes).
// Evidence: retail stores vtable 0x0080D904 (shared with the rowed default ctor
// 0x0032A0CE) then copies +4/+8/+0x30 through the pinned StringBase<char> copy
// 0x000365F0 under EH states 0/1/2, the scalar members in declaration order, and
// the 10-dword gatherer block at +0x50 by rep movsd between +0x4C and +0x78;
// called out of line from the STLport _Construct at 0x0032A2AF. Layout as in
// BuildListInfoAssign.cpp / BuildListInfoCtor.cpp (ZH SidesList.h donor).
// The members are AsciiString, not bare StringBase: the inline AsciiString copy
// ctor evaluates source and this before the push (lea eax / lea ecx / push eax),
// which bare StringBase<char> members reorder to lea / push / lea.
// The canonical type keeps real Coord3D/Coord2D fields and int[10]. Native
// copies their scalar values before constructing m_script, and copies the ten
// gatherers before initializing m_desiredGatherers. Sequence those operations
// in the corresponding initializer expressions; a bulk coordinate copy would
// emit movs, whereas the measured native stores are individual dword moves.
// BuildListGatherers is the existing trivial ten-ID copy carrier, not a second
// BuildListInfo layout. The native strings/base and their EH states stay real.
// Snapshot owns the vptr at +0; state-0 cleanup calls its destructor
// before any AsciiString member has completed construction.

// The unwind funclets jump to the out-of-line ~AsciiString 0x0048BA39.
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

struct BuildListGatherers
{
	int ids[10];
};
typedef char BuildListGatherers_extent28[(sizeof(BuildListGatherers)==0x28)?1:-1];

#include "../../../Include/GameLogic/Bfme2BuildListInfo.h"

BuildListInfo::BuildListInfo(const BuildListInfo &that) :
	Snapshot(),
	m_buildingName(that.m_buildingName),
	m_templateName(that.m_templateName),
	m_script((m_location.x = that.m_location.x,
        m_location.y = that.m_location.y,
        m_location.z = that.m_location.z,
        m_rallyPointOffset.x = that.m_rallyPointOffset.x,
        m_rallyPointOffset.y = that.m_rallyPointOffset.y,
        m_angle = that.m_angle,
        m_isInitiallyBuilt = that.m_isInitiallyBuilt,
        m_numRebuilds = that.m_numRebuilds,
        m_nextBuildList = that.m_nextBuildList,
        that.m_script)),
	m_health(that.m_health),
	m_whiner(that.m_whiner),
	m_unsellable(that.m_unsellable),
	m_repairable(that.m_repairable),
	m_automaticallyBuild(that.m_automaticallyBuild),
	m_renderObj(that.m_renderObj),
	m_shadowObj(that.m_shadowObj),
	m_selected(that.m_selected),
	m_underConstruction(that.m_underConstruction),
	m_isSupplyBuilding(that.m_isSupplyBuilding),
	m_priorityBuild(that.m_priorityBuild),
	m_objectID(that.m_objectID),
	m_objectTimestamp(that.m_objectTimestamp),
	m_desiredGatherers((*(BuildListGatherers *)m_resourceGatherers =
        *(const BuildListGatherers *)that.m_resourceGatherers,
        that.m_desiredGatherers)),
	m_currentGatherers(that.m_currentGatherers)
{
}
