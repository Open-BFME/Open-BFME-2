// cl: /GX /MD /DNDEBUG
//
// ??0ClearanceTestingSlowDeathBehaviorModuleData@@QAE@XZ, retail 0x00483E25,
// 160 bytes. SlowDeath ModuleData ctor over the ClearanceTesting table.
// Identity is the rowed poolkey 0x483CF4 in cluster plus rowed proc 0x483C1A
// plus factory 0x24C545 (news 0x208, sole caller). Shape: polymorphic
// SlowDeath base (declared-only ctor resolving to the pin at 0x45E386, its
// rowed virtual dtor 0x0045E4A5 for the single EH state) plus the class's own
// vftable 0x00C49E98, installed by the compiler between the base call and
// the member call (dtor rowed at 0x00483EE1) plus 5-arg GeometryInfo member through
// the pin at 0x50B74 plus sourced-before pointer take for the lea-run zeros
// at +0x1EC plus late b-local reused for +0x1FC and +0x204.

// Retail's table holds ModuleData's 30 inherited slots after the deleting destructor.
#include "../../../../Include/Common/ModuleData.h"

class SlowDeathBehaviorModuleData : public ModuleData
{
public:
	SlowDeathBehaviorModuleData();
	virtual ~SlowDeathBehaviorModuleData();
};

#include "../../../../Include/Common/Geometry.h"



class ClearanceTestingSlowDeathBehaviorModuleData : public SlowDeathBehaviorModuleData
{
public:
	ClearanceTestingSlowDeathBehaviorModuleData();
	virtual ~ClearanceTestingSlowDeathBehaviorModuleData();

private:
	unsigned char m_pad[0x190 - 8];
	GeometryInfo m_geometry;
	float m_offset[3];
	float m_clearanceMaxHeight;
	float m_clearanceMaxHeightFraction;
	float m_clearanceMinHeight;
	float m_clearanceMinHeightFraction;
};

// ??0ClearanceTestingSlowDeathBehaviorModuleData@@QAE@XZ @0x483E25
ClearanceTestingSlowDeathBehaviorModuleData::ClearanceTestingSlowDeathBehaviorModuleData()
	: m_geometry(GEOMETRY_SPHERE, false, 1.0f, 1.0f, 1.0f)
{
	float *offset = m_offset;
	float c = -20.0f;
	offset[0] = 0.0f;
	offset[1] = 0.0f;
	offset[2] = 0.0f;
	m_clearanceMaxHeight = 20.0f;
	float b = 1.1f;
	m_clearanceMaxHeightFraction = b;
	m_clearanceMinHeight = c;
	m_clearanceMinHeightFraction = b;
}
