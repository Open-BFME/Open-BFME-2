// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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
// EH state 0 before the first copy comes from the empty base with declared-only
// dtor (AIUpdateModuleDataCtor precedent); /arch:SSE for the xorps/movss float zeroes.

extern "C" const void *const vtbl_00C0D904[];  // ??_7BuildListInfo@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C0D904=??_7BuildListInfo@@6B@")

#include "ascii_string.h"


struct Coord3D
{
	float x;
	float y;
	float z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

#include "../../../../Libraries/Include/Lib/Coord2D.h"

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class BuildListInfo : public EmptyBase
{
public:
	BuildListInfo();
	BuildListInfo *duplicate();
	BuildListInfo &operator=(const BuildListInfo &);

private:
	void *m_vtable; // +0x00
	AsciiString m_buildingName; // +0x04
	AsciiString m_templateName; // +0x08
	Coord3D m_location; // +0x0C
	Coord2D m_rallyPointOffset; // +0x18
	float m_angle; // +0x20
	bool m_isInitiallyBuilt; // +0x24
	unsigned int m_numRebuilds; // +0x28
	BuildListInfo *m_nextBuildList; // +0x2C
	AsciiString m_script; // +0x30
	int m_health; // +0x34
	bool m_whiner; // +0x38
	bool m_unsellable; // +0x39
	bool m_repairable; // +0x3A
	bool m_automaticallyBuild; // +0x3B
	void *m_renderObj; // +0x3C
	void *m_shadowObj; // +0x40
	bool m_selected; // +0x44
	bool m_underConstruction; // +0x45
	bool m_isSupplyBuilding; // +0x46
	bool m_priorityBuild; // +0x47
	int m_objectID; // +0x48
	unsigned int m_objectTimestamp; // +0x4C
	int m_resourceGatherers[10]; // +0x50
	int m_desiredGatherers; // +0x78
	int m_currentGatherers; // +0x7C
};

BuildListInfo::BuildListInfo() :
	m_vtable(reinterpret_cast<void *>(((unsigned int)vtbl_00C0D904))),
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
