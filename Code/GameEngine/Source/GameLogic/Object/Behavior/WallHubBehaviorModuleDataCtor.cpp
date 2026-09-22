// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0WallHubBehaviorModuleData@@QAE@XZ, retail 0x00453020, 148 bytes.
// ModuleData-side ctor in the WallHub file-unit: the segment template name
// vector at +8 builds through the AsciiString Vector_base alias (0x211E58)
// and is cleared, the six template-name strings at +14/+18/+1C/+20/+24/+28
// zero-init inline with declared clear/dtor folding to 0x36410 (only
// +14/+18 call clear in the body; all six plus the base plus the vector
// drive the EH states to the retail state-7 before the erase), BuilderRadius
// at +2C defaults to the 9.876 pool float, MaxBuildoutDistance at +30 to the
// 54321.0 pool float, Options at +34 is 0, StaggeredBuildFactor at +38 is 5.
// Table 0xC3FED8 carries all eleven fields at these offsets; factory
// 0x24A94C news 0x3C with this ctor as sole caller (pinned). Shape follows
// PassiveAreaEffect (empty UpdateModuleData base with declared-only dtor
// driving the EH frame, explicit vtable first member, implicit member init
// in decl order, body in retail order: clears first, then the radius,
// options, factor and distance stores).

#include <vector>

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class WallHubBehaviorModuleData : public UpdateModuleData
{
public:
	WallHubBehaviorModuleData();

private:
	const void *m_vtable; // +0x00
	unsigned int m_unused04; // +0x04, unstored gap (DemoTrap law)
	_STL::vector<AsciiString> m_segmentTemplateNames; // +0x08
	AsciiString m_hubCapTemplateName; // +0x14
	AsciiString m_defaultSegmentTemplateName; // +0x18
	AsciiString m_cliffCapTemplateName; // +0x1C
	AsciiString m_shoreCapTemplateName; // +0x20
	AsciiString m_borderCapTemplateName; // +0x24
	AsciiString m_elevatedSegmentTemplateName; // +0x28
	float m_builderRadius; // +0x2C
	float m_maxBuildoutDistance; // +0x30
	int m_options; // +0x34
	int m_staggeredBuildFactor; // +0x38
};

// ??0WallHubBehaviorModuleData@@QAE@XZ @0x453020
WallHubBehaviorModuleData::WallHubBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C3FF98))
{
	m_segmentTemplateNames.clear();
	m_hubCapTemplateName.clear();
	m_defaultSegmentTemplateName.clear();
	m_builderRadius = 9.876f;
	m_options = 0;
	m_staggeredBuildFactor = 5;
	m_maxBuildoutDistance = 54321.0f;
}
