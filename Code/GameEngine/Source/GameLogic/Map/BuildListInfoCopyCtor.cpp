// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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
// ZH declares no copy ctor (implicit memberwise copy, which is why the gatherer
// array is copied in member order); the user-declared form below wraps the
// ObjectID[10] array in a struct so the init list keeps that order.
// ZH's Coord3D m_location / Coord2D m_rallyPointOffset sit at +0x0C/+0x18, but
// retail copies those five floats as separate dword moves; copy-constructing
// the canonical Coord3D/Coord2D (explicit or implicit) emits a movs block
// instead, so this view declares them as scalars (structural inference).
// EH state 0 before the first copy comes from the base with a declared-only
// dtor (BuildListInfoCtor.cpp precedent); retail's state-0 funclet destroys it
// at this+0, so the base owns the vptr (ZH MemoryPoolObject is the polymorphic
// base) rather than sitting after a derived vptr.

// The unwind funclets jump to the out-of-line ~AsciiString 0x0048BA39.
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"

class EmptyBase
{
public:
	EmptyBase() {}
	virtual void *deleteInstance(int pool);
protected:
	~EmptyBase();
};

struct BuildListGatherers
{
	int ids[10];
};

class BuildListInfo : public EmptyBase
{
public:
	BuildListInfo(const BuildListInfo &that);

private:
	AsciiString m_buildingName; // +0x04
	AsciiString m_templateName; // +0x08
	float m_locationX; // +0x0C
	float m_locationY; // +0x10
	float m_locationZ; // +0x14
	float m_rallyPointOffsetX; // +0x18
	float m_rallyPointOffsetY; // +0x1C
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
	BuildListGatherers m_resourceGatherers; // +0x50
	int m_desiredGatherers; // +0x78
	int m_currentGatherers; // +0x7C
};

BuildListInfo::BuildListInfo(const BuildListInfo &that) :
	EmptyBase(),
	m_buildingName(that.m_buildingName),
	m_templateName(that.m_templateName),
	m_locationX(that.m_locationX),
	m_locationY(that.m_locationY),
	m_locationZ(that.m_locationZ),
	m_rallyPointOffsetX(that.m_rallyPointOffsetX),
	m_rallyPointOffsetY(that.m_rallyPointOffsetY),
	m_angle(that.m_angle),
	m_isInitiallyBuilt(that.m_isInitiallyBuilt),
	m_numRebuilds(that.m_numRebuilds),
	m_nextBuildList(that.m_nextBuildList),
	m_script(that.m_script),
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
	m_resourceGatherers(that.m_resourceGatherers),
	m_desiredGatherers(that.m_desiredGatherers),
	m_currentGatherers(that.m_currentGatherers)
{
}
